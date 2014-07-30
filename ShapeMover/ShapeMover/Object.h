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

// Types

// Constants

// Prototypes
class IRenderer;

class IObject
{
	// Member Functions
public:
	IObject(){}
	virtual ~IObject(){}

	virtual void Process(float _fDeltaTick) = 0;
	virtual void Render(IRenderer& _rRenderer) = 0;

protected:

private:
	IObject(const IObject& _kr);
	IObject& operator= (const IObject& _kr);


	// Member Variables
public:

protected:
	float m_fX;
	float m_fY;

private:

};

#endif // __MANA2012_CLASS_OBJECT_H__