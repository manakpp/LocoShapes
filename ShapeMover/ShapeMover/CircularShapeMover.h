//
// File:	CircularShapeMover.h
// Desc:	Header of CircularShapeMover
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_CIRCULARSHAPEMOVER_H__
#define __MK2014_CLASS_CIRCULARSHAPEMOVER_H__

// Library Includes

// Local Includes
#include "ShapeMover.h"

// Types

// Constants

// Prototypes


class CCircularShapeMover : public CShapeMover
{
	// Member Functions
public:
	CCircularShapeMover();
	~CCircularShapeMover();

	bool Initialise(CShape* _pShape, const float _kfSpeed, const float _kfRadius);
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer);

protected:

private:
	CCircularShapeMover(const CCircularShapeMover& _kr);
	CCircularShapeMover& operator= (const CCircularShapeMover& _kr);


	// Member Variables
public:

protected:

private:
	float m_fRadius;
	float m_fAngle;


};

#endif // __MK2014_CLASS_CIRCULARSHAPEMOVER_H__