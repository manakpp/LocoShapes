// 
// File: DX11Renderer.cpp
// Desc: Implementation of DX10Renderer
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <D3DX10.h>
#include <DxErr.h>
#include <string>

// Local Includes
#include "Renderer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vertex.h"
#include "Colour.h"
#include "Rect.h"

// This Include
#include "DX10Renderer.h"

// Static Variables

// Defines
#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 


// Default Constructor
CDX10Renderer::CDX10Renderer()
: m_pDevice(0)
, m_pSwapChain(0)
, m_pDefaultRasterState(0)
, m_pFont(0)
, m_pRenderTargetView(0)
, m_pDefaultEffect(0)
, m_pDefaultTech(0)
, m_pViewMatrixEffectVariable(0)
, m_pProjectionMatrixEffectVariable(0)
, m_pWorldMatrixEffectVariable(0)
, m_pDefaultVertexInputLayout(0)
, m_pVertexBuffer(0)
, m_pIndexBuffer(0)
, m_pSprite(0)
{
	m_uBufferSize = 128;
	m_pBuffer = new char[m_uBufferSize];
	m_pBufferW = new WCHAR[m_uBufferSize];
}

// Default Destructor
CDX10Renderer::~CDX10Renderer()
{
	
}

bool CDX10Renderer::Initialise(HINSTANCE _hInstance, HWND _hwnd, int _iClientWidth, int _iClientHeight)
{
	m_hAppInst = _hInstance;
	m_hMainWnd = _hwnd;
	m_iTargetWidth = _iClientWidth;
	m_iTargetHeight = _iClientHeight;
	m_iClientWidth = _iClientWidth;
	m_iClientHeight = _iClientHeight;

	// Set up DX swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width  = m_iTargetWidth;
	sd.BufferDesc.Height = m_iTargetHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count   = 1;
	sd.SampleDesc.Quality = 0;

	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount  = 1;
	sd.OutputWindow = m_hMainWnd;
	sd.Windowed     = true;
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags        = 0;

	// Create DX10 device
	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)  
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	// Create the ID3D10Device and IDXGISwapChain which interfaces
	// with the D3D10CreateDeviceAndSwapChain function
	if(FAILED(D3D10CreateDeviceAndSwapChain(0, //default adapter
											D3D10_DRIVER_TYPE_HARDWARE,
											0,  // no software device
											createDeviceFlags, 
											D3D10_SDK_VERSION,
											&sd,
											&m_pSwapChain,
											&m_pDevice)))
	{
		MessageBoxA(0, "Failed to create DX10 device.", "ERROR", MB_OK);
		return (false);
	}

	// Create raster states. And set an initial state
	D3D10_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D10_RASTERIZER_DESC));

	// Make backface cull solid and set this as initial state
	rsDesc.FillMode = D3D10_FILL_SOLID;
	rsDesc.CullMode = D3D10_CULL_BACK;
	m_pDevice->CreateRasterizerState(&rsDesc, &m_pDefaultRasterState);
	m_pDevice->RSSetState(m_pDefaultRasterState);

	Resize(m_iClientWidth, m_iClientHeight);

	// Load the effect
	if (FAILED(D3DX10CreateEffectFromFile(L"default.fx",
                                            0,
                                            0,
                                            "fx_4_0",
                                            D3D10_SHADER_ENABLE_STRICTNESS,
                                            0,
                                            m_pDevice,
                                            0, 0,
                                            &m_pDefaultEffect,
                                            0, 0)))
	{
		MessageBoxA(0, "Failed to create DX10 device.", "ERROR", MB_OK);
		return (false);
	}

 
	m_pDefaultTech = m_pDefaultEffect->GetTechniqueByName("DefaultTech");
 
	// Create matrix effect pointers
	m_pWorldMatrixEffectVariable = m_pDefaultEffect->GetVariableByName( "gWorld" )->AsMatrix();
	m_pViewMatrixEffectVariable = m_pDefaultEffect->GetVariableByName( "gView" )->AsMatrix();
	m_pProjectionMatrixEffectVariable = m_pDefaultEffect->GetVariableByName( "gProjection" )->AsMatrix();


	// Vert layout
	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};

	
	UINT numElements = 2;
	D3D10_PASS_DESC passDesc;
	m_pDefaultTech->GetPassByIndex(0)->GetDesc(&passDesc);
 
	if (FAILED(m_pDevice->CreateInputLayout(layout,
											numElements,
											passDesc.pIAInputSignature,
											passDesc.IAInputSignatureSize,
											&m_pDefaultVertexInputLayout ) ) )
	{
		MessageBoxA(0, "Failed to create DX10 device.", "ERROR", MB_OK);
		return (false);
	};
 
	// Set the input layout
	m_pDevice->IASetInputLayout(m_pDefaultVertexInputLayout);

	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Set effect values now because they will not change
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranslation(&world, m_iClientWidth * -0.5f, m_iClientHeight * -0.5f, 0.0f);
	
	D3DXMATRIX rot;
	D3DXMatrixRotationX(&rot, static_cast<float>(D3DX_PI));

	world = world * rot;

		// Set up the view matrix
	//--------------------------------------------------------------
 
	D3DXVECTOR3 eye(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 view(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
 
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH( &viewMatrix, &eye, &view, &up);
 
	//Set up projection matrix
	//--------------------------------------------------------------
	D3DXMATRIX projectionMatrix;
	D3DXMatrixOrthoLH(&projectionMatrix, static_cast<float>(m_iClientWidth), static_cast<float>(m_iClientHeight), 0.0f, 1.0f);
	//D3DXMatrixPerspectiveFovLH(&projectionMatrix, (float)D3DX_PI * 0.5f, (float)m_iClientWidth/m_iClientHeight, 0.1f, 100.0f);

	m_pWorldMatrixEffectVariable->SetMatrix(world);
	m_pViewMatrixEffectVariable->SetMatrix(viewMatrix);
	m_pProjectionMatrixEffectVariable->SetMatrix(projectionMatrix);

	D3D10_TECHNIQUE_DESC techDesc;
	m_pDefaultTech->GetDesc(&techDesc);

	for(unsigned int p = 0; p < techDesc.Passes; ++p )
	{
		m_pDefaultTech->GetPassByIndex(p)->Apply(0);
	}
	
	
	//create vertex buffer (space for 100 vertices)
	//---------------------------------------------
 
	UINT numVertices = 100;
 
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( TVertex ) * numVertices; //total size of buffer in bytes
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
 
	if ( FAILED( m_pDevice->CreateBuffer( &bd, 0, &m_pVertexBuffer ) ) ) 
	{
		MessageBoxA(0, "Failed to create DX10 device.", "ERROR", MB_OK);
		return (false);
	}

	PushPenColour(TColour(0, 0, 0, 255).Value());
	PushBrushColour(TColour(0, 0, 0, 255).Value());

	// Init font
	D3DX10_FONT_DESC fontDesc;
	fontDesc.Height          = 16;
    fontDesc.Width           = 0;
    fontDesc.Weight          = 0;
    fontDesc.MipLevels       = 1;
    fontDesc.Italic          = false;
    fontDesc.CharSet         = DEFAULT_CHARSET;
    fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDesc.Quality         = DEFAULT_QUALITY;
    fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
    wcscpy_s(fontDesc.FaceName, L"Times New Roman");

	D3DX10CreateFontIndirect(m_pDevice, &fontDesc, &m_pFont);

		D3DX10CreateSprite(m_pDevice, 512, &m_pSprite);

	return(true);
}

bool CDX10Renderer::Shutdown()
{
	delete[] m_pBuffer;
	m_pBuffer = 0;

	delete[] m_pBufferW;
	m_pBufferW = 0;

	ReleaseCOM(m_pFont);
	ReleaseCOM(m_pSprite);
	ReleaseCOM(m_pSwapChain);
	ReleaseCOM(m_pDefaultRasterState);
	ReleaseCOM(m_pRenderTargetView);

	ReleaseCOM(m_pDefaultEffect);
	ReleaseCOM(m_pDefaultVertexInputLayout);
	ReleaseCOM(m_pVertexBuffer);
	ReleaseCOM(m_pIndexBuffer);

	ReleaseCOM(m_pDevice);

	return true;
}
	 
void CDX10Renderer::Clear(const unsigned int _kuiTargets)
{
	m_pDevice->ClearRenderTargetView(m_pRenderTargetView, m_ClearColour);
}

void CDX10Renderer::Present()
{
	m_pSwapChain->Present(0, 0);
}
	 
void CDX10Renderer::SetClearColour(const unsigned int _kiColor)
{
	m_ClearColour = D3DXCOLOR(_kiColor);
}

void CDX10Renderer::PushPenColour(const unsigned int _kiColor)
{
	m_uiPenColour = _kiColor;
	m_vecPenColours.push_back(_kiColor);
}

void CDX10Renderer::PopPenColour()
{
	m_vecPenColours.pop_back();
	m_uiPenColour =  m_vecPenColours.back();
}

void CDX10Renderer::PushBrushColour(const unsigned int _kiColor)
{
	m_uiBrushColour = _kiColor;
	m_vecBrushColours.push_back(_kiColor);
}

void CDX10Renderer::PopBrushColour()
{
	m_vecBrushColours.pop_back();
	m_uiBrushColour =  m_vecPenColours.back();
}
	 
void CDX10Renderer::DrawRectangle(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight)
{
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

	//fill vertex buffer with vertices
	TVertex* pVerts = 0;

	// Set vertex buffer
	UINT stride = sizeof( TVertex );
	UINT offset = 0;
	m_pDevice->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	m_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &pVerts);

	pVerts[0] = TVertex(TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0), m_uiPenColour);
	pVerts[1] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0), m_uiPenColour);
	pVerts[2] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0), m_uiPenColour);
	pVerts[3] = TVertex(TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0), m_uiPenColour);
	pVerts[4] = TVertex(TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0), m_uiPenColour);

	m_pVertexBuffer->Unmap();
	m_pDevice->Draw(5, 0);
}

