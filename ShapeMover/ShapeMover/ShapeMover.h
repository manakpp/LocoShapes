//
// File:	ShapeMover.h
// Desc:	Header of ShapeMover
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_SHAPEMOVER_H__
#define __MK2014_CLASS_SHAPEMOVER_H__

// Library Includes

// Local Includes
#include "Vector2.h"

// Types

// Constants

// Prototypes
class IRenderer;
class CShape;

class CShapeMover
{
	// Member Functions
public:
	CShapeMover();
	virtual ~CShapeMover();

	bool Initialise(CShape* _pShape);

	virtual void Process(float _fDeltaTick);
	virtual void Render(IRenderer& _rRenderer);

	static CShapeMover* CreateWaypointMover(CShape* _pShape, const float _kfSpeed, TVector2* _pv2PathPoints, const unsigned int _kuiPoints);
	static CShapeMover* CreateCircularMover(CShape* _pShape, const float _kfSpeed, const float _kfRadius);
	static CShapeMover* CreateStaticShape(CShape* _pShape);

protected:

private:
	CShapeMover(const CShapeMover& _kr);
	CShapeMover& operator= (const CShapeMover& _kr);


	// Member Variables
public:

protected:
	TVector2 m_v2InitialPosition;

	CShape* m_pShape;

	float m_fSpeed;

private:


};

#endif // __MK2014_CLASS_SHAPEMOVER_H__