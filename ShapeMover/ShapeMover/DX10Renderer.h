//
// File:	DX10Renderer.h
// Desc:	Header of DX10Renderer
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_DX10RENDERER_H__
#define __MK2014_CLASS_DX10RENDERER_H__

// Library Includes
#include <D3DX10.h>

// Local Includes
#include "Renderer.h"

// Types

// Constants

// Prototypes

class CDX10Renderer : public IRenderer
{
	// Member Functions
public:
	CDX10Renderer();
	virtual ~CDX10Renderer();

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
	CDX10Renderer(const CDX10Renderer& _kr);
	CDX10Renderer& operator= (const CDX10Renderer& _kr);


	// Member Variables
public:

protected:

private:
	D3DXCOLOR m_ClearColour;

	ID3D10Device* m_pDevice;
	IDXGISwapChain* m_pSwapChain;
	ID3DX10Font* m_pFont;
	ID3D10RasterizerState* m_pDefaultRasterState;

	//CViewport*					m_pViewport;
	ID3D10RenderTargetView*		m_pRenderTargetView;

};

#endif // __MK2014_CLASS_DX10RENDERER_H__