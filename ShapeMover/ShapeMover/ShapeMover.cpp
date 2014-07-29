// 
// File: ShapeMover.cpp
// Desc: Implementation of ShapeMover
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <assert.h>

// Local Includes
#include "Renderer.h"
#include "CircularShapeMover.h"
#include "PathShapeMover.h"
#include "Shape.h"

// This Include
#include "ShapeMover.h"

// Static Variables


// Default Constructor
CShapeMover::CShapeMover()
: m_pShape(0)
, m_fSpeed(0.0f)
{
	
}

// Default Destructor
CShapeMover::~CShapeMover()
{
	delete m_pShape;
	m_pShape = 0;
}

bool CShapeMover::Initialise(CShape* _pShape)
{
	m_pShape = _pShape;

	return true;
}

void CShapeMover::Process(float _fDeltaTick)
{
	m_pShape->Process(_fDeltaTick);
}

void CShapeMover::Render(IRenderer& _rRenderer)
{
	m_pShape->Render(_rRenderer);
}

CShapeMover* CShapeMover::CreateWaypointMover(CShape* _pShape, const float _kfSpeed, TVector2* _pv2PathPoints, const unsigned int _kuiPoints)
{
	assert(_pShape);
	assert(_pv2PathPoints);
	assert(_kuiPoints > 1);

	CPathShapeMover* pShapeMover = new CPathShapeMover();
	pShapeMover->Initialise(_pShape, _kfSpeed, _pv2PathPoints, _kuiPoints);

	return pShapeMover;
}

CShapeMover* CShapeMover::CreateCircularMover(CShape* _pShape, const float _kfSpeed, const float _kfRadius)
{
	assert(_pShape);

	CCircularShapeMover* pShapeMover = new CCircularShapeMover();
	pShapeMover->Initialise(_pShape, _kfSpeed, _kfRadius);

	return pShapeMover;
}

CShapeMover* CShapeMover::CreateStaticShape(CShape* _pShape)
{
	assert(_pShape);

	CShapeMover* pShapeMover = new CShapeMover();
	pShapeMover->Initialise(_pShape);

	return pShapeMover;
}