void CDX10Renderer::DrawRectangleFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder)
{
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//fill vertex buffer with vertices
	TVertex* pVerts = 0;

	// Set vertex buffer
	UINT stride = sizeof( TVertex );
	UINT offset = 0;
	m_pDevice->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	m_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &pVerts);

	pVerts[0] = TVertex(TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0), m_uiBrushColour);
	pVerts[1] = TVertex(TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0), m_uiBrushColour);
	pVerts[2] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0), m_uiBrushColour);
	pVerts[3] = TVertex(TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0), m_uiBrushColour);
	pVerts[4] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0), m_uiBrushColour);
	pVerts[5] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0), m_uiBrushColour);

	m_pVertexBuffer->Unmap();
	m_pDevice->Draw(6, 0);

	if(_kHasBorder)
		DrawRectangle(_rv2Position, _kfWidth, _kfHeight);
}

void CDX10Renderer::DrawRectangle(const TRect& _krRect)
{
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

	//fill vertex buffer with vertices
	TVertex* pVerts = 0;

	// Set vertex buffer
	UINT stride = sizeof( TVertex );
	UINT offset = 0;
	m_pDevice->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	m_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &pVerts);

	pVerts[0] = TVertex(TVector3(_krRect.x1, _krRect.y1, 0), m_uiPenColour);
	pVerts[1] = TVertex(TVector3(_krRect.x2, _krRect.y1, 0), m_uiPenColour);
	pVerts[2] = TVertex(TVector3(_krRect.x2, _krRect.y2, 0), m_uiPenColour);
	pVerts[3] = TVertex(TVector3(_krRect.x1, _krRect.y2, 0), m_uiPenColour);
	pVerts[4] = TVertex(TVector3(_krRect.x1, _krRect.y1, 0), m_uiPenColour);

	m_pVertexBuffer->Unmap();
	m_pDevice->Draw(5, 0);
}

