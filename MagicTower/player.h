#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player :public Object{
public:
	Player(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){
		health = 1000; attack = 10; defense = 10; money = 0; x = 5; y = 9; }
	void Paint(HDC hdc){ Object::Paint(hdc, x, y); }
	int getHealth(){ return health; }
	int getAttack(){ return attack; }
	int getDefense(){ return defense; }
	int getMoney(){ return money; }
private:
	int health, attack, defense, money;
	int x, y;
};
#endif