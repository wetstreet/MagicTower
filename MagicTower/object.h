#ifndef OBJECT_H
#define OBJECT_H

#include "bitmap.h"
#include "definitions.h"

class Object{
public:
	Object(int ID, UINT resourceId, HINSTANCE hIns) :id(ID), picture(hIns, resourceId){}
	int getId() { return id; }
	void PaintFromZero(HDC hdc){ picture.BitBlt(hdc, 0, 0); }
	virtual void function(HWND, int, int, int){}
	virtual void Paint(HDC hdc, int x, int y){ picture.BitBlt(hdc, g_x + 50 * x, g_y + 50 * y); }
private:
	const int g_x = 13;
	const int g_y = 12;
	int id;
	Bitmap picture;
};

#endif