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

#ifndef __MANA2012_CLASS_CONTEXT_H__
#define __MANA2012_CLASS_CONTEXT_H__


// Library Includes
#include <map>

// Local Includes
#include "Win32App.h"


// Types
typedef enum eSCENE
{
	eSCENE_INVALID = 0,
	eSCENE_DEFAULT,
	eSCENE_MAX

} eSCENE;

// Constants

// Prototypes
class CScene;
class CPlayerList;

class CSceneManager: public CWin32App
{
	// Member Functions
public:
	virtual ~CSceneManager();

	static CSceneManager& GetInstance();
	static void DestroyInstance();

	bool Initialise(HINSTANCE _hInstance, const char* _strTile, int _iClientWidth, int _iClientHeight);
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer); 

	void SetScene(eSCENE _eSCENE, bool _bRemovePrev = false);
	IRenderer& GetRenderer();

	void LogToScene(std::string _str);

	CInput& GetInput();
	

protected:

private:
	CSceneManager();
	CSceneManager(const CSceneManager& _kr);
	CSceneManager& operator= (const CSceneManager& _kr);

	// Member Variables
public:

protected:

private:
	static CSceneManager* s_pContext;
	eSCENE m_eCurrentScene;
	std::map<eSCENE, CScene*> m_mapScenes;

};

#endif // __MANA2012_CLASS_CONTEXT_H__