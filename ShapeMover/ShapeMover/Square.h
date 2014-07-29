//
// File:	Square.h
// Desc:	Header of Square
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_SQUARE_H__
#define __MK2014_CLASS_SQUARE_H__

// Library Includes

// Local Includes
#include "Shape.h"

// Types

// Constants

// Prototypes

class CSquare : public CShape
{
	// Member Functions
public:
	CSquare();
	virtual ~CSquare();

	void Render(IRenderer& _rRenderer);


protected:

private:
	CSquare(const CSquare& _kr);
	CSquare& operator= (const CSquare& _kr);


	// Member Variables
public:

protected:

private:

};

#endif // __MK2014_CLASS_SQUARE_H__