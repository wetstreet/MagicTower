#ifndef EDITOR_H
#define EDITOR_H

#include <Windows.h>
#include "definitions.h"
#include "resource.h"
#include "manager.h"
#include "map.h"
#include "object.h"
using namespace std;

class EditorManager{
public:
	EditorManager(HINSTANCE hIns, HWND hwnd, MapManager *mm) :hWnd(hwnd), mapManager(mm){ manager = new Manager(hIns, hwnd); }
	LRESULT OnCommand(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void OnLButtonDown(LPARAM lparam);
	void OnPaint(HDC hdc);
private:
	Manager *manager;
	MapManager *mapManager;
	int map[11][11];
	HWND hWnd;
	int StoringId;
	bool flag = false;
};

LRESULT EditorManager::OnCommand(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam){
	wchar_t *fileName;
	HWND hFile;
	int fileNameLength;
	fstream fs;
	stringstream stream;
	char path[20];

	switch (LOWORD(wparam)){
	case IDC_LOAD:
		hFile = GetDlgItem(hWnd, IDC_FILE);
		fileNameLength = GetWindowTextLength(hFile);
		fileName = (wchar_t*)malloc(fileNameLength + 6);
		GetWindowText(hFile, fileName, fileNameLength + 1);
		sprintf_s(path, "map\\%s.txt", fileName);
		fs.open(path);
		if (fs){
			for (int y = 0; y < 11; y++){
				for (int x = 0; x < 11; x++){
					fs >> map[y][x];
				}
			}
			fs.close();
			flag = true;
		}
		else
			MessageBox(hWnd, L"file doesn't exist", L"error", 0);
		return FALSE;
	case IDC_SAVE:
		hFile = GetDlgItem(hWnd, IDC_FILE);
		fileNameLength = GetWindowTextLength(hFile);
		fileName = (wchar_t*)malloc(fileNameLength + 6);
		GetWindowText(hFile, fileName, fileNameLength + 1);
		sprintf_s(path, "map\\%s.txt", fileName);
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
		return FALSE;
	case IDC_CREATE:
		hFile = GetDlgItem(hWnd, IDC_FILE);
		fileNameLength = GetWindowTextLength(hFile);
		fileName = (wchar_t*)malloc(fileNameLength + 6);
		GetWindowText(hFile, fileName, fileNameLength + 1);
		sprintf_s(path, "map\\%s.txt", fileName);
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
		return FALSE;
	case IDC_CLOSE:
		EndDialog(hWnd, LOWORD(wparam));
		return FALSE;
	case IDC_WALL:
		StoringId = ID_WALL;
		return FALSE;
	case IDC_ROAD:
		StoringId = ID_ROAD;
		return FALSE;
	case IDC_UPSTAIR:
		StoringId = ID_UPSTAIRS;
		return FALSE;
	case IDC_DOWNSTAIR:
		StoringId = ID_DOWNSTAIRS;
		return FALSE;
	case IDC_DOOR:
		StoringId = ID_DOOR;
		return FALSE;
	case IDC_KEY:
		StoringId = ID_KEY;
		return FALSE;
	case IDC_SHOP:
		StoringId = ID_SHOP;
		return FALSE;
	case IDC_BLUEGEM:
		StoringId = ID_BLUEGEM;
		return FALSE;
	case IDC_REDGEM:
		StoringId = ID_REDGEM;
		return FALSE;
	case IDC_SMALLMED:
		StoringId = ID_SMALLMED;
		return FALSE;
	case IDC_BIGMED:
		StoringId = ID_BIGMED;
		return FALSE;
	default:
		return DefWindowProc(hWnd, msg, wparam, lparam);/*
	case IDC_GREENSLIME:
		StoringId = ID_GREENSLIME;
		return FALSE;
	case IDC_REDSLIME:
		StoringId = ID_REDSLIME;
		return FALSE;
	case IDC_BLACKSLIME:
		StoringId = ID_BLACKSLIME;
		return FALSE;
	case IDC_SKELETON:
		StoringId = ID_SKELETON;
		return FALSE;
	case IDC_SKELETONSOLDIER:
		StoringId = ID_SKELETONSOLDIER;
		return FALSE;
	case IDC_SKELETONCAPTAIN:
		StoringId = ID_SKELETONCAPTAIN;
		return FALSE;
	case IDC_SMALLBAT:
		StoringId = ID_SMALLBAT;
		return FALSE;
	case IDC_BIGBAT:
		StoringId = ID_BIGBAT;
		return FALSE;
	case IDC_REDBAT:
		StoringId = ID_REDBAT;
		return FALSE;*/
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
	if (flag){
		manager->Search(ID_BACKGROUND)->PaintFromZero(hdc);
		for (int y = 0; y < 11; y++){
			for (int x = 0; x < 11; x++){
				manager->Search(map[x][y])->Paint(hdc, y, x);
			}
		}
	}
}

#endif