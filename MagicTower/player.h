#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "definitions.h"
#include <Windows.h>

class Player :public Object{
public:
	Player(int id, UINT resourceId, HINSTANCE hIns);
	void Paint(HDC hdc){ Object::Paint(hdc, x - 1, y - 1); }
	int getHealth()const{ return health; }
	void AddHealth(int i){ health += i; }
	void ReduceHealth(int i){ health -= i; }
	int getAttack()const{ return attack; }
	void AddAttack(int i){ attack += i; }
	int getDefense()const{ return defense; }
	void AddDefense(int i){ defense += i; }
	int getMoney()const{ return money; }
	void AddMoney(int i){ money += i; }
	void ReduceMoney(int i){ money -= i; }
	void MoveUp(){ y--; }
	void MoveDown(){ y++; }
	void MoveLeft(){ x--; }
	void MoveRight(){ x++; }
	int getX()const{ return x; }
	void setX(int i){ x = i; }
	int getY()const{ return y; }
	void setY(int i){ y = i; }
	int getKey()const{ return key; }
	void setKey(int i){ key = i; }
private:
	int health, attack, defense, money, key;
	int x, y;
};


Player::Player(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){
	x = PLAYER_INIT_X;
	y = PLAYER_INIT_Y;
	health = PLAYER_INIT_HEALTH;
	attack = PLAYER_INIT_ATTACK;
	defense = PLAYER_INIT_DEFENSE;
	money = PLAYER_INIT_MONEY;
	key = PLAYER_INIT_KEY;
}
#endif