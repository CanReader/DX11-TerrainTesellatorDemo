#include "System.h"
#include "TheApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	TheApp* app = new TheApp();
	System* m_System = new System(app);

	m_System->Run();

	delete m_System;
	m_System = 0;

	return 0;
}