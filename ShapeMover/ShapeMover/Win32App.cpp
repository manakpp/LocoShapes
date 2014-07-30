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
#include <sstream>

// Local Includes
#include "Clock.h"
#include "GDIRenderer.h"
#include "DX10Renderer.h"
#include "Input.h"
#include "Logger.h"
#include "Colour.h"
#include "Rect.h"

// This Include
#include "Win32App.h"

// Static Variables


// Default Constructor
CWin32App::CWin32App()
: m_hAppInst(0)
, m_iClientWidth(0)
, m_iClientHeight(0)
, m_hWnd(0)
, m_bAppPaused(false)
, m_bMinimized(false)
, m_bResizing(false)
, m_pRenderer(0)
, m_pClock(0)
, m_pInput(0)
{

}
// Default Destructor
CWin32App::~CWin32App()
{
	m_pRenderer->Shutdown();
	delete m_pRenderer;
	m_pRenderer = 0;

	delete m_pClock;
	m_pClock = 0;

	delete m_pInput;
	m_pInput = 0;
}

LRESULT CALLBACK
MainWndProc(HWND _hwnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	static CWin32App* app = 0;

	switch( _uiMsg )
	{
		case WM_CREATE:
		{
			// Get the 'this' pointer we passed to CreateWindow via the lpParam parameter.
			CREATESTRUCT* cs = (CREATESTRUCT*)_lParam;
			app = (CWin32App*)cs->lpCreateParams;

			return 0;
		}
		break;
	}

	// Don't start processing messages until after WM_CREATE.
	if( app )
	{
		return app->msgProc(_uiMsg, _wParam, _lParam);
	}
	else
	{
		return DefWindowProc(_hwnd, _uiMsg, _wParam, _lParam);
	}
}

HINSTANCE CWin32App::GetAppInst()
{
	return m_hAppInst;
}

HWND CWin32App::GetMainWnd()
{
	return m_hWnd;
}

int CWin32App::Run()
{
	MSG msg = {0};
 
	m_pClock->reset();

	while(msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if(PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
		{
            TranslateMessage( &msg );
            DispatchMessage( &msg );
		}
		// Otherwise, do animation/game stuff.
		else
        {	
			m_pClock->tick();

			if( !m_bAppPaused )
			{
				Process(m_pClock->getDeltaTime());	
			}
			else
			{
				Sleep(50);
			}

			Render(*m_pRenderer);
        }
    }
	return (int)msg.wParam;
}

bool CWin32App::Initialise(HINSTANCE _hInstance, const char* _strTile, int _iClientWidth, int _iClientHeight)
{
	m_hAppInst = _hInstance;
	m_strMainWndCaption = _strTile;
	m_iClientWidth = _iClientWidth;
	m_iClientHeight = _iClientHeight;

	m_pClock = new CClock;
	m_pClock->reset();

	InitialiseWindow();

	return InitialiseRenderer(m_hAppInst, m_hWnd, m_iClientWidth, m_iClientHeight);
}
 
void CWin32App::OnResize()
{
	// TODO: Manage this, if this even needs to happen
}

void CWin32App::Process(float _fDeltaTick)
{
	// To be derived
}

void CWin32App::UpdateFrameStats(float _fDelta)
{
	static int frameCnt = 0;
	static float t_base = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if( (m_pClock->getGameTime() - t_base) >= 1.0f )
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::stringstream ss;
		//outs.precision(6);
		ss << fps << " :  FPS" << "\n" 
			<< mspf <<" : MS/PF" ;
		m_strFrameStats = ss.str();
		
		// Reset for next average.
		frameCnt = 0;
		t_base  += 1.0f;
	}
}

void CWin32App::RenderFrameStats(IRenderer& _rRenderer)
{
	_rRenderer.PrintAllignedTextF(m_strFrameStats.c_str(), TRect(5.0f, 5.0f, (float)(m_iClientWidth - 10), 100.0f), 2);
}

void CWin32App::Render(IRenderer& _rRenderer)
{
	// TODO: Render the framerate
}

bool CWin32App::ChangeRenderer(ERenderer _eRenderer)
{
	m_pRenderer->Shutdown();

	delete m_pRenderer;
	m_pRenderer = 0;

	switch(_eRenderer)
	{
	case GDI:
		{
			m_pRenderer = new CGDIRenderer();
		}
		break;
	case DirectX10:
		{
			m_pRenderer = new CDX10Renderer();
		}
		break;
	}

	if(!m_pRenderer->Initialise(m_hAppInst, m_hWnd, m_iClientWidth, m_iClientHeight))
		return false;

	m_pRenderer->SetClearColour(TColour::MakeColour(255, 125, 125, 255));

	return true;
}

