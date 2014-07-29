//
// File:	Circle.h
// Desc:	Header of Circle
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_CIRCLE_H__
#define __MK2014_CLASS_CIRCLE_H__

// Library Includes

// Local Includes
#include "Shape.h"

// Types

// Constants

// Prototypes


class CCircle : public CShape
{
	// Member Functions
public:
	CCircle();
	virtual ~CCircle();

	void Render(IRenderer& _rRenderer);

protected:

private:
	CCircle(const CCircle& _kr);
	CCircle& operator= (const CCircle& _kr);


	// Member Variables
public:

protected:

private:


};

#endif // __MK2014_CLASS_CIRCLE_H__