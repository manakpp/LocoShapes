//
// File:	Vertex.h
// Desc:	Header of Vertex
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_VERTEX_H__
#define __MK2014_CLASS_VERTEX_H__

// Library Includes
#include <Windows.h>

// Local Includes

// Types

// Constants

// Prototypes
struct TVector2;
struct TVector3;

struct TVertex
{
	// Member Functions
public:
	TVertex();
	TVertex(const TVector2& _kr, unsigned long colour = 0xFFFFFFFF);
	TVertex(const TVector3& _kr, unsigned long colour = 0xFFFFFFFF);
	TVertex(const float& _fX, const float& _fY, unsigned long colour = 0xFFFFFFFF);
	TVertex(const float& _fX, const float& _fY, const float& _fZ, unsigned long colour = 0xFFFFFFFF);

	~TVertex();

	TVertex(const TVertex& _kr);
	TVertex& operator= (const TVertex& _kr);

protected:

private:


	// Member Variables
public:
	float x;
	float y;
	float z;

	float r;
	float g;
	float b;
	float a;

protected:

private:

};

#endif // __MK2014_CLASS_VERTEX_H__