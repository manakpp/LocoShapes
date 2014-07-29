// 
// File: CircularShapeMover.cpp
// Desc: Implementation of CircularShapeMover
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <assert.h>

// Local Includes
#include "Renderer.h"
#include "Shape.h"
#include "Vector2.h"

// This Include
#include "CircularShapeMover.h"

// Static Variables


// Default Constructor
CCircularShapeMover::CCircularShapeMover()
: m_fRadius(0.0f)
, m_fAngle(0.0f)
{
	
}

// Default Destructor
CCircularShapeMover::~CCircularShapeMover()
{
	
}

bool CCircularShapeMover::Initialise(CShape* _pShape, const float _kfSpeed, const float _kfRadius)
{
	assert(_pShape);

	m_pShape = _pShape;
	m_fSpeed = _kfSpeed;
	m_fRadius = _kfRadius;

	m_v2InitialPosition = _pShape->GetPosition();

	return true;
}

void CCircularShapeMover::Process(float _fDeltaTick)
{
	m_fAngle += m_fSpeed * _fDeltaTick; 

	float fX = m_v2InitialPosition.x + cos(m_fAngle) * m_fRadius;
	float fY = m_v2InitialPosition.y + sin(m_fAngle) * m_fRadius;

	m_pShape->SetPosition(fX, fY);

	m_pShape->Process(_fDeltaTick);
}

void CCircularShapeMover::Render(IRenderer& _rRenderer)
{
	m_pShape->Render(_rRenderer);
}

