#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "definitions.h"

extern LRESULT	CALLBACK FIGHT(HWND, UINT, WPARAM, LPARAM);
//extern LRESULT	CALLBACK SHOP(HWND, UINT, WPARAM, LPARAM);

//�൱��һ����תվ����MeetPlayer���������Ӧ�Ĳ���������������еĺ���
//��������ʱ���������Ϣ����ս�����ڣ�����ս�������ж�������б������Ϣ���в���
//������������ʱ�򿪶�Ӧ�Ĵ��ڣ����̵�
class WindowManager{
public:
	WindowManager(HINSTANCE hIns, HWND hMain) :hInstance(hIns), hMainWindow(hMain){}
	HWND getMainHandle(){ return hMainWindow; }
	void CallFight(int id, int health, int attack, int defense, int money);
	void CallShop();
	int getEnemyId(){ return enemyId; }
	int getEnemyHealth()const{ return enemyHealth; }
	void ReduceEnemyHealth(int i){ enemyHealth -= i; if (enemyHealth < 0)enemyHealth = 0; }
	int getEnemyAttack()const{ return enemyAttack; }
	int getEnemyDefense()const{ return enemyDefense; }
	int getEnemyMoney()const{ return enemyMoney; }
private:
	HINSTANCE hInstance;
	HWND hMainWindow;
	int enemyId;
	int enemyHealth;
	int enemyAttack;
	int enemyDefense;
	int enemyMoney;
};

void WindowManager::CallFight(int id, int health, int attack, int defense, int money){
	enemyId = id;
	enemyHealth = health;
	enemyAttack = attack;
	enemyDefense = defense;
	enemyMoney = money;
	DialogBox(hInstance, (LPCTSTR)IDD_FIGHT, hMainWindow, (DLGPROC)FIGHT);
}

void WindowManager::CallShop(){
	DialogBox(hInstance, (LPCTSTR)IDD_SHOP, hMainWindow, (DLGPROC)SHOP);
}

#endif