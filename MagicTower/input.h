#ifndef INPUT_H
#define INPUT_H

#include "manager.h"

void KeyDown(Manager *m, WPARAM wparam, int map[][11][11], int currentFloor){

	switch (wparam){
	case VK_UP:
		if (pos.y>0){
			switch (map[currentFloor - 1][pos.y - 1][pos.x]){
			case ROAD:
				pos.y--;
				break;
			case UPSTAIR:
				pos.y--;
				currentFloor++;
				break;
			case DOWNSTAIR:
				pos.y--;
				currentFloor--;
				break;
			default:
				func(hwnd, UP);
			}
		}
		break;
	case VK_DOWN:
		if (pos.y<10)
		{
			switch (map[currentFloor - 1][pos.y + 1][pos.x])
			{
			case ROAD:
				pos.y++;
				break;
			case UPSTAIR:
				pos.y++;
				currentFloor++;
				break;
			case DOWNSTAIR:
				pos.y++;
				currentFloor--;
				break;
			default:
				func(hwnd, DOWN);
			}
		}
		break;
	case VK_LEFT:
		if (pos.x>0)
		{
			switch (map[currentFloor - 1][pos.y][pos.x - 1])
			{
			case ROAD:
				pos.x--;
				break;
			case UPSTAIR:
				pos.x--;
				currentFloor++;
				break;
			case DOWNSTAIR:
				pos.x--;
				currentFloor--;
				break;
			default:
				func(hwnd, LEFT);
			}
		}
		break;
	case VK_RIGHT:
		if (pos.x<10)
		{
			switch (map[currentFloor - 1][pos.y][pos.x + 1])
			{
			case ROAD:
				pos.x++;
				break;
			case UPSTAIR:
				pos.x++;
				currentFloor++;
				break;
			case DOWNSTAIR:
				pos.x++;
				currentFloor--;
				break;
			default:
				func(hwnd, RIGHT);
			}
		}
		break;
	}
}

void func(HWND hwnd, int dir)
{
	int y, x;
	switch (dir)
	{
	case UP:
		y = pos.y - 1;
		x = pos.x;
		break;
	case DOWN:
		y = pos.y + 1;
		x = pos.x;
		break;
	case LEFT:
		y = pos.y;
		x = pos.x - 1;
		break;
	case RIGHT:
		y = pos.y;
		x = pos.x + 1;
		break;
	}
	manager.Search(map[currentFloor - 1][y][x])->function(hwnd,currentFloor,x,y);
	
	switch (map[currentFloor - 1][y][x])
	{
	case DOOR:
		if (key>0)
		{
			map[currentFloor - 1][y][x] = 0;
			key--;
		}
		break;
	case KEY:
		map[currentFloor - 1][y][x] = 0;
		key++;
		break;
	case SHOP:
		DialogBox(hIns, (LPCTSTR)IDD_SHOP, hwnd, (DLGPROC)Shop);
		break;
	case BLUEGEM:
		map[currentFloor - 1][y][x] = 0;
		dfs += 3;
		break;
	case REDGEM:
		map[currentFloor - 1][y][x] = 0;
		atk += 3;
		break;
	case SMALLMED:
		map[currentFloor - 1][y][x] = 0;
		hp += 200;
		break;
	case BIGMED:
		map[currentFloor - 1][y][x] = 0;
		hp += 500;
		break;
	case GREENSLIME:
		//pMp = &monster_properties[0];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pGreenSlime;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case REDSLIME:
		pMp = &monster_properties[1];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pRedSlime;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case BLACKSLIME:
		pMp = &monster_properties[2];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pBlackSlime;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case SKELETON:
		pMp = &monster_properties[3];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pSkeleton;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case SKELETONSOLDIER:
		pMp = &monster_properties[4];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pSkeletonSoldier;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case SKELETONCAPTAIN:
		pMp = &monster_properties[5];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pSkeletonCaptain;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case SMALLBAT:
		pMp = &monster_properties[6];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pSmallBat;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case BIGBAT:
		pMp = &monster_properties[7];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pBigBat;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	case REDBAT:
		pMp = &monster_properties[8];
		if (pMp->dfs<atk && CalcDamage(hp, *pMp))
		{
			pBitmap = pRedBat;
			DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
			map[currentFloor - 1][y][x] = 0;
		}
		break;
	}
}
#endif