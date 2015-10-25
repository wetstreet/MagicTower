#ifndef OBJECT_H
#define OBJECT_H

#include "bitmap.h"
#include "definitions.h"
#include "map.h"
#include "window.h"

//��Ϸ�ڸ��ֶ���Ļ��࣬����player��enemy��road��key֮��ȵȼ������ж�����
class Object{
public:
	Object(int ID, UINT resourceId, HINSTANCE hIns) :id(ID){ picture = new Bitmap(hIns, resourceId); }
	int getId()const{ return id; }
	void PaintFromZero(HDC hdc){ if(picture) picture->BitBlt(hdc, 0, 0); }
	virtual void Paint(HDC hdc, int x, int y){ picture->BitBlt(hdc, g_x + 50 * x, g_y + 50 * y); }
	void BitBlt(HDC hdc, int x, int y){ picture->BitBlt(hdc, x, y); }
	//�������������ʱִ�еĺ���
	virtual void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){}
private:
	const int g_x = 13;
	const int g_y = 12;
	int id;
	Bitmap *picture;
};

#endif