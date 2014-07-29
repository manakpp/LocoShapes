//
// File:	Hexagon.h
// Desc:	Header of Hexagon
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_HEXAGON_H__
#define __MK2014_CLASS_HEXAGON_H__

// Library Includes

// Local Includes
#include "Shape.h"
#include "Vector2.h"

// Types

// Constants

// Prototypes

class CHexagon : public CShape
{
	// Member Functions
public:
	CHexagon();
	virtual ~CHexagon();

	virtual bool Initialise(const float _kfX, const float _kfY, const float _kfSize, const unsigned int _kuiBorderColour = 0xFF000000, const unsigned int _kuiFillColour = 0xFF000000);
	void Process(float _fDeltaTick);
	void Render(IRenderer& _rRenderer);

	void UpdatePoints();

protected:

private:
	CHexagon(const CHexagon& _kr);
	CHexagon& operator= (const CHexagon& _kr);


	// Member Variables
public:

protected:

private:
	TVector2 m_points[6];

};

#endif // __MK2014_CLASS_HEXAGON_H__