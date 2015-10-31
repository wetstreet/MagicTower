#ifndef GENERAL_H
#define GENERAL_H

#include <windows.h>
#include <iostream>
#include "window.h"
#include "player.h"
#include "resource.h"
using namespace std;

//�������´��ڵĴ��ڸ�����
class WindowUpdator{
public:
	WindowUpdator(HINSTANCE hIns) :hInstance(hIns){}
	HINSTANCE getHIns()const{ return hInstance; }
	void setHMainWindow(HWND hWnd){ hMainWindow = hWnd; }
	void setHFightWindow(HWND hWnd){ hFightWindow = hWnd; }
	void setHEditorWindow(HWND hWnd){ hEditorWindow = hWnd; }
	void UpdateMainWindow(){ Update(hMainWindow); }
	void UpdateFightWindow(){ Update(hFightWindow); }
	void UpdateEditorWindow(){ Update(hEditorWindow); }
private:
	HWND hMainWindow;
	HWND hFightWindow;
	HWND hEditorWindow;
	HINSTANCE hInstance;
	void Update(HWND hwnd){
		InvalidateRgn(hwnd, NULL, FALSE);
		UpdateWindow(hwnd);
	}
};

//������ת��Ϊ���ַ�����
wstring IntToWString(int i){
	wstring s;
	wstringstream stream;
	stream << i;
	stream >> s;
	return s;
}

//����������ܷ���WindowManager���У���Ϊwindowmanager��ᱻobject����ã���������������object�������player��
//�������windowmanager�ࣨ������object�ĸ���������ñ�Ĵ��ڣ��еĻ�����ɵݹ鶨�壬�������ֻ�ܷ�����һ��ͷ�ļ���
void FightTimer(WindowManager *wm, Player *p, HWND hWnd, WPARAM wparam){
	wm->ReduceEnemyHealth(p->getAttack() - wm->getEnemyDefense());
	if (wm->getEnemyHealth() <= 0){
		p->AddMoney(wm->getEnemyMoney());
		KillTimer(hWnd, FIGHT_TIMER_ID);
		EndDialog(hWnd, LOWORD(wparam));
	}
	else{
		p->ReduceHealth(wm->getEnemyAttack() - p->getDefense());
	}
}

void ShopOnCommand(Player *p, HWND hWnd, WPARAM wparam){
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