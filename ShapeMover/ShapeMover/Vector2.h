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

#pragma once

#ifndef __MANA2012_CLASS_TVector2_H__
#define __MANA2012_CLASS_TVector2_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes

struct TVector2
{
	// Member Functions
public:
	TVector2();
	TVector2(float _x, float _y);
	TVector2(const TVector2& _kr);
	~TVector2();

	float Magnitude() const;
	float MagnitudeSquare() const;

	float Distance(const TVector2& _kvrTarget) const;
	float DistanceSquare(const TVector2& _kvrTarget) const;

	void Normalise();

	TVector2 Normal() const;

	// Assignment operator 
	TVector2& operator= (const TVector2& _kr);

	// Plus minus operations
	TVector2 operator +(const TVector2& _kr) const;
	TVector2 operator -(const TVector2& _kr) const;
	TVector2 operator *(const TVector2& _kr) const;
	TVector2 operator /(const TVector2& _kr) const;

	// Relational operations
	bool operator ==(const TVector2& _kr) const;
	bool operator !=(const TVector2& _kr) const;

	// Multiplication and division by scalar
	TVector2 operator *(float _fScalar) const;
	TVector2 operator /(float _fScalar) const;

	// Combined assignment operations
	TVector2& operator +=(const TVector2& _kr);
	TVector2& operator -=(const TVector2& _kr);
	TVector2& operator *=(const TVector2& _kr);
	TVector2& operator /=(const TVector2& _kr);

	// Unary
	TVector2 operator -() const;
	bool operator !() const;
	bool IsZero() const;

	void Zero();

protected:

private:

	// Member Variables
public:
	float x;
	float y;

protected:

private:

};

#endif // __MANA2012_CLASS_TVector2_H__