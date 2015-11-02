#ifndef KEY_H
#define KEY_H

#include "object.h"
#include "player.h"
#include "window.h"

class Key :public Object{
public:
	Key(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void Key::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	int key = player->getKey();
	player->setKey(++key);
	mm->setNumber(floor, x, y, 0);
}

#endif