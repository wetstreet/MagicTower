#ifndef INPUT_H
#define INPUT_H

#include "manager.h"

void KeyDown(Manager *m, WPARAM wparam, MapManager *map){
	Player *p = m->getPlayer();
	int x = p->getX();
	int y = p->getY();
	int currentFloor = map->getCurrentFloor();

	switch (wparam){
	case VK_UP:
		if (y > 0){
			m->Search(map->getNumber(currentFloor, x, y - 1))->MeetPlayer(currentFloor, x, y - 1, p, map);
		}
		break;
	case VK_DOWN:
		if (y < 10){
			m->Search(map->getNumber(currentFloor, x, y + 1))->MeetPlayer(currentFloor, x, y + 1, p, map);
		}
		break;
	case VK_LEFT:
		if (x > 0){
			m->Search(map->getNumber(currentFloor, x - 1, y))->MeetPlayer(currentFloor, x - 1, y, p, map);
		}
		break;
	case VK_RIGHT:
		if (x < 10){
			m->Search(map->getNumber(currentFloor, x + 1, y))->MeetPlayer(currentFloor, x + 1, y, p, map);
		}
		break;
	}
}

//判断下一步会碰到的东西，根据不同的东西有不同的结果
/*
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
*/
#endif