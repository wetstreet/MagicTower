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

ATOM MyRegisterClass(HINSTANCE hinstance){
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
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
	
	hWnd = CreateWindowEx(NULL,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 630,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam){
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg){
	case WM_CREATE:
		//添加窗口句柄到窗口更新器中
		windowUpdator->setHMainWindow(hWnd);
		//初始化用来控制主窗口的Manager类
		manager = new Manager(windowUpdator->getHIns(), hWnd);
		//初始化用来调用其它子窗口的WindowManager类
		wm = new WindowManager(windowUpdator->getHIns(), hWnd);
		player = manager->getPlayer();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		manager->DrawMap(hdc, mm);
		manager->PrintPlayerInfo(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		manager->OnKeyDown(wparam, mm, wm);
		windowUpdator->UpdateMainWindow();
		break;
	case WM_COMMAND:
		switch (LOWORD(wparam)){
		case IDM_ABOUT:
			DialogBox(hIns, (LPCTSTR)IDD_ABOUT, hWnd, (DLGPROC)ABOUT);
			break;
		case IDM_EDITOR:
			DialogBox(hIns, (LPCTSTR)IDD_EDITOR, hWnd, (DLGPROC)EDITOR);
			break;
		default:
			return DefWindowProc(hWnd, msg, wparam, lparam);
		}
		break;
	case WM_DESTROY:
		delete manager;
		delete wm;
		delete em;
		delete windowUpdator;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wparam, lparam);
	}
	return 0;
}

LRESULT CALLBACK FIGHT(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam){
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg){
	case WM_INITDIALOG:
		//开启计时器
		SetTimer(hWnd, FIGHT_TIMER, TIME_DELAY, NULL);
		//根据玩家和怪物的数据初始化战斗窗口的各个标签
		InitFightWindowText(wm, manager->getPlayer(), hWnd);
		//添加窗口句柄到窗口更新器中
		windowUpdator->setHFightWindow(hWnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//显示怪物的图片
		manager->Search(wm->getEnemyId())->BitBlt(hdc, 280, 70);
		//更新玩家和怪物的血量
		SetWindowText(GetDlgItem(hWnd, IDC_ENEMY_HEALTH), IntToWString(wm->getEnemyHealth()).c_str());
		SetWindowText(GetDlgItem(hWnd, IDC_PLAYER_HEALTH), IntToWString(player->getHealth()).c_str());
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		FightTimer(wm, manager->getPlayer(), hWnd, wparam);
		windowUpdator->UpdateFightWindow();
		windowUpdator->UpdateMainWindow();
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK SHOP(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg){
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return TRUE;
	case WM_COMMAND:
		Shopping(player, wparam, hwnd);
		windowUpdator->UpdateMainWindow();
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK EDITOR(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam){
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg){
	case WM_INITDIALOG:
		em = new EditorManager(hWnd);
		//添加窗口句柄到窗口更新器中
		windowUpdator->setHEditorWindow(hWnd);
		return TRUE;
	case WM_LBUTTONDOWN:
		em->OnLButtonDown(lparam);
		windowUpdator->UpdateEditorWindow();
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		em->OnPaint(hdc);
		EndPaint(hWnd, &ps);
		return TRUE;
	case WM_COMMAND:
		em->OnObjectSelected(wparam);
		windowUpdator->UpdateEditorWindow();
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK ABOUT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg){
	case WM_INITDIALOG:
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wparam) == IDOK){
			EndDialog(hwnd, LOWORD(wparam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}