void CDX10Renderer::DrawRectangleFill(const TRect& _krRect, const bool _kHasBorder)
{
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//fill vertex buffer with vertices
	TVertex* pVerts = 0;

	// Set vertex buffer
	UINT stride = sizeof( TVertex );
	UINT offset = 0;
	m_pDevice->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	m_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &pVerts);

	pVerts[0] = TVertex(TVector3(_krRect.x1, _krRect.y2, 0), m_uiBrushColour);
	pVerts[1] = TVertex(TVector3(_krRect.x1, _krRect.y1, 0), m_uiBrushColour);
	pVerts[2] = TVertex(TVector3(_krRect.x2, _krRect.y2, 0), m_uiBrushColour);
	pVerts[3] = TVertex(TVector3(_krRect.x1, _krRect.y1, 0), m_uiBrushColour);
	pVerts[4] = TVertex(TVector3(_krRect.x2, _krRect.y1, 0), m_uiBrushColour);
	pVerts[5] = TVertex(TVector3(_krRect.x2, _krRect.y2, 0), m_uiBrushColour);

	m_pVertexBuffer->Unmap();
	m_pDevice->Draw(6, 0);

	if(_kHasBorder)
		DrawRectangle(_krRect);
}
	
void CDX10Renderer::DrawEllipse(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight)
{
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

	//fill vertex buffer with vertices
	TVertex* pVerts = 0;

	// Set vertex buffer
	UINT stride = sizeof( TVertex );
	UINT offset = 0;
	m_pDevice->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	m_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &pVerts);

	const int kiCirclePoints = 32;
	for(int i = 0; i < kiCirclePoints; ++i)
	{
		float fAngle = (2.0f * 3.14159265359f / static_cast<float>(kiCirclePoints)) * i;
		
		pVerts[i] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f * cos(fAngle), _rv2Position.y + _kfHeight * 0.5f * sin(fAngle), 0), m_uiPenColour);
	}

	pVerts[kiCirclePoints] = TVertex(TVector3(pVerts[0].x, pVerts[0].y, 0), m_uiPenColour);

	m_pVertexBuffer->Unmap();
	m_pDevice->Draw(kiCirclePoints + 1, 0);
}

