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
	//��������������ҹ����߻���ȣ������ﲻ������������£�����false
	if (defense >= playerAttack)
		return false;
	//�������������������������������������false����������������true
	while (playerHealth > 0)
	{
		//����ȹ�������󹥣�����ҹ������������������ﲻ����
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