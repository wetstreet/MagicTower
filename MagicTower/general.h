#ifndef GENERAL_H
#define GENERAL_H

#include <windows.h>
#include <iostream>
#include "window.h"
#include "player.h"
#include "resource.h"
using namespace std;

class WindowUpdator{
public:
	WindowUpdator(HWND hwnd) :hWnd(hwnd){}
	void Update(HWND hwnd){
		InvalidateRgn(hwnd, NULL, FALSE);
		UpdateWindow(hwnd);
	}
	void Update(){
		InvalidateRgn(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
	}
private:
	HWND hWnd;
};

//这个函数不能放在WindowManager类中，因为windowmanager类会被object类调用，而这个函数会调用object类的子类player类
//如果放在windowmanager类（用来给object的各个子类调用别的窗口）中的话会造成递归定义，所以这个只能放在另一个头文件中
void FightTimer(WindowManager *wm, Player *p, HWND hWnd, WPARAM wparam){
	int playerHealth = p->getHealth();
	int playerAttack = p->getAttack();
	int playerDefense = p->getDefense();
	int enemyHealth = wm->getEnemyHealth();
	int enemyAttack = wm->getEnemyAttack();
	int enemyDefense = wm->getEnemyDefense();

	wm->ReduceEnemyHealth(playerAttack - enemyDefense);
	if (enemyHealth <= 0){
		p->AddMoney(wm->getEnemyMoney());
		KillTimer(hWnd, FIGHT_TIMER);
		EndDialog(hWnd, LOWORD(wparam));
	}
	else{
		p->ReduceHealth(enemyAttack - playerDefense);
	}
}

void Shopping(Player *p, WPARAM wparam, HWND hWnd){
	switch (LOWORD(wparam)){
	case IDC_EXIT:
		EndDialog(hWnd, LOWORD(wparam));
		break;
	case IDC_BUY_HEALTH:
		if (p->getMoney() >= 25){
			p->AddHealth(800);
			p->ReduceMoney(25);
		}
		break;
	case IDC_BUY_ATTACK:
		if (p->getMoney() >= 25){
			p->AddAttack(4);
			p->ReduceMoney(25);
		}
		break;
	case IDC_BUY_DEFENSE:
		if (p->getMoney() >= 25){
			p->AddDefense(4);
			p->ReduceMoney(25);
		}
		break;
	}
}

//将整型转换为宽字符串型
wstring IntToWString(int i){
	wstring s;
	wstringstream stream;
	stream << i;
	stream >> s;
	return s;
}

//初始化战斗窗口文本
void InitFightWindowText(WindowManager *wm, Player *p, HWND hWnd){
	SetWindowText(GetDlgItem(hWnd, IDC_PLAYER_HEALTH), IntToWString(p->getHealth()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_PLAYER_ATTACK), IntToWString(p->getAttack()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_PLAYER_DEFENSE), IntToWString(p->getDefense()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_ENEMY_HEALTH), IntToWString(wm->getEnemyHealth()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_ENEMY_ATTACK), IntToWString(wm->getEnemyAttack()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_ENEMY_DEFENSE), IntToWString(wm->getEnemyDefense()).c_str());
}
#endif