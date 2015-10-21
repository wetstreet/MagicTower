#ifndef BITMAP_H
#define BITMAP_H
#include <windows.h>

class Bitmap
{
public:
	Bitmap(HINSTANCE, UINT);
	Bitmap(){ DeleteObject(hBitmap); }
	int GetWidth()const{ return width; }
	int GetHeight()const{ return height; }
	void BitBlt(HDC hdcClient, int x, int y);
private:
	BITMAP	bitmap;
	HBITMAP	hBitmap;
	HDC		hdcMem;
	int		height;
	int		width;
};

Bitmap::Bitmap(HINSTANCE hIns, UINT nIDResource)
{
	hBitmap = LoadBitmap(hIns, MAKEINTRESOURCE(nIDResource));
	GetObject(hBitmap, sizeof(bitmap), &bitmap);
	width = bitmap.bmWidth;
	height = bitmap.bmHeight;
}

void Bitmap::BitBlt(HDC hdcClient, int x, int y)
{
	hdcMem = CreateCompatibleDC(hdcClient);
	SelectObject(hdcMem, hBitmap);
	::BitBlt(hdcClient, x, y, width, height, hdcMem, 0, 0, SRCCOPY);
	DeleteDC(hdcMem);
}
#endif