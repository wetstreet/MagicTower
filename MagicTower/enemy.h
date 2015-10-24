#ifndef ENEMY_H
#define ENEMY_H

#include "object.h"
#include "player.h"

class Enemy :public Object
{
public:
	Enemy(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	int getHealth(){ return health; }
	int getAttack(){ return attack; }
	int getDefense(){ return defense; }
	void MeetPlayer(int floor, int x, int y);
	bool calcDamage(Player *p);
private:
	int health, attack, defense, money;
};

bool Enemy::calcDamage(Player *p){
	int playerHealth = p->getHealth();
	int playerAttack = p->getAttack();
	int playerDefense = p->getDefense();
	//如果怪物防御比玩家攻击高或相等，即怪物不可能死的情况下，返回false
	if (defense >= playerAttack)
		return false;
	//计算怪物先死还是玩家先死，若玩家先死返回false，若怪物先死返回true
	while (playerHealth > 0)
	{
		//玩家先攻，怪物后攻，若玩家攻击后怪物死亡，则怪物不攻击
		health -= (playerAttack - defense);
		if (health < 0)
			return true;
		playerHealth -= (attack - playerDefense);
	}
	return false;
}

void Enemy::MeetPlayer(int floor, int x, int y){

}
#endif