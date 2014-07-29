//
// File:	Rect.h
// Desc:	Header of Rect
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_RECT_H__
#define __MK2014_CLASS_RECT_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes

struct TRect
{
	// Member Functions
public:
	TRect();
	TRect(float _fX, float _fY, float _fWidth, float _fHeight, bool _isCentered = false);

	TRect(const TRect& _kr);
	TRect& operator= (const TRect& _kr);

	~TRect();

	static TRect OffsetRect(const TRect& _krRect, const float _kfOffsetX, const float _kfOffsetY);


protected:

private:



	// Member Variables
public:
	float x1;
	float y1;
	float x2;
	float y2;

protected:

private:


};

#endif // __MK2014_CLASS_RECT_H__