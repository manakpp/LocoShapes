//
// File:	PathShapeMover.h
// Desc:	Header of PathShapeMover
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_PATHSHAPEMOVER_H__
#define __MK2014_CLASS_PATHSHAPEMOVER_H__

// Library Includes

// Local Includes
#include "ShapeMover.h"

// Types

// Constants

// Prototypes
class CShape;
struct TVector2;

class CPathShapeMover : public CShapeMover
{
	// Member Functions
public:
	CPathShapeMover();
	~CPathShapeMover();

	bool Initialise(CShape* _pShape, const float _kfSpeed, TVector2* _pv2PathPoints, const unsigned int _kuiPoints);
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer);

protected:

private:
	CPathShapeMover(const CPathShapeMover& _kr);
	CPathShapeMover& operator= (const CPathShapeMover& _kr);


	// Member Variables
public:

protected:

private:
	TVector2* m_pPathPoints;
	int m_iPointsCount;
	int m_iCurrentPoint;

};

#endif // __MK2014_CLASS_PATHSHAPEMOVER_H__