#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "definitions.h"

extern LRESULT	CALLBACK FIGHT(HWND, UINT, WPARAM, LPARAM);

class WindowManager{
public:
	WindowManager(HINSTANCE hIns, HWND hMain) :hInstance(hIns), hMainWindow(hMain){}
	HWND getMainHandle(){ return hMainWindow; }
	void CallFight();
private:
	HINSTANCE hInstance;
	HWND hMainWindow;
};

void WindowManager::CallFight(){
	DialogBox(hInstance, (LPCTSTR)IDD_FIGHT, hMainWindow, (DLGPROC)FIGHT);
}

#endif