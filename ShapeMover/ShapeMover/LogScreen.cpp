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
#include "SceneManager.h"
#include "GDIRenderer.h"

// This Include
#include "LogScreen.h"

// Static Variables
wchar_t*
ConvertToWString(const char* _kcpInput, wchar_t*& _wcprOutput)
{
	// Get input string length plus null terminator
	unsigned int uiStrLength =  static_cast<unsigned int>(strlen(_kcpInput)) + 1;


	// Create new wchar_t variable based on string length
	_wcprOutput = new wchar_t[uiStrLength];


	// Iterate through input string and copy characters
	for (unsigned int i = 0; i < uiStrLength; ++i)
	{
		_wcprOutput[i] = _kcpInput[i];
	}


	return (_wcprOutput);
}



// Default Constructor
CLogScreen::CLogScreen()
{
	
}

// Default Destructor
CLogScreen::~CLogScreen()
{
	while(!m_queOutputMessages.empty())
	{
		m_queOutputMessages.pop_front();
	}
}

bool CLogScreen::Initialise(RECT& _rRect, unsigned int _uiFormatFlags, float _fRed, float _fGreen, float _fBlue)
{
	m_iRed = static_cast<int>(_fRed * 255.0f);
	m_iGreen = static_cast<int>(_fGreen * 255.0f);
	m_iBlue = static_cast<int>(_fBlue * 255.0f);

	m_fFontOffsetY = 16.0f;
	//m_iFontID = CSceneManager::GetInstance().GetRenderer().MakeFont(m_iRed, m_iGreen, m_iBlue, 255, m_fFontOffsetY);
	m_iMaxLines = 5; // The max number of messages that may be Rendern
	m_iMaxMessages = 20; // Total messages that may be contained
	m_fTextLinger = 5.0f;

	return(true);
}

void CLogScreen::Process(float _fDeltaTick)
{
	for(unsigned int i = 0; i < m_queOutputMessages.size(); ++i)
	{
		m_queOutputMessages[i].fTimeElapsed += _fDeltaTick;
		if(m_queOutputMessages[i].fTimeElapsed > m_fTextLinger)
		{
			m_queOutputMessages.pop_back();
		}

		if((int)i > m_iMaxLines)
		{
			break;
		}
	}
}

void CLogScreen::Render(IRenderer& _rRenderer)
{
	for(unsigned int i = 0; i < m_queOutputMessages.size(); ++i)
	{
		float fAlpha = (m_fTextLinger - m_queOutputMessages[i].fTimeElapsed) / m_fTextLinger;

		//_rRenderer.SetFontColor(m_iFontID, m_iRed, m_iGreen, m_iBlue, (int)(fAlpha * 255.0f));
		//std::wstring wstrMessage(m_queOutputMessages[i].strMessage.begin(), m_queOutputMessages[i].strMessage.end());

		//_rRenderer.RenderAllignedText(wstrMessage.c_str(), RectF(5.0f, 5.0f + (m_fFontOffsetY * i), (float)_rRenderer.GetWidth(), (float)_rRenderer.GetHeight()), 1, 0, m_iFontID);
	}
}

void CLogScreen::Write(std::string _strMessage)
{
	// Adds new message to the queue of messages
	TScreenLog newMessage;
	newMessage.strMessage = _strMessage;
	newMessage.fTimeElapsed = 0.0f;

	// Check to see if the message que is full
	if((int)m_queOutputMessages.size() > m_iMaxMessages)
	{
		// It is so pop to make room
		m_queOutputMessages.pop_front();
	}

	m_queOutputMessages.push_back(newMessage);
}