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

#ifndef __MANA2012_CLASS_LOG_H__
#define __MANA2012_CLASS_LOG_H__

// Library Includes
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class IRenderer;

class ILogTarget
{
	// Member Functions
public:
	ILogTarget(){}
	virtual ~ILogTarget(){}

	virtual void Process(float _fDeltaTick) = 0;
	virtual void Render(IRenderer& _rRenderer) = 0;
	virtual void Write(std::string _strMessage) = 0;

protected:

private:


	// Member Variables
public:

protected:

private:


};

#endif // __MANA2012_CLASS_LOG_H__