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
#include "SceneManager.h"

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
	// Create a bunch of buttons
	TVector2 startPos(10.0f, 10.0f);
	TVector2 buttonSize(100.0f, 50.0f);
	TVector2 buttonOffset(0.0f, 10.0f);

	AddButton(0, "GDI Renderer", startPos.x, startPos.y, buttonSize.x, buttonSize.y);
	AddButton(1, "DX10 Renderer", startPos.x + buttonOffset.x, startPos.y + (buttonSize.y  * 1.0f) + (buttonOffset.y * 1.0f), buttonSize.x, buttonSize.y);
	AddButton(2, "Reload from file 1", startPos.x + buttonOffset.x, startPos.y + (buttonSize.y * 2.0f) + (buttonOffset.y * 2.0f), buttonSize.x, buttonSize.y);
	AddButton(3, "Reload from file 2", startPos.x + buttonOffset.x, startPos.y + (buttonSize.y * 3.0f) + (buttonOffset.y * 3.0f), buttonSize.x, buttonSize.y);

	// Load a default scene
	m_iSelectedScene = 0;
	return LoadSceneFromFile("ShapeMoverScene1");
}

// Processes all objects in scene
void CShapeMoverScene::Process(float _fDeltaTick)
{
	// Check for button presses and act on any changes
	if(UpdateButtons(_fDeltaTick))
	{
		ProcessButtonMessage(GetButtonPressedID());
	}

	// Update the positions of the all the shapes
	unsigned int uiSize = m_vecShapes.size();
	for(unsigned int i = 0; i < uiSize; ++i)
	{
		m_vecShapes[i]->Process(_fDeltaTick);
	}
}

// Renders all objects in scene
void CShapeMoverScene::Render(IRenderer& _rRenderer)
{
	RenderButtons(_rRenderer);

	unsigned int uiSize = m_vecShapes.size();
	for(unsigned int i = 0; i < uiSize; ++i)
	{
		m_vecShapes[i]->Render(_rRenderer);
	}
}

// Call back for buttons.
void CShapeMoverScene::ProcessButtonMessage(const int _kiButtonID)
{
	ClearScene();

	switch(_kiButtonID)
	{
	case 0:
		{
			CSceneManager::GetInstance().ChangeRenderer(GDI);
		}
		break;
	case 1:
		{
			CSceneManager::GetInstance().ChangeRenderer(DirectX10);
		}
		break;
	case 2:
		{
			m_iSelectedScene = 0;
		}
		break;
	case 3:
		{
			m_iSelectedScene = 1;
		}
	default:
		{
	
		}
		break;
	}

	// Load/Reload scene
	std::stringstream ss;
	ss << "ShapeMoverScene" << m_iSelectedScene + 1;

	LoadSceneFromFile(ss.str().c_str());
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
	while(true) // Caution with this infinite loop
	{
		if(!LoadShape(parser, i++))
			break;
	}

	return true;
}

bool CShapeMoverScene::LoadShape(CINIParser& _rParser, int _iShapeID)
{
	// TODO: Error checking and handling for missing data
	// Take caution :P

	// Contruct the shape section name
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

