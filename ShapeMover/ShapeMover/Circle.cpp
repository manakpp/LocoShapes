// 
// File: Circle.cpp
// Desc: Implementation of Circle
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes

// Local Includes
#include "GDIRenderer.h"
#include "Rect.h"
#include "Vector2.h"

// This Include
#include "Circle.h"

// Static Variables


// Default Constructor
CCircle::CCircle()
{
	
}

// Default Destructor
CCircle::~CCircle()
{
	
}

void CCircle::Render(IRenderer& _rRenderer)
{
	_rRenderer.PushPenColour(m_uiBorderColour);
	_rRenderer.PushBrushColour(m_uiFillColour);
	_rRenderer.DrawEllipseFill(TVector2(m_fX, m_fY), m_fSize, m_fSize, true);	
	_rRenderer.PopBrushColour();	
	_rRenderer.PopPenColour();
}