void CDX10Renderer::DrawEllipseFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder)
{
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//fill vertex buffer with vertices
	TVertex* pVerts = 0;

	// Set vertex buffer
	UINT stride = sizeof( TVertex );
	UINT offset = 0;
	m_pDevice->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	m_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &pVerts);

	const int kiCirclePoints = 20;
	const int kiMaxInc = kiCirclePoints * 3;

	for(int i = 0; i < kiMaxInc; i += 3)
	{
		float fAngleA = (2.0f * 3.14159265359f / static_cast<float>(kiCirclePoints)) * i;
		float fAngleB = (2.0f * 3.14159265359f / static_cast<float>(kiCirclePoints)) * (i + 1);
		
		pVerts[i] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f * cos(fAngleA), _rv2Position.y + _kfHeight * 0.5f * sin(fAngleA), 0), m_uiBrushColour);
		pVerts[i + 1] = TVertex(TVector3(_rv2Position.x + _kfWidth * 0.5f * cos(fAngleB), _rv2Position.y + _kfHeight * 0.5f * sin(fAngleB), 0), m_uiBrushColour);
		pVerts[i + 2] = TVertex(TVector3(_rv2Position.x, _rv2Position.y, 0), m_uiBrushColour);
	}

	m_pVertexBuffer->Unmap();
	m_pDevice->Draw(kiMaxInc, 0);

	if(_kHasBorder)
		DrawEllipse(_rv2Position, _kfWidth, _kfHeight);
}

void CDX10Renderer::DrawEllipse(const TRect& _krRect)
{
	// Not used
}

void CDX10Renderer::DrawEllipseFill(const TRect& _krRect, const bool _kHasBorder)
{
	// Not used
}
	 
void CDX10Renderer::DrawPolygon(TVector2* _pPoints, int _iPoints)
{
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

	//fill vertex buffer with vertices
	TVertex* pVerts = 0;

	// Set vertex buffer
	UINT stride = sizeof( TVertex );
	UINT offset = 0;
	m_pDevice->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );

	m_pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &pVerts);

	for(int i = 0; i < _iPoints; ++i)
	{
		pVerts[i] = TVertex(TVector3(_pPoints[i].x, _pPoints[i].y, 0), m_uiPenColour);
	}

	pVerts[_iPoints] = TVertex(TVector3(_pPoints[0].x, _pPoints[0].y, 0), m_uiPenColour);

	m_pVertexBuffer->Unmap();
	m_pDevice->Draw(_iPoints + 1, 0);
}

void CDX10Renderer::DrawPolygonFill(TVector2* _pPoints, int _iPoints, const bool _kHasBorder)
{
	// Can't draw polygons... No triangle fan topology, no easy way to do it
	DrawPolygon(_pPoints, _iPoints);
}
	 
