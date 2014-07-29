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

#ifdef _DEBUG
#include "vld.h" // Can leave this in release
#endif
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
				   PSTR _pstrCmdLine, int _iCommands)
{
	CSceneManager& theApp = CSceneManager::GetInstance();
	if(theApp.Initialise(_hInstance, L"Shape Mover" , 800, 600))
	{
		int iMsg = theApp.Run();

		CSceneManager::GetInstance().DestroyInstance();

		return(iMsg);
	}

	return 0;
}
