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

#ifndef __MANA2012_CLASS_WIN32APP_H__
#define __MANA2012_CLASS_WIN32APP_H__


// Library Includes
#include <Windows.h>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class IRenderer;
class CClock;
class CInput;
enum ERenderer;

class CWin32App
{
public:
	CWin32App();
	virtual ~CWin32App();

	HINSTANCE GetAppInst();
	HWND      GetMainWnd();

	bool ExecuteFrame();
	int Run();

	// To be derived:
	virtual bool Initialise(HINSTANCE _hInstance, const char* _strTile, int _iClientWidth, int _iClientHeight);
	virtual void OnResize();
	virtual void Process(float _fDelta);
	virtual void Render(IRenderer& _rRenderer); 
	virtual LRESULT msgProc(UINT _uiMsg, WPARAM _wParam, LPARAM _lParam);

	void UpdateFrameStats(float _fDelta);
	void RenderFrameStats(IRenderer& _rRenderer);

	bool ChangeRenderer(ERenderer _eRenderer);

protected:
	void InitialiseWindow();
	bool InitialiseRenderer(HINSTANCE _hInstance, HWND _hwnd, int _iClientWidth, int _iClientHeight);
	
protected:
	std::string m_strFrameStats;
	std::string m_strMainWndCaption;
	
	IRenderer* m_pRenderer;
	CClock* m_pClock;
	CInput* m_pInput;

	HINSTANCE m_hAppInst;
	HWND m_hWnd;

	int m_iClientWidth;
	int m_iClientHeight;

	bool m_bAppPaused;
	bool m_bMinimized;
	bool m_bMaximized;
	bool m_bResizing;
};


#endif // __MANA2012_CLASS_WIN32APP_H__