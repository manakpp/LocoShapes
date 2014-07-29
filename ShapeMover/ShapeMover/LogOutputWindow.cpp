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
#include "LogOutputWindow.h"

// Static Variables


// Default Constructor
CLogOutputWindow::CLogOutputWindow()
{
	
}

// Default Destructor
CLogOutputWindow::~CLogOutputWindow()
{
	
}

bool CLogOutputWindow::Initialise()
{
	// Not Used
	return(true);
}

void CLogOutputWindow::Process(float _fDeltaTick)
{
	// Not Used
}

void CLogOutputWindow::Render(IRenderer& _rRenderer)
{
	// Not Used
}

void CLogOutputWindow::Write(std::string _strMessage)
{
	OutputDebugStringA((_strMessage + "\n").c_str());
}
