#ifndef OBJECT_H
#define OBJECT_H

#include "bitmap.h"
#include "definitions.h"
#include "map.h"
#include "window.h"

class Object{
public:
	Object(int ID, UINT resourceId, HINSTANCE hIns) :id(ID){ picture = new Bitmap(hIns, resourceId); }
	int getId() { return id; }
	void PaintFromZero(HDC hdc){ if(picture) picture->BitBlt(hdc, 0, 0); }
	virtual void setX(int i){}
	virtual void setY(int i){}
	virtual int getKey()const{ return 0; }
	virtual void setKey(int i){}
	virtual void Paint(HDC hdc, int x, int y){ if (picture) picture->BitBlt(hdc, g_x + 50 * x, g_y + 50 * y); }
	//当物体碰到玩家时执行的函数
	virtual void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){}
private:
	const int g_x = 13;
	const int g_y = 12;
	int id;
	Bitmap *picture;
};

#endif