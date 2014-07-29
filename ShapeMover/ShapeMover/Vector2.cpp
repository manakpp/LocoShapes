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

// Library Includes
#include <math.h>

// Local Includes
#include "Renderer.h"

// This Include
#include "Vector2.h"

// Static Variables


// Default Constructor
TVector2::TVector2()
: x(0.0f)
, y(0.0f)
{
	// Empty
}

TVector2::TVector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

TVector2::TVector2(const TVector2& _kr)
{
	x = _kr.x;
	y = _kr.y;
}

TVector2::~TVector2()
{
	// Empty
}

float
TVector2::Magnitude() const
{
	return (sqrt((x * x) + (y * y)));
}

float
TVector2::MagnitudeSquare() const
{
	return ((x * x) + (y * y));
}

float
TVector2::Distance(const TVector2& _kvrTarget) const
{
	return (((*this) - _kvrTarget).Magnitude() );
}

float
TVector2::DistanceSquare(const TVector2& _kvrTarget) const
{
	return (((*this) - _kvrTarget).MagnitudeSquare());
}

void
TVector2::Normalise()
{
	float fMagnitude = sqrt(x*x + y*y);
	if (fMagnitude)
	{
		x /= fMagnitude;
		y /= fMagnitude;
	}
}

TVector2 TVector2::Normal() const
{
	TVector2 normal;
	normal.x = x;
	normal.y = y;
	normal.Normalise();

	return normal;
}

// Assignment operator
TVector2&
TVector2::operator =(const TVector2& _kr)
{
	x = _kr.x;
	y = _kr.y;

	return (*this);
}

// Equality operator
bool
TVector2::operator ==(const TVector2&_kr) const
{
	return (x == _kr.x && y == _kr.y);
}

// Inequality operator
bool
TVector2::operator !=(const TVector2&_kr) const
{
	return (x != _kr.x && y != _kr.y);
}

// Unary minus returns the negative of the vector.
TVector2
TVector2::operator -() const
{
	return (TVector2(-x, -y));
}

// Binary +, addition vectors.
TVector2
TVector2::operator +(const TVector2& _kr) const
{
	return (TVector2(x + _kr.x, y + _kr.y));
}

// Binary -, subtract vectors.
TVector2
TVector2::operator -(const TVector2& _kr) const
{
	return (TVector2(x - _kr.x, y - _kr.y));
}

// Multiplication by scalar.
TVector2
TVector2::operator *(float _fScalar) const
{
	return (TVector2(x * _fScalar, y * _fScalar));
}

// Division by scalar.
// Precondition: _f must not be zero.
TVector2
TVector2::operator /(float _fScalar) const
{
	if(_fScalar == 0.0f)
	{
		return(TVector2(0.0f, 0.0f));
	}
	return (TVector2(x / _fScalar, y / _fScalar));
}

TVector2&
TVector2::operator +=(const TVector2& _kr)
{
	x += _kr.x;
	y += _kr.y;

	return (*this);
}

TVector2&
TVector2::operator -=(const TVector2& _kr)
{
	x -= _kr.x;
	y -= _kr.y;

	return (*this);
}

TVector2& TVector2::operator *=(const TVector2& _kr)
{
	x *= _kr.x;
	y *= _kr.y;

	return(*this);
}

TVector2& TVector2::operator /=(const TVector2& _kr)
{
	x /= _kr.x;
	y /= _kr.y;

	return(*this);
}

bool TVector2::IsZero() const
{
	return(x == 0.0f && y == 0.0f);
}

void TVector2::Zero()
{
	x = 0.0f;
	y = 0.0f;
}