#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define EDITOR_X 200

const int TIME_DELAY = 300;
const int FIGHT_TIMER = 1;

const int PLAYER_INIT_ATTACK = 20;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int ID_PLAYER = -2;
const int ID_BACKGROUND = -1;
const int ID_ROAD = 0;
const int ID_WALL = 1;
const int ID_UPSTAIRS = 2;
const int ID_DOWNSTAIRS = 3;
const int ID_DOOR = 4;
const int ID_KEY = 5;
const int ID_SHOP = 6;
const int ID_BLUEGEM = 7;
const int ID_REDGEM = 8;
const int ID_SMALLMED = 9;
const int ID_BIGMED = 10;
const int ID_GREENSLIME = 11;
const int ID_REDSLIME = 12;
const int ID_BLACKSLIME = 13;
const int ID_SKELETON = 14;
const int ID_SKELETONSOLDIER = 15;
const int ID_SKELETONCAPTAIN = 16;
const int ID_SMALLBAT = 17;
const int ID_BIGBAT = 18;
const int ID_REDBAT = 19;

const int TYPE_OBJECT = 0;
const int TYPE_PLAYER = 1;
const int TYPE_ENEMY = 2;
const int TYPE_ROAD = 3;
const int TYPE_UPSTAIRS = 4;
const int TYPE_DOWNSTAIRS = 5;
const int TYPE_DOOR = 6;
const int TYPE_KEY = 7;
const int TYPE_BLUEGEM = 8;
const int TYPE_REDGEM = 9;

#define dim(x) (sizeof(x)/sizeof(x[0]))

#endif