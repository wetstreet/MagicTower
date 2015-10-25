#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include "definitions.h"

extern LRESULT	CALLBACK FIGHT(HWND, UINT, WPARAM, LPARAM);
//extern LRESULT	CALLBACK SHOP(HWND, UINT, WPARAM, LPARAM);

//相当于一个中转站，由MeetPlayer函数传入对应的参数并调用这个类中的函数
//遇到怪物时保存怪物信息并打开战斗窗口，并在战斗窗口中对这个类中保存的信息进行操作
//遇到其他东西时打开对应的窗口，如商店
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