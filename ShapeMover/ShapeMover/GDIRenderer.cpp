// 
//  Bachelor of Software Engineering
//  Media Design School
//  Auckland
//  New Zealand
// 
//  Copyright (c) 2012 Media Design School
// 
//  Author:	Mana Khamphanpheng
// 
// SVN Info
// $Author$
// $Date$
// $Rev$
// 

// Library Includes

// Local Includes
#include "Rect.h"
#include "Vector2.h"
#include "Colour.h"

// This Include
#include "GDIRenderer.h"

// Static Variables

// Default Constructor
CGDIRenderer::CGDIRenderer()
: m_hDC(0)
, m_GDIPlusToken(0)
, m_pGraphics(0)
, m_iClearBrush(0)
, m_pPen(0)
, m_pBrush(0)
, m_pFont(0)
{
	m_uBufferSize = 128;
	m_pBuffer = new char[m_uBufferSize];
	m_pBufferW = new WCHAR[m_uBufferSize];
}

// Default Destructor
CGDIRenderer::~CGDIRenderer()
{
	// Use the shutdown function
}

bool CGDIRenderer::Initialise(HINSTANCE _hInstance, HWND _hwnd, int _iClientWidth, int _iClientHeight)
{
	// Init members
	m_hAppInst = _hInstance;
	m_hMainWnd = _hwnd;
	m_iTargetWidth = _iClientWidth;
	m_iTargetHeight = _iClientHeight;
	m_iClientWidth = _iClientWidth;
	m_iClientHeight = _iClientHeight;

	// Init the GDI+
	GdiplusStartupInput gdiplusStartupInput;
	gdiplusStartupInput.GdiplusVersion = 1;
	gdiplusStartupInput.DebugEventCallback = 0;
	gdiplusStartupInput.SuppressBackgroundThread = false;
	gdiplusStartupInput.SuppressExternalCodecs = false;
	GdiplusStartup(&m_GDIPlusToken, &gdiplusStartupInput, 0);

	// Create Backbuffer and window DC
	Resize(_iClientWidth, _iClientHeight);

	m_pPen = new Pen(Color(255, 0, 0, 0)); // Black
	PushPenColour(TColour(0, 0, 0, 255).Value());

	m_pBrush = new SolidBrush(Color(255, 0, 0, 0)); // Black 0
	PushBrushColour(TColour(0, 0, 0, 255).Value());

	m_colClear = Color(255, 255, 125, 125);

	// Create Default font
	m_pFont = new TFont();
	m_pFont->pBrush = new SolidBrush(Color(255, 0, 0, 0));
	m_pFont->pFont = new Font(&FontFamily(L"Times New Roman"), 16, FontStyleRegular, UnitPixel);

	return true;
}

bool CGDIRenderer::Shutdown()
{
	SelectObject(m_hDC, m_hOldSurface);
	DeleteObject(m_hSurface);
	ReleaseDC(m_hMainWnd, m_hDC);

	// Clean up GDI+ 
	delete m_pFont;
	m_pFont = 0;

	delete m_pPen;
	m_pPen = 0;

	delete m_pBrush;
	m_pBrush = 0;
	
	delete[] m_pBuffer;
	m_pBuffer;

	delete[] m_pBufferW;
	m_pBufferW;

	delete m_pGraphics;
	m_pGraphics = 0;
	
	// Shutdown the GDI+
	 GdiplusShutdown(m_GDIPlusToken);

	 return true;
}

void CGDIRenderer::Clear(const unsigned int _kuiTargets)
{
	m_pGraphics->Clear(m_colClear);
}

void CGDIRenderer::Present()
{
	HDC hDC = ::GetDC(m_hMainWnd);
	BitBlt(hDC, 0, 0, m_iTargetWidth, m_iTargetHeight, m_hDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hMainWnd, hDC);
}

void CGDIRenderer::SetClearColour(const unsigned int _kiColor)
{
	m_uiClearColour = _kiColor;
	m_colClear = Color(static_cast<ARGB>(_kiColor));
}

void CGDIRenderer::PushPenColour(const unsigned int _kiColor)
{
	m_uiPenColour = _kiColor;
	m_pPen->SetColor(static_cast<ARGB>(_kiColor));
	m_vecPenColours.push_back(_kiColor);
}

void CGDIRenderer::PopPenColour()
{
	m_vecPenColours.pop_back();
	m_pPen->SetColor(static_cast<ARGB>(m_vecPenColours.back()));
}

void CGDIRenderer::PushBrushColour(const unsigned int _kiColor)
{
	Color
	m_uiBrushColour = _kiColor;
	m_pBrush->SetColor(static_cast<ARGB>(_kiColor));
	m_vecBrushColours.push_back(_kiColor);
}

void CGDIRenderer::PopBrushColour()
{
	m_vecBrushColours.pop_back();
	m_pBrush->SetColor(static_cast<ARGB>(m_vecBrushColours.back()));
}

void CGDIRenderer::DrawRectangle(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight)
{
	m_pGraphics->DrawRectangle(m_pPen, _rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, _kfWidth, _kfHeight);
}

void CGDIRenderer::DrawRectangleFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder)
{
	m_pGraphics->FillRectangle(m_pBrush, _rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, _kfWidth, _kfHeight);

	if(_kHasBorder)
		DrawRectangle(_rv2Position, _kfWidth, _kfHeight);
}

