#include "resource.h"
#include "definitions.h"
#include "manager.h"
#include "map.h"
#include "window.h"
#include "general.h"
#include "editor.h"

HINSTANCE hIns;
TCHAR szTitle[100];					// 标题栏文本
TCHAR szWindowClass[100];			// 主窗口类名

Player *player;
Manager *manager;
MapManager *mm;
WindowManager *wm;
EditorManager *em;
WindowUpdator *windowUpdator;

ATOM	MyRegisterClass(HINSTANCE);
BOOL	InitInstance(HINSTANCE, int);
LRESULT	CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK FIGHT(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK SHOP(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK ABOUT(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK EDITOR(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MSG msg;
	hIns = hInstance;

	mm = new MapManager;
	windowUpdator = new WindowUpdator(hInstance);

	LoadString(hInstance, IDS_MAGICTOWER, szTitle, 100);
	LoadString(hInstance, IDS_MAGICTOWER, szWindowClass, 100);

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance){
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	winclass.lpszMenuName = (LPCWSTR)IDR_MENU1;
	winclass.lpszClassName = szWindowClass;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&winclass);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
	HWND hWnd;
	
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	hWnd = CreateWindowEx(NULL,
		szWindowClass,
		szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		x / 2 - MAINWINDOW_WIDTH / 2,
		y / 2 - MAINWINDOW_HEIGHT / 2,
		MAINWINDOW_WIDTH,
		MAINWINDOW_HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

int dir = 0;
void MainOnTimer(){
	manager->OnKeyDown(dir, mm, wm);
	windowUpdator->UpdateMainWindow();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hDC, hDCMem;
	HBITMAP hOrgBmp, hOldBmp;
	static bool flag = false;

	switch (message){
	case WM_CREATE:
		//添加窗口句柄到窗口更新器中
		windowUpdator->setHMainWindow(hWnd);
		//初始化用来控制主窗口的Manager类
		manager = new Manager(windowUpdator->getHIns(), hWnd);
		//初始化用来调用其它子窗口的WindowManager类
		wm = new WindowManager(windowUpdator->getHIns(), hWnd);
		player = manager->getPlayer();
		return 0;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		//创建与当前DC兼容的内存DC
		hDCMem = CreateCompatibleDC(hDC);
		hOrgBmp = LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BACKGROUND));
		//将该位图选入到内存DC中
		hOldBmp = (HBITMAP)SelectObject(hDCMem, hOrgBmp);
		//在缓冲区中绘图
		manager->DrawMap(hDCMem, mm);
		manager->PrintPlayerInfo(hDCMem);
		//将缓冲区图像复制到显示缓冲区
		BitBlt(hDC, 0, 0, 800, 630, hDCMem, 0, 0, SRCCOPY);
		SelectObject(hDCMem, hOldBmp);
		//释放资源
		DeleteDC(hDCMem);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		wm->PlayerCanWalk = true;
		if (!flag){
			flag = true;
			dir = manager->GetDirection(wParam);
			manager->OnKeyDown(dir, mm, wm);
			windowUpdator->UpdateMainWindow();
			SetTimer(hWnd, MAIN_TIMER_ID, MAIN_TIMER_DELAY, (TIMERPROC)MainOnTimer);
		}
		return 0;
	case WM_KEYUP:
		wm->PlayerCanWalk = false;
		flag = false;
		KillTimer(hWnd, MAIN_TIMER_ID);
		return 0;
	case WM_COMMAND:
		//若处理消息则返回0，未处理消息则由DefWindowProc处理
		switch (LOWORD(wParam)){
		case IDM_ABOUT:
			DialogBox(hIns, (LPCTSTR)IDD_ABOUT, hWnd, (DLGPROC)ABOUT);
			return 0;
		case IDM_EDITOR:
			DialogBox(hIns, (LPCTSTR)IDD_EDITOR, hWnd, (DLGPROC)EDITOR);
			return 0;
		}
		break;
	case WM_DESTROY:
		delete manager;
		delete wm;
		delete em;
		delete windowUpdator;
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK FIGHT(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message){
	case WM_INITDIALOG:
		//开启计时器
		SetTimer(hDlg, FIGHT_TIMER_ID, FIGHT_TIMER_DELAY, NULL);
		//根据玩家和怪物的数据初始化战斗窗口的各个标签
		InitFightWindowText(wm, manager->getPlayer(), hDlg);
		//添加窗口句柄到窗口更新器中
		windowUpdator->setHFightWindow(hDlg);
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		//显示怪物的图片,因为通过这种方式显示的图片刷新就会消失，所以要每一帧都显示一遍
		manager->Search(wm->getEnemyId())->BitBlt(hdc, 280, 70);
		//更新玩家和怪物的血量
		SetWindowText(GetDlgItem(hDlg, IDC_ENEMY_HEALTH), IntToWString(wm->getEnemyHealth()).c_str());
		SetWindowText(GetDlgItem(hDlg, IDC_PLAYER_HEALTH), IntToWString(player->getHealth()).c_str());
		EndPaint(hDlg, &ps);
		return TRUE;
	case WM_TIMER:
		FightTimer(wm, manager->getPlayer(), hDlg, wParam);
		windowUpdator->UpdateFightWindow();
		windowUpdator->UpdateMainWindow();
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK SHOP(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
	case WM_COMMAND:
		ShopOnCommand(player, hDlg, wParam);
		windowUpdator->UpdateMainWindow();
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK EDITOR(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	bool ret = false;

	switch (message){
	case WM_INITDIALOG:
		em = new EditorManager(hIns, hDlg, mm);
		//添加窗口句柄到窗口更新器中
		windowUpdator->setHEditorWindow(hDlg);
		return TRUE;
	case WM_LBUTTONDOWN:
		em->OnLButtonDown(hDlg, lParam);
		windowUpdator->UpdateEditorWindow();
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		em->OnPaint(hdc);
		EndPaint(hDlg, &ps);
		return TRUE;
	case WM_COMMAND:
		ret = em->OnCommand(hDlg, message, wParam, lParam);
		windowUpdator->UpdateEditorWindow();
		return ret;
	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK ABOUT(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message){
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK){
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));
		return TRUE;
		break;
	}
	return FALSE;
}