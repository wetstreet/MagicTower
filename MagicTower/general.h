#ifndef GENERAL_H
#define GENERAL_H

#include <windows.h>

class WindowUpdator{
public:
	WindowUpdator(HWND hwnd) :hWnd(hwnd){}
	void Update(){
		InvalidateRgn(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
	}
private:
	HWND hWnd;
};
#endif