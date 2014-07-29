// 
// File: ShapeMoverScene.cpp
// Desc: Implementation of ShapeMoverScene
// 
//  Author:	Mana Khamphanpheng
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <vector>
#include <sstream>

// Local Includes
#include "GDIRenderer.h"
#include "Colour.h"
#include "INIParser.h"

// This Include
#include "ShapeMoverScene.h"
#include "Shape.h"
#include "Square.h"
#include "Triangle.h"
#include "Circle.h"
#include "Hexagon.h"
#include "ShapeMover.h"

// Static Variables


// Default Constructor
CShapeMoverScene::CShapeMoverScene()
{
	
}

// Default Destructor
CShapeMoverScene::~CShapeMoverScene()
{
	ClearScene();
}

bool CShapeMoverScene::Initialise()
{
	AddButton(0, "Reload from file 1", 10.0f, 10.0f, 100.0f, 50.0f);
	AddButton(1, "Reload from file 2", 10.0f, 70.0f, 100.0f, 50.0f);

	return LoadSceneFromFile("ShapeMoverScene1");
}

void CShapeMoverScene::Process(float _fDeltaTick)
{
	if(UpdateButtons(_fDeltaTick))
	{
		ProcessButtonMessage(GetButtonPressedID());
	}

	unsigned int uiSize = m_vecShapes.size();
	for(unsigned int i = 0; i < uiSize; ++i)
	{
		m_vecShapes[i]->Process(_fDeltaTick);
	}
}

void CShapeMoverScene::Render(IRenderer& _rRenderer)
{
	RenderButtons(_rRenderer);

	unsigned int uiSize = m_vecShapes.size();
	for(unsigned int i = 0; i < uiSize; ++i)
	{
		m_vecShapes[i]->Render(_rRenderer);
	}
}

void CShapeMoverScene::ProcessButtonMessage(const int _kiButtonID)
{
	switch(_kiButtonID)
	{
	case 0:
		{
			ClearScene();
			LoadSceneFromFile("ShapeMoverScene1");
		}
		break;
	case 1:
		{
			ClearScene();
			LoadSceneFromFile("ShapeMoverScene2");
		}
	default:
		{
	
		}
		break;
	}
}

void CShapeMoverScene::ClearScene()
{
	while(!m_vecShapes.empty())
	{
		delete m_vecShapes.back();
		m_vecShapes.back() = 0;
		m_vecShapes.pop_back();
	}
}

bool CShapeMoverScene::LoadSceneFromFile(const char* _strFile)
{
	CINIParser parser;
	if(!parser.LoadFile(_strFile))
		return false;
	
	// Load shapes

	int i = 1;
	while(true)
	{
		if(!LoadShape(parser, i++))
			break;
	}

	return true;
}

bool CShapeMoverScene::LoadShape(CINIParser& _rParser, int _iShapeID)
{
	std::stringstream ss;
	ss << "Shape" << _iShapeID;
	std::string strShape = ss.str();

	// Load in shape info
	float fX = 0.0f;
	float fY = 0.0f;
	float fSize = 0.0f;
	std::string strType = "";
	std::string strBorderColour = "";
	std::string strFillColour = "";
	unsigned int uiBorderColour = 0;
	unsigned int uiFillColour = 0;

	_rParser.GetStringValue(strShape.c_str(), "ShapeType", strType);
	_rParser.GetStringValue(strShape.c_str(), "BorderColour", strBorderColour);
	_rParser.GetStringValue(strShape.c_str(), "FillColour", strFillColour);
	_rParser.GetFloatValue(strShape.c_str(), "PosX", fX);
	_rParser.GetFloatValue(strShape.c_str(), "PosY", fY);
	_rParser.GetFloatValue(strShape.c_str(), "Size", fSize);

	CShape* pShape = 0;

	if(strType == "Square")
	{
		pShape = new CSquare();
	}
	else if(strType == "Triangle")
	{
		pShape = new CTriangle();
	}
	else if(strType == "Circle")
	{
		pShape = new CCircle();
	}
	else if(strType == "Hexagon")
	{
		pShape = new CHexagon();
	}

	if(!pShape)
		return false;

	uiBorderColour = TColour::TryParse(strBorderColour.c_str());
	uiFillColour = TColour::TryParse(strFillColour.c_str());

	pShape->Initialise(fX, fY, fSize, uiBorderColour, uiFillColour);

	// Load in Mover info
	float fSpeed = 0.0f;
	float fRadius = 0.0f;
	std::vector<TVector2> vecPoints;
	float fTemp = 0.0f;

	_rParser.GetFloatValue(strShape.c_str(), "Speed", fSpeed);

	// Attempt to get radius
	if(_rParser.GetFloatValue(strShape.c_str(), "Radius", fRadius))
	{
		CShapeMover* pShapeMover = CShapeMover::CreateCircularMover(pShape, fSpeed, fRadius);
		m_vecShapes.push_back(pShapeMover);
	}
	// Attempt to get points
	else if(_rParser.GetFloatValue(strShape.c_str(), "Point1X", fTemp))
	{
		// Add start Pos as first point
		TVector2 v2Point(fX, fY);
		vecPoints.push_back(v2Point);

		int i = 1;
		std::string strPoint;

		while(true)
		{
			TVector2 v2Point;

			ss.str("");
			ss << "Point" << i << "X";
			strPoint = ss.str();
		
			if(!_rParser.GetFloatValue(strShape.c_str(), strPoint.c_str(), v2Point.x))
				break;

			ss.str("");
			ss << "Point" << i << "Y";
			strPoint = ss.str();

			if(!_rParser.GetFloatValue(strShape.c_str(), strPoint.c_str(), v2Point.y))
				break;

			vecPoints.push_back(v2Point);

			i++;
		}

		// Add this shape mover
		TVector2* pPoints = new TVector2[vecPoints.size()];
		//pPoints = &vecPoints[0];
		memcpy(pPoints, &vecPoints[0], sizeof(TVector2) * vecPoints.size());

		CShapeMover* pShapeMover = CShapeMover::CreateWaypointMover(pShape, fSpeed, &pPoints[0], vecPoints.size());
		m_vecShapes.push_back(pShapeMover);
	}
	// This is a static shape
	else
	{
		CShapeMover* pShapeMover = CShapeMover::CreateStaticShape(pShape);
		m_vecShapes.push_back(pShapeMover);
	}

	return true;
}

