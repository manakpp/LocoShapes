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

#ifndef __MANA2012_CLASS_LOGGER_H__
#define __MANA2012_CLASS_LOGGER_H__

// Library Includes
#include <vector>
#include <string>
#include <Windows.h>

// Local Includes

// Types

// Constants

// Prototypes
class IRenderer;
class ILogTarget;

#define LOG_MSG(MESSAGE) { CLogger::GetInstance().Log(MESSAGE, __FUNCTION__, __LINE__); };

class CLogger
{
	// Member Functions
public:
	~CLogger();

	static CLogger& GetInstance();
	static void DestroyInstance();

	void AddScreenLogTarget(RECT& _rRect, unsigned int _uiFormatFlags, float _fRed, float _fGreen, float _fBlue);
	void AddFileLogTarget(std::string _strFileName);
	void AddOutputWindowLogTarget();
	void Process(float _fDeltaTick);
	void Log(std::string _strMessage, std::string _strFunction, unsigned int _uiLine);
	void Log(std::string _strMessage);
	void Write(std::string _strMessage);
	void Render(IRenderer& _rRenderer);
	void AddLogTarget(ILogTarget* _pTarget);

protected:

private:
	CLogger();
	CLogger(const CLogger& _kr);
	CLogger& operator= (const CLogger& _kr);


	// Member Variables
public:

protected:

private:
	static CLogger* s_pLogger;
	std::vector<ILogTarget*> m_vecLogTargets;

};

#endif // __MANA2012_CLASS_LOGGER_H__