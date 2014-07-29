// 
// File: PathShapeMover.cpp
// Desc: Implementation of PathShapeMover
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <assert.h>

// Local Includes
#include "Renderer.h"
#include "Vector2.h"
#include "Shape.h"

// This Include
#include "PathShapeMover.h"

// Static Variables


// Default Constructor
CPathShapeMover::CPathShapeMover()
: m_pPathPoints(0)
, m_iPointsCount(0)
, m_iCurrentPoint(0)
{
	
}

// Default Destructor
CPathShapeMover::~CPathShapeMover()
{
	delete[] m_pPathPoints;
	m_pPathPoints = 0;
}

bool CPathShapeMover::Initialise(CShape* _pShape, const float _kfSpeed, TVector2* _pv2PathPoints, const unsigned int _kuiPoints)
{
	assert(_pShape);
	assert(_pv2PathPoints);

	m_pShape = _pShape;
	m_fSpeed = _kfSpeed;
	m_pPathPoints = _pv2PathPoints;
	m_iPointsCount = _kuiPoints;

	m_v2InitialPosition = _pShape->GetPosition();

	return(true);
}

void CPathShapeMover::Process(float _fDeltaTick)
{
	// Find the path given the current point and next point
	int nextPathIndex = m_iCurrentPoint;

	nextPathIndex += 1;
	if(nextPathIndex > m_iPointsCount - 1)
	{
		nextPathIndex = 0;
	}

	TVector2 currentPoint = m_pPathPoints[m_iCurrentPoint];
	TVector2 nextPoint = m_pPathPoints[nextPathIndex];

	TVector2 position = m_pShape->GetPosition();

	// Check if the shape is near the end of the path
	if(position.x > nextPoint.x - 0.5f &&
		position.x < nextPoint.x + 0.5f &&
		position.y > nextPoint.y - 0.5f &&
		position.y < nextPoint.y + 0.5f)
	{
		m_iCurrentPoint++;
		if(m_iCurrentPoint > m_iPointsCount)
			m_iCurrentPoint = 0;
	}

	TVector2 direction = (nextPoint - currentPoint).Normal();

	float fX = position.x + direction.x * m_fSpeed * _fDeltaTick;
	float fY = position.y + direction.y * m_fSpeed * _fDeltaTick;

	m_pShape->SetPosition(fX, fY);

	m_pShape->Process(_fDeltaTick);
}

void CPathShapeMover::Render(IRenderer& _rRenderer)
{
	m_pShape->Render(_rRenderer);
}

