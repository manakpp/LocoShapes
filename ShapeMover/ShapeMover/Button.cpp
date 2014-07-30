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
#include <sstream>

// Local Includes
#include "GDIRenderer.h"
#include "SceneManager.h"
#include "Input.h"
#include "LogScreen.h"
#include "Colour.h"
#include "Rect.h"

// This Include
#include "Button.h"

// Static Variables
TColour CButton::s_iBrush[BUTTON_MAX];

// Default Constructor
CButton::CButton()
: m_eState(BUTTON_IDLE)
, m_iID(-1)
{
	
}


// Default Destructor
CButton::~CButton()
{
}

bool CButton::Initialise(const char* _strTitle, const TRect& _krRect, const int _kiButtonID)
{
	// Create brushes
	s_iBrush[BUTTON_IDLE] = TColour(178, 34, 30, 255);
	s_iBrush[BUTTON_MOUSE_OVER] = TColour(210, 65, 30, 255);
	s_iBrush[BUTTON_DOWN] = TColour(100, 15, 15, 255);
	s_iBrush[BUTTON_PRESSED] = TColour(75, 25, 25, 255);

	m_strLabel = _strTitle;

	m_Rect = _krRect;
	m_iID = _kiButtonID;

	return(true);
}

bool CButton::Process(float _fDeltaTick)
{
	// Check for mouse XY intersection
	float fX;
	float fY;
	CSceneManager::GetInstance().GetInput().GetMousePos(fX, fY);

	if( fX > m_Rect.x1 &&
		fX < m_Rect.x2 &&
		fY > m_Rect.y1 &&
		fY < m_Rect.y2)
	{
		if(CSceneManager::GetInstance().GetInput().IsMouseKeyDown())
		{
			m_eState = BUTTON_DOWN;
		}
		else if(CSceneManager::GetInstance().GetInput().IsMouseKeyUp())
		{
			return(true);
		}
		else
		{
			m_eState = BUTTON_MOUSE_OVER;
		}	
	}
	else
	{
		m_eState = BUTTON_IDLE;
	}

	return(false);
}

void CButton::Render(IRenderer& _rRenderer)
{
	if(m_eState == BUTTON_MOUSE_OVER)
	{
		float fOffset = 2.5f;
		TRect offsetRect = TRect::OffsetRect(m_Rect, fOffset, fOffset);

		_rRenderer.PushBrushColour(s_iBrush[BUTTON_MOUSE_OVER].Value());
		_rRenderer.PushPenColour(0xFF000000);
		_rRenderer.DrawRectangleFill(offsetRect, true);
		_rRenderer.PrintAllignedTextF(m_strLabel, offsetRect, 1, 1);
		_rRenderer.PopPenColour();
		_rRenderer.PopBrushColour();
	}
	else if(m_eState == BUTTON_DOWN)
	{
		float fOffset = 5.0f;
		TRect offsetRect = TRect::OffsetRect(m_Rect, fOffset, fOffset);

		_rRenderer.PushPenColour(0xFF000000);
		_rRenderer.PushBrushColour(s_iBrush[BUTTON_DOWN].Value());
		_rRenderer.DrawRectangleFill(offsetRect, true);
		_rRenderer.PrintAllignedTextF(m_strLabel, offsetRect, 1, 1);
		_rRenderer.PopBrushColour();
		_rRenderer.PopPenColour();
	}
	else
	{
		_rRenderer.PushPenColour(0xFF000000);
		_rRenderer.PushBrushColour(s_iBrush[BUTTON_IDLE].Value());
		_rRenderer.DrawRectangleFill(m_Rect, true);
		_rRenderer.PrintAllignedTextF(m_strLabel, m_Rect, 1, 1);
		_rRenderer.PopPenColour();
		_rRenderer.PopBrushColour();
	}
}

bool CButton::IsPressed() const
{
	return(m_eState == BUTTON_PRESSED);
}

int CButton::GetID() const
{
	return(m_iID);
}

void CButton::SetRect(const TRect& _krRect)
{
	m_Rect = _krRect;
}

void CButton::SetState(int _iState)
{
	m_eState = (EButtonState)_iState;
}

