// 
// File: Colour.cpp
// Desc: Implementation of Colour
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes

// Local Includes
#include "Renderer.h"

// This Include
#include "Colour.h"

// Static Variables


// Default Constructor
TColour::TColour()
{
	
}

TColour::TColour(unsigned char _r, unsigned char _g, unsigned char _b)
{
	m_uiColour = MakeColour(_r, _g, _b, 255);
}

TColour::TColour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
	m_uiColour = MakeColour(_r, _g, _b, _a);
}


// Default Destructor
TColour::~TColour()
{
	
}

TColour& TColour::operator =(const TColour& _kr)
{
	m_uiColour = _kr.m_uiColour;

	return (*this);
}

unsigned int TColour::Value() const
{
	return m_uiColour;
}

unsigned int TColour::MakeColour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
	return (_a << 24) | (_r << 16) | (_g << 8) | _b;
}

unsigned int TColour::TryParse(const char* _strColour)
{
	if(strcmp(_strColour, "Black") == 0)
	{
		return Black;
	}
	else if(strcmp(_strColour, "White") == 0)
	{
		return White;
	}
	else if(strcmp(_strColour, "Red") == 0)
	{
		return Red;
	}
	else if(strcmp(_strColour, "Green") == 0)
	{
		return Green;
	}
	else if(strcmp(_strColour, "Blue") == 0)
	{
		return Blue;
	}
	else if(strcmp(_strColour, "Yellow") == 0)
	{
		return Yellow;
	}

	return Black;
}