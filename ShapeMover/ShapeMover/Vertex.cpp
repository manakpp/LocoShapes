// 
// File: Vertex.cpp
// Desc: Implementation of Vertex
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes

// Local Includes
#include "Vector2.h"
#include "Vector3.h"
#include "Colour.h"

// This Include
#include "Vertex.h"

// Static Variables


// Default Constructor
TVertex::TVertex()
{
	
}

TVertex::TVertex(const TVector2& _kr, unsigned long colour)
{
	x = _kr.x;
	y = _kr.y;
	z = 0.0f;
	r = TColour::GetColourComponentF(colour, RedShift);
	g = TColour::GetColourComponentF(colour, GreenShift);
	b = TColour::GetColourComponentF(colour, BlueShift);
	a = TColour::GetColourComponentF(colour, AlphaShift);
}

TVertex::TVertex(const TVector3& _kr, unsigned long colour)
{
	x = _kr.x;
	y = _kr.y;
	z = _kr.z;
	r = TColour::GetColourComponentF(colour, RedShift);
	g = TColour::GetColourComponentF(colour, GreenShift);
	b = TColour::GetColourComponentF(colour, BlueShift);
	a = TColour::GetColourComponentF(colour, AlphaShift);
}

TVertex::TVertex(const float& _fX, const float& _fY, unsigned long colour)
{
	x = _fX;
	y = _fY;
	z = 0.0f;
	r = TColour::GetColourComponentF(colour, RedShift);
	g = TColour::GetColourComponentF(colour, GreenShift);
	b = TColour::GetColourComponentF(colour, BlueShift);
	a = TColour::GetColourComponentF(colour, AlphaShift);
}

TVertex::TVertex(const float& _fX, const float& _fY, const float& _fZ, unsigned long colour)
{
	x = _fX;
	y = _fY;
	z = _fZ;
	r = TColour::GetColourComponentF(colour, RedShift);
	g = TColour::GetColourComponentF(colour, GreenShift);
	b = TColour::GetColourComponentF(colour, BlueShift);
	a = TColour::GetColourComponentF(colour, AlphaShift);;
}

TVertex& TVertex::operator =(const TVertex& _kr)
{
	x = _kr.x;
	y = _kr.y;
	z = _kr.z;
	r = _kr.r;
	g = _kr.g;
	b = _kr.b;
	a = _kr.a;

	return (*this);
}


// Default Destructor
TVertex::~TVertex()
{
	
}
