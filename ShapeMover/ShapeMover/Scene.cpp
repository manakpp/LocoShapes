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

// Local Includes
#include "Button.h"

// This Include
#include "Scene.h"

// Static Variables


// Default Constructor
CScene::CScene()
: m_bButtonPressed(false)
, m_iButtonPressed(-1)
{
	
}

// Default Destructor
CScene::~CScene()
{
	while(!m_mapButton.empty())
	{
		m_iterButton = m_mapButton.begin();
		delete m_iterButton->second;
		m_iterButton->second = 0;
		m_mapButton.erase(m_iterButton);
	}
}

bool CScene::UpdateButtons(float _fDeltaTick)
{
	for(m_iterButton = m_mapButton.begin(); m_iterButton != m_mapButton.end(); ++m_iterButton)
	{
		if(m_iterButton->second->Process(_fDeltaTick))
		{
			m_iButtonPressed = m_iterButton->second->GetID();
			m_bButtonPressed = true;
			return(true);
		}
	}
	return(false);
}

void CScene::RenderButtons(IRenderer& _rRenderer)
{
	for(m_iterButton = m_mapButton.begin(); m_iterButton != m_mapButton.end(); ++m_iterButton)
	{
		m_iterButton->second->Render(_rRenderer);
	}
}

void CScene::AddButton(int _iID, const char* _strTitle, float _fX, float _fY, float _fWidth, float _fHeight)
{
	if(!m_mapButton[_iID])
	{
		TRect rect(_fX, _fY , _fWidth, _fHeight);
		CButton* pButton = new CButton();
		pButton->Initialise(_strTitle, rect, _iID);
		m_mapButton[_iID] = pButton;
	}
}

bool CScene::RemoveButton(int _iID)
{
	if(!m_mapButton.empty())
	{
		for(m_iterButton = m_mapButton.begin(); m_iterButton != m_mapButton.end(); ++m_iterButton);
		{
			if(m_iterButton->second->GetID() == _iID)
			{
				delete m_iterButton->second;
				m_iterButton->second = 0;
				m_mapButton.erase(m_iterButton);
				return true;
			}
		}
	}
	return(false);
}

bool CScene::SetButtonPos(int _iID, float _fX, float _fY, float _fWidth, float _fHeight)
{
	if(!m_mapButton.empty())
	{
		for(m_iterButton = m_mapButton.begin(); m_iterButton != m_mapButton.end(); ++m_iterButton);
		{
			if(m_iterButton->second->GetID() == _iID)
			{
				m_iterButton->second->SetRect(TRect(_fX, _fY, _fWidth, _fHeight));
				return true;
			}
		}
	}
	return(false);
}

bool CScene::IsButtonPressed()
{
	return(m_bButtonPressed);
}

int CScene::GetButtonPressedID()
{
	return(m_iButtonPressed);
}

void CScene::SetButtonState(int _iID, int _iState)
{
	m_mapButton[_iID]->SetState(_iState);
}