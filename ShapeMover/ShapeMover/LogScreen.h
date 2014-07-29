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

#ifndef __MANA2012_CLASS_LOGSCREEN_H__
#define __MANA2012_CLASS_LOGSCREEN_H__

// Library Includes
#include <string>
#include <deque>
#include <windows.h>

// Local Includes
#include "LogTarget.h"

// Types
struct TScreenLog
{
	std::string strMessage;
	float fTimeElapsed;

	TScreenLog::TScreenLog()
	: strMessage("")
	, fTimeElapsed(0.0f)
	{

	}
};

// Constants

// Prototypes


class CLogScreen: public ILogTarget
{
	// Member Functions
public:
	CLogScreen();
	virtual ~CLogScreen();

	bool Initialise(RECT& _rRect, unsigned int _uiFormatFlags, float _fRed, float _fGreen, float _fBlue);
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer);
	void Write(std::string _strMessage);

protected:

private:
	CLogScreen(const CLogScreen& _kr);
	CLogScreen& operator= (const CLogScreen& _kr);


	// Member Variables
public:

protected:

private:
	float m_fFontOffsetY;
	int m_iFontID;
	int m_iMaxLines; // The max number of messages that may be Rendern
	int m_iMaxMessages; // Total messages that may be contained
	float m_fTextLinger;
	int m_iRed;
	int m_iGreen;
	int m_iBlue;
	

	std::deque<TScreenLog> m_queOutputMessages;


};

#endif // __MANA2012_CLASS_LOGSCREEN_H__