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

// Library Includes
#include <Windows.h>

// Local Includes
#include "GDIRenderer.h"
#include "SceneManager.h"

// This Include
#include "Input.h"

// Static Variables


CInput::CInput()
: m_bMouseDown(0.0f)
, m_bMouseUp(0.0f)
, m_fMousePosX(0.0f)
, m_fMousePosY(0.0f)
{
	// Empty
}

CInput::~CInput()
{
}

bool
CInput::Initialise()
{
	return(true);
}

void
CInput::Process(const float _kfDeltaTick)
{
	//m_bMouseDown = false;
	m_bMouseUp = false;
}

void
CInput::SetKeyPress(int _iKeyPressed)
{
	m_mapKeysPressed[_iKeyPressed].bPressed = true;
}

void
CInput::SetKeyRelease(int _iKeyReleased)
{
	m_mapKeysPressed[_iKeyReleased].bPressed = false;
	m_mapKeysPressed[_iKeyReleased].bComplete = false;
}

bool CInput::IsKeyPressed(int _iKeyPressed, bool _bOnce)
{
	if(_bOnce)
	{
		if(m_mapKeysPressed[_iKeyPressed].bPressed && !m_mapKeysPressed[_iKeyPressed].bComplete)
		{
			m_mapKeysPressed[_iKeyPressed].bComplete = true; // set the second to 
			return(true);
		}
		return(false);
	}
	
	return(m_mapKeysPressed[_iKeyPressed].bPressed);
}

void CInput::SetMousePos(float _fX, float _fY)
{
	m_fMousePosX = _fX;
	m_fMousePosY = _fY;
}

void CInput::GetMousePos(float& _rfX, float& _rfY)
{
	_rfX = m_fMousePosX; 
	_rfY = m_fMousePosY;
}

float CInput::GetMousePosX()
{
	return(m_fMousePosX);
}

float CInput::GetMousePosY()
{
	return(m_fMousePosY);
}

void CInput::SetMouseButtonUp(bool _b)
{
	m_bMouseUp = _b;
}

void CInput::SetMouseButtonDown(bool _b)
{
	m_bMouseDown = _b;
}

bool CInput::IsMouseKeyDown()
{
	return(m_bMouseDown);
}

bool CInput::IsMouseKeyUp()
{
	return(m_bMouseUp);
}