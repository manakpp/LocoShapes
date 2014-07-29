// 
// File: Hexagon.cpp
// Desc: Implementation of Hexagon
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <math.h>

// Local Includes
#include "GDIRenderer.h"
#include "Rect.h"
#include "Vector2.h"

// This Include
#include "Hexagon.h"

// Static Variables


// Default Constructor
CHexagon::CHexagon()
{
	
}

// Default Destructor
CHexagon::~CHexagon()
{
	
}

bool CHexagon::Initialise(const float _kfX, const float _kfY, const float _kfSize, const unsigned int _kuiBorderColour, const unsigned int _kuiFillColour)
{
	CShape::Initialise(_kfX, _kfY, _kfSize * 0.55f, _kuiBorderColour, _kuiFillColour);

	UpdatePoints();

	return(true);
}

void CHexagon::Process(float _fDeltaTick)
{
	CShape::Process(_fDeltaTick);

	UpdatePoints();
}

void CHexagon::Render(IRenderer& _rRenderer)
{
	_rRenderer.PushPenColour(m_uiBorderColour);
	_rRenderer.PushBrushColour(m_uiFillColour);
	_rRenderer.DrawPolygonFill(&m_points[0], 6, true);
	_rRenderer.PopBrushColour();
	_rRenderer.PopPenColour();
}

void CHexagon::UpdatePoints()
{
	for(int i = 0; i < 6; ++i)
	{
		// 2 * PI / 6 * i
		float fAngle = (2.0f * 3.14159265359f / 6.0f) * i;
		
		m_points[i].x = m_fX + m_fSize * cos(fAngle);
		m_points[i].y = m_fY + m_fSize * sin(fAngle);
	}
}