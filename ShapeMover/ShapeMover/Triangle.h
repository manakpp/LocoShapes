//
// File:	Triangle.h
// Desc:	Header of Triangle
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_TRIANGLE_H__
#define __MK2014_CLASS_TRIANGLE_H__

// Library Includes

// Local Includes
#include "Shape.h"
#include "Vector2.h"

// Types

// Constants

// Prototypes

class CTriangle : public CShape
{
	// Member Functions
public:
	CTriangle();
	virtual ~CTriangle();

	bool Initialise(const float _kfX, const float _kfY, const float _kfSize, const unsigned int _kuiBorderColour = 0xFF000000, const unsigned int _kuiFillColour = 0xFF000000);
	void Render(IRenderer& _rRenderer);
	
	void UpdatePoints();

protected:

private:
	CTriangle(const CTriangle& _kr);
	CTriangle& operator= (const CTriangle& _kr);


	// Member Variables
public:

protected:

private:
	TVector2 m_points[3];
};

#endif // __MK2014_CLASS_TRIANGLE_H__