void CGDIRenderer::DrawRectangle(const TRect& _krRect)
{
	m_pGraphics->DrawRectangle(m_pPen, _krRect.x1, _krRect.y1, _krRect.x2 - _krRect.x1, _krRect.y2 - _krRect.y1);
}

void CGDIRenderer::DrawRectangleFill(const TRect& _krRect, const bool _kHasBorder)
{
	m_pGraphics->FillRectangle(m_pBrush, _krRect.x1, _krRect.y1, _krRect.x2 - _krRect.x1, _krRect.y2 - _krRect.y1);

	if(_kHasBorder)
		DrawRectangle(_krRect);
}

void CGDIRenderer::DrawEllipse(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight)
{
	m_pGraphics->DrawEllipse(m_pPen, _rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, _kfWidth, _kfHeight);
}

void CGDIRenderer::DrawEllipseFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder)
{
	m_pGraphics->FillEllipse(m_pBrush, _rv2Position.x - _kfWidth * 0.5f, _rv2Position.y - _kfHeight * 0.5f, _kfWidth, _kfHeight);

	if(_kHasBorder)
		DrawEllipse(_rv2Position, _kfWidth, _kfHeight);
}

void CGDIRenderer::DrawEllipse(const TRect& _krRect)
{
	m_pGraphics->DrawEllipse(m_pPen, _krRect.x1, _krRect.y1, _krRect.x2 - _krRect.x1, _krRect.y2 - _krRect.y1);
}

void CGDIRenderer::DrawEllipseFill(const TRect& _krRect, const bool _kHasBorder)
{
	m_pGraphics->FillEllipse(m_pBrush, _krRect.x1, _krRect.y1, _krRect.x2 - _krRect.x1, _krRect.y2 - _krRect.y1);
	
	if(_kHasBorder)
		DrawEllipse(_krRect);
}


void CGDIRenderer::DrawPolygon(TVector2* _pPoints, int _iPoints)
{
	m_pGraphics->DrawPolygon(m_pPen, reinterpret_cast<PointF*>(_pPoints), _iPoints);
}

void CGDIRenderer::DrawPolygonFill(TVector2* _pPoints, int _iPoints, const bool _kHasBorder)
{
	m_pGraphics->FillPolygon(m_pBrush, reinterpret_cast<PointF*>(_pPoints), _iPoints);

	if(_kHasBorder)
		DrawPolygon(_pPoints, _iPoints);
}

void CGDIRenderer::DrawLine(const TVector2& _rv2From, const TVector2& _rv2To)
{
	TVector2 from = _rv2From;
	TVector2 to = _rv2To;

	m_pGraphics->DrawLine(m_pPen, *reinterpret_cast<PointF*>(&from), *reinterpret_cast<PointF*>(&to));
}

void CGDIRenderer::PrintTextF(std::string _strMessage, const TVector2& _rv2Position, ...)
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
	
	TVector2 position = _rv2Position;
	m_pGraphics->DrawString(m_pBufferW, -1, m_pFont->pFont, *reinterpret_cast<PointF*>(&position), m_pFont->pBrush);
}

void CGDIRenderer::PrintAllignedTextF(std::string _strMessage, const TRect& _krRect, unsigned int _uiHorizAllignment, unsigned int _uVertAllignment, ...)
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

	StringFormat stringFormat;
	stringFormat.SetAlignment((StringAlignment)_uiHorizAllignment);
	stringFormat.SetLineAlignment((StringAlignment)_uVertAllignment);

	m_pGraphics->DrawString(m_pBufferW, -1, m_pFont->pFont, RectF(_krRect.x1, _krRect.y1, _krRect.x2 - _krRect.x1, _krRect.y2 - _krRect.y1), &stringFormat, m_pFont->pBrush);
}

void CGDIRenderer::Resize(int _iClientWidth, int _iClientHeight)
{
	if(m_pGraphics)
	{
		delete m_pGraphics;
		SelectObject(m_hDC, m_hOldSurface);
		DeleteObject(m_hSurface);
		ReleaseDC(m_hMainWnd, m_hDC);
	}

	// Create Backbuffer and window DC
	HDC hWindowDC = ::GetDC(m_hMainWnd);
	m_hDC = CreateCompatibleDC(hWindowDC);
	m_hSurface = CreateCompatibleBitmap(hWindowDC, _iClientWidth, _iClientHeight);
	ReleaseDC(m_hMainWnd, hWindowDC);
	m_hOldSurface = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));
	m_iClientHeight = _iClientHeight;
	m_iClientWidth = _iClientWidth; 
	
	m_pGraphics = new Graphics(m_hDC);
	//m_pGraphics->SetCompositingMode( CompositingModeSourceCopy );
	m_pGraphics->SetCompositingQuality( CompositingQualityHighSpeed );
	m_pGraphics->SetPixelOffsetMode( PixelOffsetModeNone );
	m_pGraphics->SetSmoothingMode( SmoothingModeNone );
	m_pGraphics->SetInterpolationMode( InterpolationModeDefault );
}

int CGDIRenderer::GetHeight() const
{
	return (m_iTargetHeight);
}

int CGDIRenderer::GetWidth() const
{
	return (m_iTargetWidth);
}