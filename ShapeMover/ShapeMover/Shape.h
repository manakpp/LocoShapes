//
// File:	Shape.h
// Desc:	Header of Shape
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_SHAPE_H__
#define __MK2014_CLASS_SHAPE_H__

// Library Includes

// Local Includes
#include "Object.h"

// Types
enum EShape
{
	None,

	Square,
	Circle,
	Triange,
	Hexagon,

	Max
};

// Constants

// Prototypes
struct TVector2;

class CShape : public IObject
{
	// Member Functions
public:
	CShape();
	virtual ~CShape();

	virtual bool Initialise(const float _kfX, const float _kfY, const float _kfSize, const unsigned int _kuiBorderColour = 0xFF000000, const unsigned int _kuiFillColour = 0xFF000000);
	virtual void Process(float _fDeltaTick);
	virtual void Render(IRenderer& _rRenderer);

	virtual void UpdatePoints();

	void SetPosition(const float _kfX, const float _kfY);
	TVector2 GetPosition() const;

protected:

private:
	CShape(const CShape& _kr);
	CShape& operator= (const CShape& _kr);


	// Member Variables
public:

protected:
	float m_fSize;

	unsigned int m_uiFillColour;
	unsigned int m_uiBorderColour;

private:


};

#endif // __MK2014_CLASS_SHAPE_H__