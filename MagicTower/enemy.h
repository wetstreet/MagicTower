#ifndef ENEMY_H
#define ENEMY_H

#include "object.h"

class Enemy :public Object
{
public:
	Enemy(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	int getHealth(){ return health; }
	int getAttack(){ return attack; }
	int getDefense(){ return defense; }
private:
	int health, attack, defense, money;
};
#endif