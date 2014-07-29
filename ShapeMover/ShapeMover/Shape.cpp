// 
// File: Shape.cpp
// Desc: Implementation of Shape
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes

// Local Includes
#include "Renderer.h"
#include "Vector2.h"

// This Include
#include "Shape.h"

// Static Variables


// Default Constructor
CShape::CShape()
{
	
}

// Default Destructor
CShape::~CShape()
{
	
}

bool CShape::Initialise(const float _kfX, const float _kfY, const float _kfSize, const unsigned int _kuiBorderColour, const unsigned int _kuiFillColour)
{
	m_fX = _kfX;
	m_fY = _kfY;

	m_fSize = _kfSize;

	m_uiBorderColour = _kuiBorderColour;
	m_uiFillColour = _kuiFillColour;

	return true;
}

void CShape::Process(float _fDeltaTick)
{

	// Update points after the shape has moved
	UpdatePoints();
}

void CShape::Render(IRenderer& _rRenderer)
{
	// to be derived
}


void CShape::UpdatePoints()
{
	// to be derived
}

void CShape::SetPosition(const float _kfX, const float _kfY)
{
	m_fX = _kfX;
	m_fY = _kfY;
}

TVector2 CShape::GetPosition() const
{
	return TVector2(m_fX, m_fY);
}