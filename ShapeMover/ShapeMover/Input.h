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

#ifndef __MANA2012_CLASS_INPUT_H__
#define __MANA2012_CLASS_INPUT_H__

// Library Includes
#include <map>

// Local Includes

// Types
struct tKeyState
{
	tKeyState::tKeyState()
	: bPressed(false), bComplete(false){}

	bool bPressed;
	bool bComplete;

};

// Constants

// Prototypes
class CSceneManager;

class CInput
{
	// Methods
public:
	CInput();
	~CInput();

	// Sets up input manager with a reference to the game so it can update if necessary
	bool Initialise();

	// Processes input and takes action
	void Process(const float _kfDeltaTick);

	void SetKeyPress(int _iKeyPressed);
	void SetKeyRelease(int _iKeyRelease);
	std::map<int, std::pair<bool, bool>> GetKeyCommands();

	// Set bool to true if you only want to read the input once
	bool IsKeyPressed(int _iKeyPressed, bool _bOnce = false);

	void SetMousePos(float _fX, float _fY);
	void GetMousePos(float& _rfX, float& _rfY);
	float GetMousePosX();
	float GetMousePosY();
	void SetMouseButtonUp(bool _b);
	void SetMouseButtonDown(bool _b);
	bool IsMouseKeyDown();
	bool IsMouseKeyUp();

protected:

private:
	CInput(const CInput& _kr);
	CInput& operator= (const CInput& _kr);

	// Members
public:


protected:

private:
	std::map<int, tKeyState> m_mapKeysPressed;

	bool m_bMouseDown;
	bool m_bMouseUp;
	float m_fMousePosX;
	float m_fMousePosY;

};

#endif // __MANA2012_CLASS_INPUT_H__