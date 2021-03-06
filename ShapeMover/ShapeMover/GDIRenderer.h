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

#pragma once

#ifndef __MANA2012_CLASS_RENDERER_H__
#define __MANA2012_CLASS_RENDERER_H__

// Library Includes
#include <string>
#include <Windows.h>
#include <vector>
#include <objidl.h>
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

// Local Includes
#include "Renderer.h"

// Types
typedef struct TFont
{
	TFont::TFont()
	:pBrush(0), pFont(0)
	{

	}
	TFont::~TFont()
	{
		delete pBrush; 
		pBrush;
		delete pFont; 
		pFont;
	}
	SolidBrush*  pBrush;
	Font*        pFont;
} TFont;

// Constants

// Prototypes

class CGDIRenderer : public IRenderer
{
	// Member Functions
public:
	CGDIRenderer();
	virtual ~CGDIRenderer();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hwnd, int _iClientWidth, int _iClientHeight);
	virtual bool Shutdown();

	virtual void Clear(const unsigned int _kuiTargets);
	virtual void Present();
	
	virtual void SetClearColour(const unsigned int _kiColor);
	virtual void PushPenColour(const unsigned int _kiColor);
	virtual void PopPenColour();
	virtual void PushBrushColour(const unsigned int _kiColor);
	virtual void PopBrushColour(); 

	virtual void DrawRectangle(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight);
	virtual void DrawRectangleFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder);
	virtual void DrawRectangle(const TRect& _krRect);
	virtual void DrawRectangleFill(const TRect& _krRect, const bool _kHasBorder);
	 
	virtual void DrawEllipse(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight);
	virtual void DrawEllipseFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder);
	virtual void DrawEllipse(const TRect& _krRect);
	virtual void DrawEllipseFill(const TRect& _krRect, const bool _kHasBorder);

	virtual void DrawPolygon(TVector2* _pPoints, int _iPoints);
	virtual void DrawPolygonFill(TVector2* _pPoints, int _iPoints, const bool _kHasBorder);

	virtual void DrawLine(const TVector2& _rv2From, const TVector2& _rv2To);
	 
	virtual void PrintTextF(std::string _strMessage, const TVector2& _rv2Position, ...);
	virtual void PrintAllignedTextF(std::string _strMessage, const TRect& _rRect,	unsigned int _uiHorizAllignment, unsigned int _uVertAllignment, ...);

	virtual void Resize(int _iClientWidth, int _iClientHeight);

	virtual int GetHeight() const;
	virtual int GetWidth() const;


protected:

private:
	CGDIRenderer(const CGDIRenderer& _kr);
	CGDIRenderer& operator= (const CGDIRenderer& _kr);

	// Member Variables
public:

protected:

private:
	ULONG_PTR m_GDIPlusToken;

	Color m_colClear;

	HDC m_hDC;
	HBITMAP m_hSurface;
	HBITMAP m_hOldSurface;
	
	Graphics* m_pGraphics;
	Pen* m_pPen;
	SolidBrush* m_pBrush;
	TFont* m_pFont;
	
	WCHAR*	m_pBufferW;
	char*	m_pBuffer;
	
	int m_iClearBrush;
	UINT32	m_uBufferSize;
};

#endif // __MANA2012_CLASS_RENDERER_H__