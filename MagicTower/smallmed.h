#ifndef SMALLMED_H
#define SMALLMED_H

#include "object.h"
#include "player.h"
#include <Windows.h>

class SmallMed :public Object{
public:
	SmallMed(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void SmallMed::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	player->AddHealth(200);
	//��Ʒ�ѱ���һ�ã�����Ʒ�ӵ�ͼ����ȥ
	mm->setNumber(floor, x, y, 0);
}

#endif