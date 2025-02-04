#ifndef _BASEAPPLICATION_H_
#define _BASEAPPLICATION_H_

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;	
const float SCREEN_NEAR = 0.1f;		

#include "input.h"
#include "d3d.h"
#include "camera.h"
#include "timer.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"

class BaseApplication
{
public:

	BaseApplication();
	~BaseApplication();
	virtual void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in);

	virtual bool Frame();

protected:
	virtual void HandleInput(float);
	virtual bool Render() = 0;

protected:
	HWND wnd;
	int sWidth, sHeight;
	int deltax, deltay;	
	POINT cursor;
	Input* m_Input;
	D3D* m_Direct3D;
	Camera* m_Camera;
	Timer* m_Timer;
};

#endif