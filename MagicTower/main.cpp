#include "resource.h"
#include "definitions.h"
#include "manager.h"
#include "general.h"
#include "map.h"
#include "input.h"

HINSTANCE hIns;
TCHAR szTitle[100];					// 标题栏文本
TCHAR szWindowClass[100];			// 主窗口类名

Manager *manager;
MapManager *mm;
WindowUpdator *windowUpdator;
/*
Enemy monster_properties[9] = {
	{ 50, 20, 1, 1 },
	{ 70, 15, 2, 2 },
	{ 200, 35, 10, 5 },
	{ 110, 25, 5, 5 },
	{ 150, 40, 20, 8 },
	{ 400, 90, 50, 15 },
	{ 100, 20, 5, 3 },
	{ 150, 60, 35, 10 },
	{ 550, 160, 90, 25 } };*/

void func(HWND, int);
ATOM	MyRegisterClass(HINSTANCE);
BOOL	InitInstance(HINSTANCE, int);
LRESULT	CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
//LRESULT	CALLBACK ABOUT(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK FIGHT(HWND, UINT, WPARAM, LPARAM);
//LRESULT	CALLBACK EDITOR(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK Shop(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	MSG msg;
	//在这里初始化manager是因为需要参数hInstance
	manager = new Manager(hInstance);
	hIns = hInstance;

	LoadString(hInstance, IDS_MAGICTOWER, szTitle, 100);
	LoadString(hInstance, IDS_MAGICTOWER, szWindowClass, 100);

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hinstance)
{
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

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
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
	/*
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);*/

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
		windowUpdator = new WindowUpdator(hwnd);
		mm = new MapManager;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		manager->DrawMap(hdc, mm);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		KeyDown(manager, wparam, mm);
		windowUpdator->Update();
		break;
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case IDM_ABOUT:
			//DialogBox(hIns, (LPCTSTR)IDD_ABOUT, hwnd, (DLGPROC)ABOUT);
			break;
		case IDM_EDITOR:
			//DialogBox(hIns, (LPCTSTR)IDD_EDITOR, hwnd, (DLGPROC)EDITOR);
			break;
		default:
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}
/*
LRESULT CALLBACK FIGHT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	LPCWSTR buffer;
	char b[20];
	static Enemy m = *pMp;

	switch (msg)
	{
	case WM_INITDIALOG:
		m.hp = pMp->hp;
		SetTimer(hwnd, 1, 300, NULL);
		if (sprintf(b, "%d", m.hp))
			SetWindowText(GetDlgItem(hwnd, IDC_MONSTER_HEALTH), buffer);
		if (sprintf(b, "%d", m.atk))
			SetWindowText(GetDlgItem(hwnd, IDC_MONSTER_ATTACK), buffer);
		if (sprintf(b, "%d", m.dfs))
			SetWindowText(GetDlgItem(hwnd, IDC_MONSTER_DEFENSE), buffer);
		if (sprintf(b, "%d", hp))
			SetWindowText(GetDlgItem(hwnd, IDC_PLAYER_HEALTH), buffer);
		if (sprintf(b, "%d", atk))
			SetWindowText(GetDlgItem(hwnd, IDC_PLAYER_ATTACK), buffer);
		if (sprintf(b, "%d", dfs))
			SetWindowText(GetDlgItem(hwnd, IDC_PLAYER_DEFENSE), buffer);
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		pBitmap->BitBlt(hdc, 76, 47);
		if (sprintf(buffer, "%d", m.hp))
			SetWindowText(GetDlgItem(hwnd, IDC_MONSTER_HEALTH), buffer);
		if (sprintf(buffer, "%d", hp))
			SetWindowText(GetDlgItem(hwnd, IDC_PLAYER_HEALTH), buffer);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		break;
	case WM_TIMER:
		m.hp -= (atk - m.dfs);
		if (m.hp <= 0)
		{
			money += m.money;
			KillTimer(hwnd, 1);
			EndDialog(hwnd, LOWORD(wparam));
		}
		else
			hp -= (m.atk - dfs);
		windowUpdator->Update();
		return TRUE;
	}
	return FALSE;
}*/
/*
LRESULT CALLBACK EDITOR(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static int editor_map[11][11], nFlag, status, s_x, s_y;
	int x, y, i;
	HDC hdc;
	PAINTSTRUCT ps;
	FILE *fp;
	char number[10], buffer[20];
	static char path[20];

	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		s_x = (LOWORD(lparam) - EDITOR_X) / 50;
		s_y = (HIWORD(lparam) - g_y) / 50;
		TextOut(hdc, 0, 0, buffer, sprintf(buffer, "%d,%d", s_x, s_y));
		ReleaseDC(hwnd, hdc);
		if (LOWORD(lparam)>EDITOR_X)
			for (i = 0; i<dim(n_m); i++)
				if (status == i)
					editor_map[s_y][s_x] = i;
		windowUpdator->Update();
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (nFlag)
		{
			pBackground->BitBlt(hdc, EDITOR_X - g_x, 0);
			for (y = 0; y<11; y++)
				for (x = 0; x<11; x++)
					for (i = 0; i<dim(n_m); i++)
						if (editor_map[y][x] == i)
						{
							(*n_m[i].p)->BitBlt(hdc, EDITOR_X + 50 * x, g_y + 50 * y);
						}
		}
		EndPaint(hwnd, &ps);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case IDC_LOAD:
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), number, 10);
			sprintf(path, "map\\%s.txt", number);
			if (fp = fopen(path, "r"))
			{
				for (y = 0; y<11; y++)
				{
					for (x = 0; x<11; x++)
					{
						fscanf(fp, "%d", &editor_map[y][x]);
					}
				}
				fclose(fp);
				nFlag = 1;
				windowUpdator->Update();
			}
			else
				MessageBox(hwnd, "file doesn't exist", "error", 0);
			return TRUE;
		case IDC_SAVE:
			if (fp = fopen(path, "w"))
			{
				for (y = 0; y<11; y++)
				{
					for (x = 0; x<11; x++)
					{
						fprintf(fp, "%d ", editor_map[y][x]);
					}
					fprintf(fp, "\n");
				}
				fclose(fp);
				MessageBox(hwnd, "file saved!", "success", 0);
			}
			else
				MessageBox(hwnd, "file doesn't exist", "error", 0);
			return TRUE;
		case IDC_CREATE:
			GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), number, 10);
			sprintf(path, "map\\%s.txt", number);
			if (fp = fopen(path, "r"))
			{
				MessageBox(hwnd, "file already exist", "error", 0);
				fclose(fp);
			}
			else
			{
				fp = fopen(path, "w");
				for (y = 0; y<11; y++)
				{
					for (x = 0; x<11; x++)
					{
						fprintf(fp, "0 ");
					}
					fprintf(fp, "\n");
				}
				fclose(fp);
				MessageBox(hwnd, "file created!", "success", 0);
			}
			return TRUE;
		case IDC_CLOSE:
			EndDialog(hwnd, LOWORD(wparam));
			return TRUE;
		case IDC_WALL:
			status = WALL;
			return TRUE;
		case IDC_ROAD:
			status = ROAD;
			return TRUE;
		case IDC_UPSTAIR:
			status = UPSTAIR;
			return TRUE;
		case IDC_DOWNSTAIR:
			status = DOWNSTAIR;
			return TRUE;
		case IDC_DOOR:
			status = DOOR;
			return TRUE;
		case IDC_KEY:
			status = KEY;
			return TRUE;
		case IDC_SHOP:
			status = SHOP;
			return TRUE;
		case IDC_BLUEGEM:
			status = BLUEGEM;
			return TRUE;
		case IDC_REDGEM:
			status = REDGEM;
			return TRUE;
		case IDC_SMALLMED:
			status = SMALLMED;
			return TRUE;
		case IDC_BIGMED:
			status = BIGMED;
			return TRUE;
		case IDC_GREENSLIME:
			status = GREENSLIME;
			return TRUE;
		case IDC_REDSLIME:
			status = REDSLIME;
			return TRUE;
		case IDC_BLACKSLIME:
			status = BLACKSLIME;
			return TRUE;
		case IDC_SKELETON:
			status = SKELETON;
			return TRUE;
		case IDC_SKELETONSOLDIER:
			status = SKELETONSOLDIER;
			return TRUE;
		case IDC_SKELETONCAPTAIN:
			status = SKELETONCAPTAIN;
			return TRUE;
		case IDC_SMALLBAT:
			status = SMALLBAT;
			return TRUE;
		case IDC_BIGBAT:
			status = BIGBAT;
			return TRUE;
		case IDC_REDBAT:
			status = REDBAT;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK Shop(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case IDC_EXIT:
			EndDialog(hwnd, LOWORD(wparam));
			break;
		case IDC_BUYHP:
			if (money >= 25)
			{
				hp += 800;
				money -= 25;
			}
			break;
		case IDC_BUYATK:
			if (money >= 25)
			{
				atk += 4;
				money -= 25;
			}
			break;
		case IDC_BUYDFS:
			if (money >= 25)
			{
				dfs += 4;
				money -= 25;
			}
			break;
		default:
			return FALSE;
		}
		windowUpdator->Update();
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK ABOUT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wparam) == IDOK || LOWORD(wparam) == IDCANCEL)
		{
			EndDialog(hwnd, LOWORD(wparam));
			return TRUE;
		}
		break;
	}
	return FALSE;
	}*/