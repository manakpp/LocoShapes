//
// File:	Colour.h
// Desc:	Header of Colour
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_COLOUR_H__
#define __MK2014_CLASS_COLOUR_H__

// Library Includes

// Local Includes

// Types
enum EColourComponent
{
	AlphaShift  = 24,
	RedShift    = 16,
    GreenShift  = 8,
    BlueShift   = 0

} typedef EColourComponent;


enum EColourMask
{
    AlphaMask   = 0xff000000,
    RedMask     = 0x00ff0000,
    GreenMask   = 0x0000ff00,
    BlueMask    = 0x000000ff

} typedef EColourMask;


enum
{
    Black                = 0xFF000000, 
    Blue                 = 0xFF0000FF,
    Green                = 0xFF008000,
    Maroon               = 0xFF800000,
    Pink                 = 0xFFFFC0CB,
    Purple               = 0xFF800080,
    Red                  = 0xFFFF0000,
    Salmon               = 0xFFFA8072,
    Teal                 = 0xFF008080,
    White                = 0xFFFFFFFF,
    Yellow               = 0xFFFFFF00,
};

// Constants

// Prototypes


struct TColour
{
	// Member Functions
public:
	TColour();
	TColour(float _r, float _g, float _b);
	TColour(float _r, float _g, float _b, float _a);
	TColour(const unsigned int _kuiColour);

	TColour(const TColour& _kr);
	TColour& operator= (const TColour& _kr);

	~TColour();

	unsigned long Value() const;

	static unsigned long MakeColour(float _r, float _g, float _b, float _a);
	static unsigned long MakeColour(int _r, int _g, int _b, int _a);

	static float GetColourComponentF(const TColour& _krColour, EColourComponent _component);
	static int GetColourComponent(const TColour& _krColour, EColourComponent _component);

	static float GetColourComponentF(const unsigned long& _kuiColour, EColourComponent _component);
	static int GetColourComponent(const unsigned long& _kuiColour, EColourComponent _component);

	static unsigned long TryParse(const char* _strColour);

	static int ClampColourRange(int _iColor);

protected:

private:



	// Member Variables
public:

protected:

private:
	float r;
	float g;
	float b;
	float a;

};

#endif // __MK2014_CLASS_COLOUR_H__