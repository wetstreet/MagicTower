#ifndef INPUT_H
#define INPUT_H

#include "manager.h"

void KeyDown(Manager *m, WPARAM wparam, MapManager *map, WindowManager *wm){
	Player *p = m->getPlayer();
	int x = p->getX();
	int y = p->getY();
	int currentFloor = map->getCurrentFloor();

	switch (wparam){
	case VK_UP:
		if (y > 0){
			m->Search(map->getNumber(currentFloor, x, y - 1))->MeetPlayer(currentFloor, x, y - 1, p, map, wm);
		}
		break;
	case VK_DOWN:
		if (y < 10){
			m->Search(map->getNumber(currentFloor, x, y + 1))->MeetPlayer(currentFloor, x, y + 1, p, map, wm);
		}
		break;
	case VK_LEFT:
		if (x > 0){
			m->Search(map->getNumber(currentFloor, x - 1, y))->MeetPlayer(currentFloor, x - 1, y, p, map, wm);
		}
		break;
	case VK_RIGHT:
		if (x < 10){
			m->Search(map->getNumber(currentFloor, x + 1, y))->MeetPlayer(currentFloor, x + 1, y, p, map, wm);
		}
		break;
	}
}
#endif