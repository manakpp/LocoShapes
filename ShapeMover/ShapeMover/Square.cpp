// 
// File: Square.cpp
// Desc: Implementation of Square
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
#include "Square.h"

// Static Variables


// Default Constructor
CSquare::CSquare()
{
	
}

// Default Destructor
CSquare::~CSquare()
{
	
}

void CSquare::Render(IRenderer& _rRenderer)
{
	_rRenderer.PushPenColour(m_uiBorderColour);
	_rRenderer.PushBrushColour(m_uiFillColour);
	_rRenderer.DrawRectangleFill(TVector2(m_fX, m_fY), m_fSize, m_fSize, true);
	_rRenderer.PopBrushColour();
	_rRenderer.PopPenColour();
}