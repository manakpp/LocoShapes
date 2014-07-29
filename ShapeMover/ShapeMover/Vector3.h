//
// File:	Vector3.h
// Desc:	Header of Vector3
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_VECTOR3_H__
#define __MK2014_CLASS_VECTOR3_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
struct TVector2;

struct TVector3
{
	// Member Functions
public:
	TVector3();	
	TVector3(const float _x, const float _y, const float _z = 0.0f);
	TVector3(const TVector2& _kr, const float _z = 0.0f);
	TVector3(const TVector3& _kr);

	~TVector3();

	float Magnitude() const;
	float MagnitudeSquare() const;

	float Distance(const TVector3& _kvrTarget) const;
	float DistanceSquare(const TVector3& _kvrTarget) const;

	void Normalise();

	TVector3 Normal() const;

	// Assignment operator 
	TVector3& operator= (const TVector3& _kr);

	// Plus minus operations
	TVector3 operator +(const TVector3& _kr) const;
	TVector3 operator -(const TVector3& _kr) const;
	TVector3 operator *(const TVector3& _kr) const;
	TVector3 operator /(const TVector3& _kr) const;

	// Relational operations
	bool operator ==(const TVector3& _kr) const;
	bool operator !=(const TVector3& _kr) const;

	// Multiplication and division by scalar
	TVector3 operator *(float _fScalar) const;
	TVector3 operator /(float _fScalar) const;

	// Combined assignment operations
	TVector3& operator +=(const TVector3& _kr);
	TVector3& operator -=(const TVector3& _kr);
	TVector3& operator *=(const TVector3& _kr);
	TVector3& operator /=(const TVector3& _kr);

	// Unary
	TVector3 operator -() const;
	bool operator !() const;
	bool IsZero() const;

	void Zero();

protected:

private:
	

	// Member Variables
public:
	float x;
	float y; 
	float z;

protected:

private:


};

#endif // __MK2014_CLASS_VECTOR3_H__