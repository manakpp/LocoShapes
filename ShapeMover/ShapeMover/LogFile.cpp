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
#include <Windows.h>

// Local Includes

// This Include
#include "LogFile.h"

// Static Variables


// Default Constructor
CLogFile::CLogFile()
{
	
}

// Default Destructor
CLogFile::~CLogFile()
{
	m_oFileStream.close();
}

bool CLogFile::Initialise(std::string _strFileName)
{
	m_oFileStream.open(_strFileName.c_str());
	if(!m_oFileStream.is_open())
	{
		// TODO: Msg box this problem
		return(false);
	}
	// Keep file open so messages can be written to
	return(true);
}

void CLogFile::Process(float _fDeltaTick)
{
	// Not used
}

void CLogFile::Render(IRenderer& _rRenderer)
{
	// Not used
}

void CLogFile::Write(std::string _strMessage)
{
	m_oFileStream << (_strMessage + "\n").c_str();
}