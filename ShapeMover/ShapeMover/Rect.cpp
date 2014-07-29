// 
// File: Rect.cpp
// Desc: Implementation of Rect
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes

// Local Includes
#include "Renderer.h"

// This Include
#include "Rect.h"

// Static Variables


// Default Constructor
TRect::TRect()
{
	
}

TRect::TRect(float _fX, float _fY, float _fWidth, float _fHeight, bool _isCentered)
{
	if(_isCentered)
	{
		x1 = _fX - _fWidth * 0.5f;
		x2 = _fX + _fWidth * 0.5f;
		y1 = _fY - _fHeight * 0.5f;
		y2 = _fY + _fHeight * 0.5f;
		return;
	}

	x1 = _fX;
	x2 = _fX + _fWidth;
	y1 = _fY;
	y2 = _fY + _fHeight;
}

// Default Destructor
TRect::~TRect()
{
	
}

TRect::TRect(const TRect& _kr)
{
	x1 = _kr.x1;
	x2 = _kr.x2;
	y1 = _kr.y1;
	y2 = _kr.y2;
}

TRect& TRect::operator =(const TRect& _kr)
{
	x1 = _kr.x1;
	x2 = _kr.x2;
	y1 = _kr.y1;
	y2 = _kr.y2;

	return (*this);
}

TRect TRect::OffsetRect(const TRect& _krRect, const float _kfOffsetX, const float _kfOffsetY)
{
	TRect rect = _krRect;
	rect.x1 += _kfOffsetX;
	rect.x2 += _kfOffsetX;
	rect.y1 += _kfOffsetY;
	rect.y2 += _kfOffsetY;

	return rect;
}