void CDX10Renderer::DrawLine(const TVector2& _rv2From, const TVector2& _rv2To)
{
	// Not used
}
	 
void CDX10Renderer::PrintTextF(std::string _strMessage, const TVector2& _rv2Position, ...)
{
	if(_strMessage.size() == 0)
	return;
 
	std::wstring wstrTo;
    wchar_t *wszTo = new wchar_t[_strMessage.length() + 1];
    wszTo[_strMessage.size()] = L'\0';
    MultiByteToWideChar(CP_ACP, 0, _strMessage.c_str(), -1, wszTo, (int)_strMessage.length());
    wstrTo = wszTo;

	va_list arg;
	va_start(arg, _rv2Position);
	_vsnwprintf_s(m_pBufferW, m_uBufferSize, m_uBufferSize, wszTo, arg);
	va_end(arg);

	delete[] wszTo;
	
	RECT rect;
	rect.left = static_cast<long>(_rv2Position.x);
	rect.right = static_cast<long>(_rv2Position.x + 1000.0f);
	rect.top = static_cast<long>(_rv2Position.y);
	rect.bottom = static_cast<long>(_rv2Position.y + 1000.0f);

	m_pFont->DrawText(0, m_pBufferW, -1, &rect, DT_NOCLIP, m_uiPenColour);
}

void CDX10Renderer::PrintAllignedTextF(std::string _strMessage, const TRect& _rRect, unsigned int _uiHorizAllignment, unsigned int _uVertAllignment, ...)
{
	if(_strMessage.size() == 0)
		return;

	std::wstring wstrTo;
    wchar_t *wszTo = new wchar_t[_strMessage.length() + 1];
    wszTo[_strMessage.size()] = L'\0';
    MultiByteToWideChar(CP_ACP, 0, _strMessage.c_str(), -1, wszTo, (int)_strMessage.length());
    wstrTo = wszTo;

	va_list arg;
	va_start(arg, _uVertAllignment);
	_vsnwprintf_s(m_pBufferW, m_uBufferSize, m_uBufferSize, wszTo, arg);
	va_end(arg);

	delete[] wszTo;

	RECT rect;
	rect.left = static_cast<long>(_rRect.x1);
	rect.right = static_cast<long>(_rRect.x2);
	rect.top = static_cast<long>(_rRect.y1);
	rect.bottom = static_cast<long>(_rRect.y2);

	unsigned int uiFlags = _uiHorizAllignment | _uVertAllignment | DT_NOCLIP;

	m_pSprite->Begin(D3DX10_SPRITE_SAVE_STATE);
	m_pFont->DrawText(0, m_pBufferW, -1, &rect, uiFlags, m_uiPenColour);
	m_pSprite->End();
}
	
void CDX10Renderer::Resize(int _iClientWidth, int _iClientHeight)
{
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	ReleaseCOM(m_pRenderTargetView);

	// Resize the swap chain and recreate the render target view.
	// 1. Create a render target view to the swap chain's back buffer.
	HR(m_pSwapChain->ResizeBuffers(1, _iClientWidth, _iClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D10Texture2D* backBuffer;
	HR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<LPVOID*>(&backBuffer)));
	HR(m_pDevice->CreateRenderTargetView(backBuffer, 0, &m_pRenderTargetView));
	
	ReleaseCOM(backBuffer);

	m_pDevice->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	// 2. Create the depth/stencil buffer and it's associated depth/stencil view
	D3D10_TEXTURE2D_DESC depthStencilDesc;
	
	depthStencilDesc.Width     = _iClientWidth;
	depthStencilDesc.Height    = _iClientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1; // multisampling must match
	depthStencilDesc.SampleDesc.Quality = 0; // swap chain values.
	depthStencilDesc.Usage          = D3D10_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;
	
	// 5. Set the viewport transform.
	D3D10_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width    = _iClientWidth;
	vp.Height   = _iClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_pDevice->RSSetViewports(1, &vp);
}

int CDX10Renderer::GetHeight() const
{
	return m_iTargetHeight;
}

int CDX10Renderer::GetWidth() const
{
	return m_iTargetHeight;
}