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

#ifndef __MANA2012_CLASS_LOGOUTPUTWINDOW_H__
#define __MANA2012_CLASS_LOGOUTPUTWINDOW_H__

// Library Includes

// Local Includes
#include "LogTarget.h"

// Types

// Constants

// Prototypes


class CLogOutputWindow: public ILogTarget
{
	// Member Functions
public:
	CLogOutputWindow();
	virtual ~CLogOutputWindow();

	bool Initialise();
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer);
	void Write(std::string _strMessage);

protected:

private:
	CLogOutputWindow(const CLogOutputWindow& _kr);
	CLogOutputWindow& operator= (const CLogOutputWindow& _kr);


	// Member Variables
public:

protected:

private:


};

#endif // __MANA2012_CLASS_LOGOUTPUTWINDOW_H__