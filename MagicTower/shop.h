#ifndef SHOP_H
#define SHOP_H

#include "object.h"
#include "player.h"
#include <Windows.h>

class Shop :public Object{
public:
	Shop(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void Shop::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	wm->KillMainTimer(MAIN_TIMER_ID);
	wm->CallShop();
}

#endif