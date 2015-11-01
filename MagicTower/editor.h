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
	void OnLButtonDown(HWND hWnd, LPARAM lparam);
	void OnPaint(HDC hdc);
private:
	void OnLoad(HWND hwnd);
	void OnSave(HWND hwnd);
	void OnCreate(HWND hwnd);
	string ItemTextToString(HWND hwnd, int ItemID);
	Manager *manager;
	MapManager *mapManager;
	int map[11][11];
	HWND hWnd;
	//选择物体类型后将类型保存在此，在地图上点击时读取这里的数据
	int StoringId;
	//载入地图成功后flag为true，OnPaint函数开始将地图里的数据显示到屏幕上
	bool flag;
};

//由控件id获取控件的text属性
string EditorManager::ItemTextToString(HWND hWnd, int ItemID){
	wchar_t *fileName;
	HWND hFile;
	int fileNameLength;
	char path[20];

	hFile = GetDlgItem(hWnd, IDC_FILE);
	fileNameLength = GetWindowTextLength(hFile);
	fileName = (wchar_t*)malloc(fileNameLength + 6);
	GetWindowText(hFile, fileName, fileNameLength + 1);
	sprintf_s(path, "map\\%s.txt", fileName);
	free(fileName);
	return path;
}

void EditorManager::OnLoad(HWND hWnd){
	fstream fs;
	string path;

	path = ItemTextToString(hWnd, IDC_FILE);
	fs.open(path, ios::_Nocreate | ios::in);

	if (fs){
		for (int y = 0; y < 11; y++){
			for (int x = 0; x < 11; x++){
				fs >> map[y][x];
			}
		}
		fs.close();
		flag = true;
	}
	else {
		MessageBox(hWnd, L"file doesn't exist", L"error", 0);
	}
}

void EditorManager::OnSave(HWND hWnd){
	fstream fs;
	string path;

	path = ItemTextToString(hWnd, IDC_FILE);
	fs.open(path, ios::_Nocreate | ios::out | ios::trunc);

	if (fs){
		for (int y = 0; y < 11; y++){
			for (int x = 0; x < 11; x++){
				fs << map[y][x] << " ";
			}
			fs << "\n";
		}
		fs.close();
		MessageBox(hWnd, L"file saved!", L"success", 0);
	}
	else {
		MessageBox(hWnd, L"file doesn't exist", L"error", 0);
	}
}

void EditorManager::OnCreate(HWND hWnd){
	fstream fs;
	string path;

	path = ItemTextToString(hWnd, IDC_FILE);
	fs.open(path, ios::_Nocreate);
	if (fs){
		MessageBox(hWnd, L"file already exist", L"error", 0);
		fs.close();
	}
	else {
		fs.open(path, ios::out);
		for (int y = 0; y < 11; y++){
			for (int x = 0; x < 11; x++){
				fs << "0 ";
			}
			fs << "\n";
		}
		fs.close();
		MessageBox(hWnd, L"file created!", L"success", 0);
	}
}

LRESULT EditorManager::OnCommand(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam){
	switch (LOWORD(wparam)){
	default:
		return FALSE;
	case IDC_LOAD:
		OnLoad(hWnd);
		return TRUE;
	case IDC_SAVE:
		OnSave(hWnd);
		return TRUE;
	case IDC_CREATE:
		OnCreate(hWnd);
		return TRUE;
	case IDC_WALL:
		StoringId = ID_WALL;
		return TRUE;
	case IDC_ROAD:
		StoringId = ID_ROAD;
		return TRUE;
	case IDC_UPSTAIR:
		StoringId = ID_UPSTAIRS;
		return TRUE;
	case IDC_DOWNSTAIR:
		StoringId = ID_DOWNSTAIRS;
		return TRUE;
	case IDC_DOOR:
		StoringId = ID_DOOR;
		return TRUE;
	case IDC_KEY:
		StoringId = ID_KEY;
		return TRUE;
	case IDC_SHOP:
		StoringId = ID_SHOP;
		return TRUE;
	case IDC_BLUEGEM:
		StoringId = ID_BLUEGEM;
		return TRUE;
	case IDC_REDGEM:
		StoringId = ID_REDGEM;
		return TRUE;
	case IDC_SMALLMED:
		StoringId = ID_SMALLMED;
		return TRUE;
	case IDC_BIGMED:
		StoringId = ID_BIGMED;
		return TRUE;
	case IDC_GREENSLIME:
		StoringId = ID_GREENSLIME;
		return TRUE;
	case IDC_REDSLIME:
		StoringId = ID_REDSLIME;
		return TRUE;
	case IDC_BLACKSLIME:
		StoringId = ID_BLACKSLIME;
		return TRUE;
	case IDC_SKELETON:
		StoringId = ID_SKELETON;
		return TRUE;
	case IDC_SKELETONSOLDIER:
		StoringId = ID_SKELETONSOLDIER;
		return TRUE;
	case IDC_SKELETONCAPTAIN:
		StoringId = ID_SKELETONCAPTAIN;
		return TRUE;
	case IDC_SMALLBAT:
		StoringId = ID_SMALLBAT;
		return TRUE;
	case IDC_BIGBAT:
		StoringId = ID_BIGBAT;
		return TRUE;
	case IDC_REDBAT:
		StoringId = ID_REDBAT;
		return TRUE;
	}
}

void EditorManager::OnLButtonDown(HWND hWnd, LPARAM lparam){
	int x, y;

	x = (LOWORD(lparam) - 13) / 50;
	y = (HIWORD(lparam) - 12) / 50;
	if (LOWORD(lparam) < 630){
		//x保存的是横坐标，也就是矩阵的列，在数组中先行后列，故x在y后
		map[y][x] = StoringId;
	}
}

void EditorManager::OnPaint(HDC hdc){
	if (flag){
		manager->Search(ID_BACKGROUND)->PaintFromZero(hdc);
		for (int x = 0; x < 11; x++){
			for (int y = 0; y < 11; y++){
				//因为坐标在数组中是以x为行，y为列保存的
				//但是在屏幕上x是横坐标，也就是矩阵的列，因此要把x和y调换位置显示到屏幕上
				manager->Search(map[x][y])->Paint(hdc, y, x);
			}
		}
	}
}

#endif