LRESULT CWin32App::msgProc(UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch( _uiMsg )
	{
	case WM_KEYUP:
		{
			m_pInput->SetKeyRelease(static_cast<int>(_wParam));
			
			return(0);
		}
	case WM_KEYDOWN:
		{
			m_pInput->SetKeyPress(static_cast<int>(_wParam));
			
			return(0);
		}
	case WM_MOUSEMOVE:
		{
			m_pInput->SetMousePos((float)LOWORD(_lParam), (float)HIWORD(_lParam));
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			m_pInput->SetMouseButtonDown(true);
			m_pInput->SetMouseButtonUp(false);
			return 0;
		}
	case WM_LBUTTONUP:
		{		
			m_pInput->SetMouseButtonDown(false);
			m_pInput->SetMouseButtonUp(true);
			return 0;
		}

	// WM_ACTIVATE is sent when the window is activated or deactivated.  
	// We pause the game when the window is deactivated and unpause it 
	// when it becomes active.  
	//case WM_ACTIVATE:
	//	if( LOWORD(_wParam) == WA_INACTIVE )
	//	{
	//		m_bAppPaused = true;
	//		m_pClock->stop();
	//	}
	//	else
	//	{
	//		m_bAppPaused = false;
	//		m_pClock->start();
	//	}
	//	return 0;

	// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		{
		// Save the new client area dimensions.
		m_iClientWidth  = LOWORD(_lParam);
		m_iClientHeight = HIWORD(_lParam);

			if( m_pRenderer )
			{
				if( _wParam == SIZE_MINIMIZED )
				{
					m_bAppPaused = true;
					m_bMinimized = true;
					m_bMaximized = false;
				}
				else if( _wParam == SIZE_MAXIMIZED )
				{
					m_bAppPaused = false;
					m_bMinimized = false;
					m_bMaximized = true;
					OnResize();
				}
				else if( _wParam == SIZE_RESTORED )
				{
					
					// Restoring from minimized state?
					if( m_bMinimized )
					{
						m_bAppPaused = false;
						m_bMinimized = false;
						OnResize();
					}

					// Restoring from maximized state?
					else if( m_bMaximized )
					{
						m_bAppPaused = false;
						m_bMaximized = false;
						OnResize();
					}
					else if( m_bResizing )
					{
						// If user is dragging the resize bars, we do not resize 
						// the buffers here because as the user continuously 
						// drags the resize bars, a stream of WM_SIZE messages are
						// sent to the window, and it would be pointless (and slow)
						// to resize for each WM_SIZE message received from dragging
						// the resize bars.  So instead, we reset after the user is 
						// done resizing the window and releases the resize bars, which 
						// sends a WM_EXITSIZEMOVE message.
					}
					else // API call such as SetWindowPos or mSwapChain->SetFullSceneState.
					{
						OnResize();
					}
				}
			}
		}
		return 0;

	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_bAppPaused = true;
		m_bResizing  = true;
		m_pClock->stop();
		return 0;

	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		m_bAppPaused = false;
		m_bResizing  = false;
		m_pClock->start();
		OnResize();
		return 0;
 
	// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	// The WM_MENUCHAR message is sent when a menu is active and the user presses 
	// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
        // Don't beep when we alt-enter.
        return MAKELRESULT(0, MNC_CLOSE);

	// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)_lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)_lParam)->ptMinTrackSize.y = 200; 
		return 0;
	}

	return DefWindowProc(m_hWnd, _uiMsg, _wParam, _lParam);
}


void CWin32App::InitialiseWindow()
{
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hAppInst;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"GDIWndClassName";

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		PostQuitMessage(0);
	}

	RECT R = { 0, 0, m_iClientWidth, m_iClientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	m_hWnd = CreateWindowExA(NULL,
								"GDIWndClassName",
								m_strMainWndCaption.c_str(), 
								WS_SYSMENU | WS_CAPTION & WS_MAXIMIZE | WS_MINIMIZEBOX,
								CW_USEDEFAULT, CW_USEDEFAULT,
								width,height,
								0, 0,
								m_hAppInst, 
								this); 

	if( !m_hWnd )
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

bool CWin32App::InitialiseRenderer(HINSTANCE _hInstance, HWND _hwnd, int _iClientWidth, int _iClientHeight)
{
	m_pRenderer = new CGDIRenderer();
	
	if(!m_pRenderer->Initialise(_hInstance, _hwnd, _iClientWidth, _iClientHeight))
		return false;

	m_pRenderer->SetClearColour(TColour::MakeColour(255, 125, 125, 255));
	
	return true;
}