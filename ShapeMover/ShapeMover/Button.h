// 
//  Bachelor of Software Engineering
//  Media Design School
//  Auckland
//  New Zealand
// 
//  Copyright (c) 2012 Media Design School
// 
//  Author:	Mana Khamphanpheng
// 
// SVN Info
// $Author$
// $Date$
// $Rev$
// 

#pragma once

#ifndef __MANA2012_CLASS_BUTTON_H__
#define __MANA2012_CLASS_BUTTON_H__

// Library Includes
#include <Windows.h>

// Local Includes
#include "Rect.h"

// Types
enum EButtonState
{
	BUTTON_IDLE = 0,
	BUTTON_MOUSE_OVER,
	BUTTON_DOWN,
	BUTTON_PRESSED, // Release
	BUTTON_MAX
};

// Constants

// Prototypes
class IRenderer;
struct TColour;

class CButton
{
	// Member Functions
public:
	CButton();
	~CButton();

	bool Initialise(const char* _strTitle, const TRect& _krRect, const int _kiButtonID);
	bool Process(const float _kfDeltaTick);
	void Render(IRenderer& _rRenderer);

	void SetRect(const TRect& _krRect);
	void SetState(const int _kiState);

	bool IsPressed() const;
	int GetID() const;

protected:
	
private:
	CButton(const CButton& _kr);
	CButton& operator= (const CButton& _kr);


	// Member Variables
public:

protected:

private:
	const char* m_strLabel;
	int m_iID;
	
	TRect m_Rect;

	EButtonState m_eState;

	static TColour s_iBrush[BUTTON_MAX];
	
};

#endif // __MANA2012_CLASS_BUTTON_H__