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
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>

// Local Includes
#include "Logger.h"
#include "Input.h"
#include "Scene.h"
#include "ShapeMoverScene.h"
#include "Renderer.h"
#include "GDIRenderer.h"

// This Include
#include "SceneManager.h"

// Static Variables
CSceneManager* CSceneManager::s_pContext = 0;


// Default Constructor
CSceneManager::CSceneManager()
: m_eCurrentScene(eSCENE_INVALID)
{
	
}

// Default Destructor
CSceneManager::~CSceneManager()
{
	for(int i = eSCENE_INVALID; i < eSCENE_MAX; ++i)
	{
		if(m_mapScenes[(eSCENE)i])
		{
			delete m_mapScenes[(eSCENE)i];
			m_mapScenes[(eSCENE)i] = 0;
		}
	}

	// Clean up the logger
	CLogger::DestroyInstance();
}

CSceneManager& CSceneManager::GetInstance()
{
	if(!s_pContext)
	{
		s_pContext = new CSceneManager();
	}
	return(*s_pContext);
}

void CSceneManager::DestroyInstance()
{
	delete s_pContext;
	s_pContext = 0;
}

bool CSceneManager::Initialise(HINSTANCE _hInstance, const char* _strTile, int _iClientWidth, int _iClientHeight)
{
	srand((unsigned int)time(0));

	if(!CWin32App::Initialise(_hInstance, _strTile, _iClientWidth, _iClientHeight))
	{
		return(false);
	}

	// Init Input
	m_pInput = new CInput;
	
	// Init Logger
	CLogger::GetInstance().AddOutputWindowLogTarget();
	RECT rect = {15, 15, 100, 100};
	CLogger::GetInstance().AddScreenLogTarget(rect, 0, 0.0f, 0.0f, 0.0f);

	SetScene(eSCENE_DEFAULT);

	return(true);
}

void CSceneManager::Process(float _fDeltaTick)
{
	// This stuff needs to happen
	CLogger::GetInstance().Process(_fDeltaTick);
	UpdateFrameStats(_fDeltaTick);

	// Now update the game
	m_mapScenes[m_eCurrentScene]->Process(_fDeltaTick);

	m_pInput->Process(_fDeltaTick);
}

void CSceneManager::Render(IRenderer& _rRenderer)
{
	_rRenderer.Clear(0);
	
	// Render the game (everyone does this the same)
	m_mapScenes[m_eCurrentScene]->Render(_rRenderer);

	// This stuff needs to happen (render last so we see the stats)
	CLogger::GetInstance().Render(_rRenderer);
	RenderFrameStats(_rRenderer);

	_rRenderer.Present();
}

void CSceneManager::SetScene(eSCENE _eSCENE, bool _bRemovePrev)
{
	if(m_mapScenes[_eSCENE] != 0)
		return;
	
	// It doesnt so make it!
	switch(_eSCENE)
	{
	case eSCENE_DEFAULT:
		{
			m_mapScenes[_eSCENE] = new CShapeMoverScene();
			m_mapScenes[_eSCENE]->Initialise();
		}
		break;
	default:
		{
			LOG_MSG("Unhandled case");
		}
		break;
	}
	
	if(_bRemovePrev)
	{
		if(m_mapScenes[m_eCurrentScene])
		{
			delete m_mapScenes[m_eCurrentScene];
			m_mapScenes[m_eCurrentScene] = 0;
		}
	}
	
	m_eCurrentScene = _eSCENE;
}

IRenderer& CSceneManager::GetRenderer()
{
	return(*m_pRenderer);
}

CInput& CSceneManager::GetInput()
{
	return(*m_pInput);
}