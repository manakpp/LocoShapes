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

TColour::TColour(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
	a = 1.0f;
}

TColour::TColour(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}


// Default Destructor
TColour::~TColour()
{
	
}

TColour& TColour::operator =(const TColour& _kr)
{
	r = _kr.r;
	g = _kr.g;
	b = _kr.b;
	a = _kr.a;

	return (*this);
}

unsigned long TColour::Value() const
{
	// From D3DX1math.inl
    unsigned int dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned int) (r * 255.0f + 0.5f);
    unsigned int dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned int) (g * 255.0f + 0.5f);
    unsigned int dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned int) (b * 255.0f + 0.5f);
    unsigned int dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned int) (a * 255.0f + 0.5f);

	return (dwA << AlphaShift) | (dwR << RedShift) | (dwG << GreenShift) | (dwB << BlueShift);
}


unsigned long TColour::MakeColour(float _r, float _g, float _b, float _a)
{
    unsigned int dwR = _r >= 1.0f ? 0xff : _r <= 0.0f ? 0x00 : (unsigned int) (_r * 255.0f + 0.5f);
    unsigned int dwG = _g >= 1.0f ? 0xff : _g <= 0.0f ? 0x00 : (unsigned int) (_g * 255.0f + 0.5f);
    unsigned int dwB = _b >= 1.0f ? 0xff : _b <= 0.0f ? 0x00 : (unsigned int) (_b * 255.0f + 0.5f);
    unsigned int dwA = _a >= 1.0f ? 0xff : _a <= 0.0f ? 0x00 : (unsigned int) (_a * 255.0f + 0.5f);

	return (dwA << AlphaShift) | (dwR << RedShift) | (dwG << GreenShift) | (dwB << BlueShift);
}

unsigned long TColour::MakeColour(int _r, int _g, int _b, int _a)
{
	float r = ClampColourRange(_r) / 255.0f;
	float g = ClampColourRange(_g) / 255.0f;
	float b = ClampColourRange(_b) / 255.0f;
	float a = ClampColourRange(_a) / 255.0f;

    unsigned int dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (unsigned int) (r * 255.0f + 0.5f);
    unsigned int dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (unsigned int) (g * 255.0f + 0.5f);
    unsigned int dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (unsigned int) (b * 255.0f + 0.5f);
    unsigned int dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (unsigned int) (a * 255.0f + 0.5f);

	return (dwA << AlphaShift) | (dwR << RedShift) | (dwG << GreenShift) | (dwB << BlueShift);
}

float TColour::GetColourComponentF(const unsigned long& _kuiColour, EColourComponent _component)
{
    return ((_kuiColour & 0xFF << _component) >> _component) / 255.0f;     
}

int TColour::GetColourComponent(const unsigned long& _kuiColour, EColourComponent _component)
{
    return ((_kuiColour & 0xFF << _component) >> _component);     
}

unsigned long TColour::TryParse(const char* _strColour)
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

int TColour::ClampColourRange(int _iColor)
{
	if(_iColor < 0)
		_iColor = 0;
	else if(_iColor > 255)
		_iColor = 255;
	return _iColor;
}