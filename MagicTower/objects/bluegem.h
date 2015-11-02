#ifndef BLUEGEM_H
#define BLUEGEM_H

#include "object.h"
#include "player.h"
#include <Windows.h>

class BlueGem :public Object{
public:
	BlueGem(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void BlueGem::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	player->AddDefense(3);
	mm->setNumber(floor, x, y, 0);
}

#endif