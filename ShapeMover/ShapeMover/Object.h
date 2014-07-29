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

#ifndef __MANA2012_CLASS_OBJECT_H__
#define __MANA2012_CLASS_OBJECT_H__

// Library Includes

// Local Includes
#include "GDIRenderer.h"

// Types

// Constants

// Prototypes


class CObject
{
	// Member Functions
public:
	CObject();
	~CObject();

	bool Initialise();
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer);

protected:

private:
	CObject(const CObject& _kr);
	CObject& operator= (const CObject& _kr);


	// Member Variables
public:

protected:

private:


};

#endif // __MANA2012_CLASS_OBJECT_H__