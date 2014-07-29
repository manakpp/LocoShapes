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

#ifndef __MANA2012_INTERFACE_SCENE_H__
#define __MANA2012_INTERFACE_SCENE_H__

// Library Includes
#include <map>
#include <Windows.h>
#include <objidl.h>
#include <GdiPlus.h>

// Local Includes

// Types

// Constants
static const float fBUTTON_OFFSETY = 25.0f;

// Prototypes
class IRenderer;
class CButton;

class CScene
{
	// Member Functions
public:
	CScene();
	virtual ~CScene();
	
	virtual bool Initialise() = 0;
	virtual void Process(const float _kfDeltaTick) = 0;
	virtual void Render(IRenderer& _rRenderer) = 0;
	virtual void ProcessButtonMessage(const int _kiID) = 0;

	bool UpdateButtons(float _fDeltaTick);
	void RenderButtons(IRenderer& _rRenderer);
	void AddButton(int _iID, const char* _strTitle, float _fX, float _fY, float _fWidth, float _fHeight);
	bool RemoveButton(int _iID);
	bool SetButtonPos(int _iID, float _fX, float _fY, float _fWidth, float _fHeight);
	bool IsButtonPressed();
	int GetButtonPressedID();
	void SetButtonState(int _iID, int _iState);

protected:

private:
	CScene(const CScene& _kr);
	CScene& operator= (const CScene& _kr);


	// Member Variables
public:

protected:
	bool m_bServer;
	std::map<int, CButton*>::iterator m_iterButton;
	std::map<int, CButton*> m_mapButton;
	int m_iButtonPressed;
	bool m_bButtonPressed;

private:

};

#endif // __MANA2012_INTERFACE_SCENE_H__