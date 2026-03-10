#include "System.h"
#include "TheApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// Set working directory to the executable's location so relative asset paths resolve correctly
	WCHAR exePath[MAX_PATH];
	GetModuleFileNameW(NULL, exePath, MAX_PATH);
	WCHAR* lastSlash = wcsrchr(exePath, L'\\');
	if (lastSlash) *lastSlash = L'\0';
	SetCurrentDirectoryW(exePath);

	TheApp* app = new TheApp();
	System* m_System = new System(app);

	m_System->Run();

	delete m_System;
	m_System = 0;

	return 0;
}
