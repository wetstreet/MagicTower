#ifndef ENEMY_H
#define ENEMY_H

#include "resource.h"
#include "object.h"
#include "player.h"
#include "window.h"

//һ��enemy��Ķ����ʾһ�ֹ���������ɾ���Ĺ��Ҳ����ζ�Ų�ͬ����֮��ֻ�в�����ͼƬ��������ʵ����ͬһ����Ķ���
//��ͼ����ʾ��ֻ�ǹ��������һ��ͶӰ��������������Ӱ�촢����manager���еĹ�������
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
	//��������������ҹ����߻���ȣ������ﲻ������������£�����false
	if (defense >= playerAttack)
		return false;
	//�������������������������������������false����������������true
	while (playerHealth > 0)
	{
		//����ȹ�������󹥣�����ҹ������������������ﲻ����
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