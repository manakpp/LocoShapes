//
// File:	ShapeMoverScene.h
// Desc:	Header of ShapeMoverScene
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_SHAPEMOVERSCENE_H__
#define __MK2014_CLASS_SHAPEMOVERSCENE_H__

// Library Includes
#include <vector>

// Local Includes
#include "Scene.h"

// Types

// Constants

// Prototypes
class CShape;
class CShapeMover;
class CINIParser;

class CShapeMoverScene: public CScene
{
	// Member Functions
public:
	CShapeMoverScene();
	virtual ~CShapeMoverScene();

	bool Initialise();
	void Process(const float _kfDeltaTick);
	void Render(IRenderer& _rRenderer);
	void ProcessButtonMessage(const int _kiID);

	void ClearScene();

	bool LoadSceneFromFile(const char* _strFile);
	bool LoadShape(CINIParser& _rParser, int _iShapeID);
	


protected:

private:
	CShapeMoverScene(const CShapeMoverScene& _kr);
	CShapeMoverScene& operator= (const CShapeMoverScene& _kr);


	// Member Variables
public:

protected:

private:
	std::vector<CShapeMover*> m_vecShapes;

	int m_iSelectedScene;


};

#endif // __MK2014_CLASS_SHAPEMOVERSCENE_H__