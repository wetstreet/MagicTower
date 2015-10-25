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

//����������ܷ���WindowManager���У���Ϊwindowmanager��ᱻobject����ã���������������object�������player��
//�������windowmanager�ࣨ������object�ĸ���������ñ�Ĵ��ڣ��еĻ�����ɵݹ鶨�壬�������ֻ�ܷ�����һ��ͷ�ļ���
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

//������ת��Ϊ���ַ�����
wstring IntToWString(int i){
	wstring s;
	wstringstream stream;
	stream << i;
	stream >> s;
	return s;
}

//��ʼ��ս�������ı�
void InitFightWindowText(WindowManager *wm, Player *p, HWND hWnd){
	SetWindowText(GetDlgItem(hWnd, IDC_PLAYER_HEALTH), IntToWString(p->getHealth()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_PLAYER_ATTACK), IntToWString(p->getAttack()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_PLAYER_DEFENSE), IntToWString(p->getDefense()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_ENEMY_HEALTH), IntToWString(wm->getEnemyHealth()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_ENEMY_ATTACK), IntToWString(wm->getEnemyAttack()).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_ENEMY_DEFENSE), IntToWString(wm->getEnemyDefense()).c_str());
}
#endif