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

#ifndef __MANA2012_CLASS_LOGFILE_H__
#define __MANA2012_CLASS_LOGFILE_H__

// Library Includes
#include <vector>
#include <fstream>
#include <iostream>

// Local Includes
#include "LogTarget.h"

// Types

// Constants

// Prototypes


class CLogFile: public ILogTarget
{
	// Member Functions
public:
	CLogFile();
	virtual ~CLogFile();

	bool Initialise(std::string _strFileName);
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer);
	void Write(std::string _strMessage);

protected:

private:
	CLogFile(const CLogFile& _kr);
	CLogFile& operator= (const CLogFile& _kr);


	// Member Variables
public:

protected:

private:
	std::ofstream m_oFileStream;

};

#endif // __MANA2012_CLASS_LOGFILE_H__