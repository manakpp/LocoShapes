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

// Local Includes
#include "Renderer.h"
#include "Vector2.h"
#include "Vector3.h"

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
{
	
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

	Resize(m_iClientWidth, m_iClientHeight);

	return(true);
}

bool CDX10Renderer::Shutdown()
{
	ReleaseCOM(m_pFont);
	ReleaseCOM(m_pSwapChain);
	ReleaseCOM(m_pDefaultRasterState);
	ReleaseCOM(m_pRenderTargetView);
	ReleaseCOM(m_pDevice);

	return true;
}
	 
void CDX10Renderer::Clear(const unsigned int _kuiTargets)
{
	m_pDevice->ClearRenderTargetView(m_pRenderTargetView, m_ClearColour);

	// Don't need other targets at the moment
	//UINT clear = 0;
	//if(_kuiTargets & D3D10_CLEAR_DEPTH == D3D10_CLEAR_DEPTH)
	//	clear |= D3D10_CLEAR_DEPTH;

	//if(_kuiTargets & D3D10_CLEAR_STENCIL == D3D10_CLEAR_STENCIL)
	//	clear |= D3D10_CLEAR_STENCIL;
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

}

void CDX10Renderer::PopPenColour()
{

}

void CDX10Renderer::PushBrushColour(const unsigned int _kiColor)
{
}

void CDX10Renderer::PopBrushColour()
{

}
	 
void CDX10Renderer::DrawRectangle(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight)
{
	const int kiNumberOfVerts = 4;
	TVector3 verts[kiNumberOfVerts];

	verts[0] = TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0.0f);
	verts[1] = TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0.0f);
	verts[2] = TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0.0f);
	verts[3] = TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0.0f);

	ID3D10Buffer* pVertexBuffer = 0;

	D3D10_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D10_USAGE_IMMUTABLE;
    vertexBufferDesc.ByteWidth = 48; // 4 points of a rect * 12 bytes of xyz
    vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_READ;
    vertexBufferDesc.MiscFlags = 0;

    D3D10_SUBRESOURCE_DATA vertexInitData;
    vertexInitData.pSysMem = &verts;
	HR(m_pDevice->CreateBuffer(&vertexBufferDesc, &vertexInitData, &pVertexBuffer));


	DWORD iIndices = 6;
	DWORD* indices = new DWORD[iIndices];
			
	indices[0] = 0; 
	indices[1] = 1; 
	indices[2] = 2; 
	indices[3] = 1;
	indices[4] = 3; 
	indices[5] = 2;

	unsigned int stride = 12;
	unsigned int offset = 0;
	m_pDevice->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pDevice->IASetIndexBuffer(0, DXGI_FORMAT_R32_UINT, 0);
	m_pDevice->DrawIndexed(6, 0, 0);
}

void CDX10Renderer::DrawRectangleFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder)
{
	/*const int kiNumberOfVerts = 4;
	TVector3* pVerts = new TVector3[kiNumberOfVerts];

	pVerts[0] = TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0.0f);
	pVerts[1] = TVector3(_rv2Position.x - _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0.0f);
	pVerts[2] = TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, 0.0f);
	pVerts[3] = TVector3(_rv2Position.x + _kfWidth * 0.5f, _rv2Position.y + _kfHeight * 0.5f, 0.0f);

	ID3D10Buffer* pVertexBuffer = 0;

	D3D10_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(TVector3) * kiNumberOfVerts;
    vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    D3D10_SUBRESOURCE_DATA vertexInitData;
    vertexInitData.pSysMem = pVerts;
	vertexInitData.SysMemPitch = 0;
	vertexInitData.SysMemSlicePitch = 0;
	HR(m_pDevice->CreateBuffer(&vertexBufferDesc, &vertexInitData, &pVertexBuffer));

	DWORD iIndices = 6;
	DWORD* pIndices = new DWORD[iIndices];
			
	pIndices[0] = 0; 
	pIndices[1] = 1; 
	pIndices[2] = 2; 
	pIndices[3] = 1;
	pIndices[4] = 3; 
	pIndices[5] = 2;

	ID3D10Buffer* pIndexBuffer = 0;

	D3D10_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * iIndices;
    indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

    D3D10_SUBRESOURCE_DATA indexInitData;
    indexInitData.pSysMem = pIndices;
	indexInitData.SysMemPitch = 0;
	indexInitData.SysMemSlicePitch = 0;
	HR(m_pDevice->CreateBuffer(&indexBufferDesc, &indexInitData, &pIndexBuffer));

	unsigned int stride = sizeof(TVector3);
	unsigned int offset = 0;
	m_pDevice->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pDevice->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDevice->DrawIndexed(6, 0, 0);

	delete pVertexBuffer;
	delete pIndexBuffer;
	delete[] pVerts;
	delete[] pIndices;*/
}

void CDX10Renderer::DrawRectangle(const TRect& _krRect)
{

}

void CDX10Renderer::DrawRectangleFill(const TRect& _krRect, const bool _kHasBorder)
{

}
	
void CDX10Renderer::DrawEllipse(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight)
{

}

void CDX10Renderer::DrawEllipseFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder)
{

}

void CDX10Renderer::DrawEllipse(const TRect& _krRect)
{

}

void CDX10Renderer::DrawEllipseFill(const TRect& _krRect, const bool _kHasBorder)
{

}
	 
void CDX10Renderer::DrawPolygon(TVector2* _pPoints, int _iPoints)
{

}

void CDX10Renderer::DrawPolygonFill(TVector2* _pPoints, int _iPoints, const bool _kHasBorder)
{

}
	 
void CDX10Renderer::DrawLine(const TVector2& _rv2From, const TVector2& _rv2To)
{

}
	 
void CDX10Renderer::PrintTextF(std::string _strMessage, const TVector2& _rv2Position, ...)
{

}

void CDX10Renderer::PrintAllignedTextF(std::string _strMessage, const TRect& _rRect,	unsigned int _uiHorizAllignment, unsigned int _uVertAllignment, ...)
{

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
	HR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_pDevice->CreateRenderTargetView(backBuffer, 0, &m_pRenderTargetView));
	ReleaseCOM(backBuffer);


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