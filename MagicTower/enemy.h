#ifndef ENEMY_H
#define ENEMY_H

#include "resource.h"
#include "object.h"
#include "player.h"
#include "window.h"

//一个enemy类的对象表示一种怪物，并不生成具体的怪物，也就意味着不同怪物之间只有参数和图片的区别，其实都是同一个类的对象。
//地图上显示的只是怪物种类的一个投影，怪物死亡并不影响储存在manager类中的怪物种类
class Enemy :public Object
{
public:
	Enemy(int id, UINT resourceId, HINSTANCE hIns, int Health, int Attack, int Defense, int Money) 
		:Object(id, resourceId, hIns), health(Health), attack(Attack), defense(Defense), money(Money){}
	int getHealth(){ return health; }
	int getAttack(){ return attack; }
	int getDefense(){ return defense; }
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
	bool calcDamage(Player *p);
private:
	int health, attack, defense, money;
};

bool Enemy::calcDamage(Player *p){
	int playerHealth = p->getHealth();
	int playerAttack = p->getAttack();
	int playerDefense = p->getDefense();
	int EnemyHealth = health;
	//如果怪物防御比玩家攻击高或相等，即怪物不可能死的情况下，返回false
	if (defense >= playerAttack)
		return false;
	//计算怪物先死还是玩家先死，若玩家先死返回false，若怪物先死返回true
	while (playerHealth > 0)
	{
		//玩家先攻，怪物后攻，若玩家攻击后怪物死亡，则怪物不攻击
		EnemyHealth -= (playerAttack - defense);
		if (EnemyHealth < 0)
			return true;
		playerHealth -= (attack - playerDefense);
	}
	return false;
}

void Enemy::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	if (calcDamage((Player *)p)){
		wm->CallFight(getId(), health, attack, defense, money);
		mm->setNumber(floor, x, y, 0);
	}
}
#endif