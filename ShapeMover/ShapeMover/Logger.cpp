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
#include "LogTarget.h"
#include "LogFile.h"
#include "LogScreen.h"
#include "LogOutputWindow.h"

// This Include
#include "Logger.h"

// Static Variables
CLogger* CLogger::s_pLogger = 0;


// Default Constructor
CLogger::CLogger()
{
	
}

// Default Destructor
CLogger::~CLogger()
{
	while(!m_vecLogTargets.empty())
	{
		ILogTarget* pTarget = m_vecLogTargets.back();
		delete pTarget;
		pTarget = 0;
		m_vecLogTargets.pop_back();
	}
}

CLogger& CLogger::GetInstance()
{
	if(!s_pLogger)
	{
		s_pLogger = new CLogger();
	}
	return(*s_pLogger);
}

void  CLogger::DestroyInstance()
{
	delete s_pLogger;
	s_pLogger = 0;
}

void CLogger::AddLogTarget(ILogTarget* _pTarget)
{
	if(_pTarget)
	{
		m_vecLogTargets.push_back(_pTarget);
	}
}

void CLogger::AddScreenLogTarget(RECT& _rRect, unsigned int _uiFormatFlags, float _fRed, float _fGreen, float _fBlue)
{
	CLogScreen* pScreenLog = new CLogScreen(); 
	pScreenLog->Initialise(_rRect, _uiFormatFlags, _fRed, _fGreen, _fBlue);
	m_vecLogTargets.push_back(pScreenLog);
}

void CLogger::AddFileLogTarget(std::string _strFileName)
{
	// TODO: Add indexable files so that messages can be sent to files
	CLogFile* pFileLog = new CLogFile();
	pFileLog->Initialise(_strFileName);
	m_vecLogTargets.push_back(pFileLog);
}

void CLogger::AddOutputWindowLogTarget()
{
	CLogOutputWindow* pLogWindow = new CLogOutputWindow();
	m_vecLogTargets.push_back(pLogWindow);

}

void CLogger::Process(float _fDeltaTick)
{
	for(unsigned int i = 0; i < m_vecLogTargets.size(); ++i)
	{
		m_vecLogTargets[i]->Process(_fDeltaTick);
	}
}


void CLogger::Log(std::string _strMessage, std::string _strFunction, unsigned int _uiLine)
{
	std::stringstream ss;
	ss << _strMessage << " | LINE: " << _uiLine  << " | FUNC: " << _strFunction;
	Write(ss.str());
}

void CLogger::Log(std::string _strMessage)
{
	Write(_strMessage);
}

void CLogger::Write(std::string _strMessage)
{	
	for(unsigned int i = 0; i < m_vecLogTargets.size(); ++i)
	{
		m_vecLogTargets[i]->Write(_strMessage);
	}
}

void CLogger::Render(IRenderer& _rRenderer)
{
	for(unsigned int i = 0; i < m_vecLogTargets.size(); ++i)
	{
		m_vecLogTargets[i]->Render(_rRenderer);
	}
}