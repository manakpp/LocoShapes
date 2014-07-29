// 
// File: Vector3.cpp
// Desc: Implementation of Vector3
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes

// Local Includes
#include "Vector2.h"

// This Include
#include "Vector3.h"

// Static Variables


// Default Constructor
TVector3::TVector3()
: x(0.0f)
, y(0.0f)
, z(0.0f)
{
	
}

TVector3::TVector3(const float _x, const float _y, const float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

TVector3::TVector3(const TVector2& _kr, const float _z)
{
	x = _kr.x;
	y = _kr.y;
	z = _z;
}

TVector3::TVector3(const TVector3& _kr)
{
	x = _kr.x;
	y = _kr.y;
	z = _kr.z;
}

// Default Destructor
TVector3::~TVector3()
{
	
}

TVector3& TVector3::operator =(const TVector3& _kr)
{
	x = _kr.x;
	y = _kr.y;
	z = _kr.z;

	return (*this);
}