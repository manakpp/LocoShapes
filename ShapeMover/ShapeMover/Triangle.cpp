// 
// File: Triangle.cpp
// Desc: Implementation of Triangle
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes

// Local Includes
#include "GDIRenderer.h"

// This Include
#include "Triangle.h"

// Static Variables


// Default Constructor
CTriangle::CTriangle()
{
	
}

// Default Destructor
CTriangle::~CTriangle()
{
	
}

bool CTriangle::Initialise(const float _kfX, const float _kfY, const float _kfSize, const unsigned int _kuiBorderColour, const unsigned int _kuiFillColour)
{
	CShape::Initialise(_kfX, _kfY, _kfSize * 0.55f, _kuiBorderColour, _kuiFillColour);
	UpdatePoints();

	return(true);
}

void CTriangle::Render(IRenderer& _rRenderer)
{
	_rRenderer.PushPenColour(m_uiBorderColour);
	_rRenderer.PushBrushColour(m_uiFillColour);
	_rRenderer.DrawPolygonFill(&m_points[0], 3, true);
	_rRenderer.PopBrushColour();
	_rRenderer.PopPenColour();
}

void CTriangle::UpdatePoints()
{
	for(int i = 0; i < 3; ++i)
	{
		// 2 * PI / 3 * i
		float fAngle = (2.0f * 3.14159265359f / 3.0f) * (i + 0.25f);
		
		m_points[i].x = m_fX + m_fSize * cos(fAngle);
		m_points[i].y = m_fY + m_fSize * sin(fAngle);
	}
}
