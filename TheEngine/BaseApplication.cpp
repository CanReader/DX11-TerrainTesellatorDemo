#include "BaseApplication.h"


BaseApplication::BaseApplication()
{
	
}


BaseApplication::~BaseApplication()
{
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Direct3D)
	{
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}

void BaseApplication::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	m_Input = in;
	wnd = hwnd;
	sWidth = screenWidth;
	sHeight = screenHeight;

	m_Direct3D = new D3D(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!m_Direct3D)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		exit(EXIT_FAILURE);
	}

	m_Camera = new Camera();
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Update();

	m_Timer = new Timer();

	ImGui_ImplDX11_Init(wnd, m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
}

bool BaseApplication::Frame()
{
	if (m_Input->isKeyDown(VK_ESCAPE) == true)
		return false;

	m_Timer->Frame();

	HandleInput(m_Timer->GetTime());

	ImGui_ImplDX11_NewFrame();

	return true;
}


void BaseApplication::HandleInput(float frameTime)
{
	m_Camera->SetFrameTime(frameTime);

	if (m_Input->isKeyDown('W'))
	{
		m_Camera->MoveForward();
	}
	if (m_Input->isKeyDown('S'))
	{
		m_Camera->MoveBackward();
	}
	if (m_Input->isKeyDown('A'))
	{
		m_Camera->StrafeLeft();
	}
	if (m_Input->isKeyDown('D'))
	{
		m_Camera->StrafeRight();
	}
	if (m_Input->isKeyDown('Q'))
	{
		m_Camera->MoveDownward();
	}
	if (m_Input->isKeyDown('E'))
	{
		m_Camera->MoveUpward();
	}
	if (m_Input->isKeyDown(VK_UP))
	{
		m_Camera->TurnUp();
	}
	if (m_Input->isKeyDown(VK_DOWN))
	{
		m_Camera->TurnDown();
	}
	if (m_Input->isKeyDown(VK_LEFT))
	{
		m_Camera->TurnLeft();
	}
	if (m_Input->isKeyDown(VK_RIGHT))
	{
		m_Camera->TurnRight();
	}

	if (m_Input->isMouseActive())
	{
		deltax = m_Input->getMouseX() - (sWidth / 2);
		deltay = m_Input->getMouseY() - (sHeight / 2);
		m_Camera->Turn(deltax, deltay);
		cursor.x = sWidth / 2;
		cursor.y = sHeight / 2;
		ClientToScreen(wnd, &cursor);
		SetCursorPos(cursor.x, cursor.y);
	}

	if (m_Input->isKeyDown(VK_SPACE))
	{
		MessageBox(NULL,L"Space triggered!",L"Btn",MB_OK);
		cursor.x = sWidth / 2;
		cursor.y = sHeight / 2;
		ClientToScreen(wnd, &cursor);
		SetCursorPos(cursor.x, cursor.y);
		m_Input->setMouseX(sWidth / 2);
		m_Input->setMouseY(sHeight / 2);
		m_Input->SetKeyUp(VK_SPACE);
		m_Input->setMouseActive(!m_Input->isMouseActive());
		if (!m_Input->isMouseActive())
		{
			ShowCursor(true);
		}
		else
		{
			ShowCursor(false);
		}
	}

	
}
