//
// File:	Renderer.h
// Desc:	Header of Renderer
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_RENDERER_H__
#define __MK2014_CLASS_RENDERER_H__

// Library Includes
#include <Windows.h>
#include <string>
#include <vector>

// Local Includes

// Types

// Constants

// Prototypes
struct TVector2;
struct TRect;
struct TColour;

class IRenderer
{
	// Member Functions
public:
	IRenderer(){}
	virtual ~IRenderer(){};

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hwnd, int _iClientWidth, int _iClientHeight) = 0;
	virtual bool Shutdown() = 0;

	virtual void Clear(const unsigned int _kuiTargets) = 0;
	virtual void Present() = 0;

	virtual void Resize(int _iClientWidth, int _iClientHeight) = 0;
	 
	virtual int GetHeight() const = 0;
	virtual int GetWidth() const = 0;
	 
	virtual void SetClearColour(const unsigned int _kiColor) = 0;
	virtual void PushPenColour(const unsigned int _kiColor) = 0;
	virtual void PopPenColour() = 0;
	virtual void PushBrushColour(const unsigned int _kiColor) = 0;
	virtual void PopBrushColour() = 0;
	 
	virtual void DrawRectangle(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight) = 0;
	virtual void DrawRectangleFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder = false) = 0;
	virtual void DrawRectangle(const TRect& _krRect) = 0;
	virtual void DrawRectangleFill(const TRect& _krRect, const bool _kHasBorder = false) = 0;
	 
	virtual void DrawEllipse(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight) = 0;
	virtual void DrawEllipseFill(const TVector2& _rv2Position, const float _kfWidth, const float _kfHeight, const bool _kHasBorder = false) = 0;
	virtual void DrawEllipse(const TRect& _krRect) = 0;
	virtual void DrawEllipseFill(const TRect& _krRect, const bool _kHasBorder = false) = 0;

	virtual void DrawPolygon(TVector2* _pPoints, int _iPoints) = 0;
	virtual void DrawPolygonFill(TVector2* _pPoints, int _iPoints, const bool _kHasBorder = false) = 0;

	virtual void DrawLine(const TVector2& _rv2From, const TVector2& _rv2To) = 0;
	 
	virtual void PrintTextF(std::string _strMessage, const TVector2& _rv2Position, ...) = 0;
	virtual void PrintAllignedTextF(std::string _strMessage, const TRect& _rRect,	unsigned int _uiHorizAllignment = 0, unsigned int _uVertAllignment = 0, ...) = 0;

protected:

private:
	IRenderer(const IRenderer& _kr);
	IRenderer& operator= (const IRenderer& _kr);


	// Member Variables
public:

protected:
	std::vector<unsigned int> m_vecPenColours;
	std::vector<unsigned int> m_vecBrushColours;

	int m_iTargetWidth;
	int m_iTargetHeight;
	int m_iClientWidth;
	int m_iClientHeight;

	unsigned int m_uiClearColour;
	unsigned int m_uiPenColour;
	unsigned int m_uiBrushColour; 

	HINSTANCE m_hAppInst;
	HWND m_hMainWnd;

private:


};

#endif // __MK2014_CLASS_RENDERER_H__