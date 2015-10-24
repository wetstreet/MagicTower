#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player :public Object{
public:
	Player(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){
		health = 1000; attack = 10; defense = 10; money = 0; x = 5; y = 9; }
	void Paint(HDC hdc){ Object::Paint(hdc, x, y); }
	int getHealth()const{ return health; }
	int getAttack()const{ return attack; }
	int getDefense()const{ return defense; }
	int getMoney()const{ return money; }
	int getX()const{ return x; }
	int getY()const{ return y; }
	int getKey()const{ return key; }
	void MoveUp(){ y--; }
	void MoveDown(){ y++; }
	void MoveLeft(){ x--; }
	void MoveRight(){ x++; }
	void setX(int i){ x = i; }
	void setY(int i){ y = i; }
	void setKey(int i){ key = i; }
private:
	int health, attack, defense, money, key;
	int x, y;
};
#endif