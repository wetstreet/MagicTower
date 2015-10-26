#ifndef EDITOR_H
#define EDITOR_H

#include <Windows.h>
#include "resource.h"
#include "object.h"
using namespace std;

class EditorManager{
public:
	EditorManager(HWND hwnd) :hWnd(hwnd){}
	void OnObjectSelected(WPARAM wparam);
	void OnLButtonDown(LPARAM lparam);
	void OnPaint(HDC hdc);
private:
	Object *p;
	int map[11][11];
	HWND hWnd;
	int StoringId;
};

void EditorManager::OnObjectSelected(WPARAM wparam){
	LPWSTR number = nullptr;
	fstream fs;
	stringstream stream;
	char path[20];

	switch (LOWORD(wparam)){
	case IDC_LOAD:
		GetWindowText(GetDlgItem(hWnd, IDC_FILE), number, 10);
		sprintf_s(path, "map\\%s.txt", number);
		fs.open(path);
		if (fs){
			for (int y = 0; y < 11; y++){
				for (int x = 0; x < 11; x++){
					fs >> map[y][x];
				}
			}
			fs.close();
		}
		else
			MessageBox(hWnd, L"file doesn't exist", L"error", 0);
	case IDC_SAVE:
		GetWindowText(GetDlgItem(hWnd, IDC_FILE), number, 10);
		sprintf_s(path, "map\\%s.txt", number);
		fs.open(path);
		if (fs){
			for (int y = 0; y < 11; y++){
				for (int x = 0; x < 11; x++){
					fs << map[y][x];
				}
				fs << "\n";
			}
			fs.close();
			MessageBox(hWnd, L"file saved!", L"success", 0);
		}
		else
			MessageBox(hWnd, L"file doesn't exist", L"error", 0);
	case IDC_CREATE:
		GetWindowText(GetDlgItem(hWnd, IDC_FILE), number, 10);
		sprintf_s(path, "map\\%s.txt", number);
		fs.open(path,ios::in);
		if (fs){
			MessageBox(hWnd, L"file already exist", L"error", 0);
			fs.close();
		} else {
			fs.open(path);
			for (int y = 0; y < 11; y++){
				for (int x = 0; x < 11; x++){
					fs << "0 ";
				}
				fs << "\n";
			}
			fs.close();
			MessageBox(hWnd, L"file created!", L"success", 0);
		}
	case IDC_CLOSE:
		EndDialog(hWnd, LOWORD(wparam));
	case IDC_WALL:
		StoringId = ID_WALL;
	case IDC_ROAD:
		StoringId = ID_ROAD;
	case IDC_UPSTAIR:
		StoringId = ID_UPSTAIRS;
	case IDC_DOWNSTAIR:
		StoringId = ID_DOWNSTAIRS;
	case IDC_DOOR:
		StoringId = ID_DOOR;
	case IDC_KEY:
		StoringId = ID_KEY;
	case IDC_SHOP:
		StoringId = ID_SHOP;
	case IDC_BLUEGEM:
		StoringId = ID_BLUEGEM;
	case IDC_REDGEM:
		StoringId = ID_REDGEM;
	case IDC_SMALLMED:
		StoringId = ID_SMALLMED;
	case IDC_BIGMED:
		StoringId = ID_BIGMED;/*
	case IDC_GREENSLIME:
		StoringId = ID_GREENSLIME;
	case IDC_REDSLIME:
		StoringId = ID_REDSLIME;
	case IDC_BLACKSLIME:
		StoringId = ID_BLACKSLIME;
	case IDC_SKELETON:
		StoringId = ID_SKELETON;
	case IDC_SKELETONSOLDIER:
		StoringId = ID_SKELETONSOLDIER;
	case IDC_SKELETONCAPTAIN:
		StoringId = ID_SKELETONCAPTAIN;
	case IDC_SMALLBAT:
		StoringId = ID_SMALLBAT;
	case IDC_BIGBAT:
		StoringId = ID_BIGBAT;
	case IDC_REDBAT:
		StoringId = ID_REDBAT;*/
	}
}

void EditorManager::OnLButtonDown(LPARAM lparam){
	/*
	HDC hdc;
	hdc = GetDC(hWnd);
	s_x = (LOWORD(lparam) - EDITOR_X) / 50;
	s_y = (HIWORD(lparam) - g_y) / 50;
	TextOut(hdc, 0, 0, buffer, sprintf(buffer, "%d,%d", s_x, s_y));
	ReleaseDC(hWnd, hdc);
	if (LOWORD(lparam)>EDITOR_X)
		for (i = 0; i<dim(n_m); i++)
			if (StoringId == i)
				editor_map[s_y][s_x] = i;*/
}

void EditorManager::OnPaint(HDC hdc){
	/*
	if (nFlag){
		pBackground->BitBlt(hdc, EDITOR_X - g_x, 0);
		for (y = 0; y<11; y++)
			for (x = 0; x<11; x++)
				for (i = 0; i<dim(n_m); i++)
					if (editor_map[y][x] == i){
						(*n_m[i].p)->BitBlt(hdc, EDITOR_X + 50 * x, g_y + 50 * y);
					}
	}*/
}

#endif