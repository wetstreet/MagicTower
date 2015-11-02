#ifndef BIGMED_H
#define BIGMED_H

#include "object.h"
#include "player.h"
#include <Windows.h>

class BigMed :public Object{
public:
	BigMed(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void BigMed::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	player->AddHealth(500);
	//��Ʒ�ѱ���һ�ã�����Ʒ�ӵ�ͼ����ȥ
	mm->setNumber(floor, x, y, 0);
}

#endif