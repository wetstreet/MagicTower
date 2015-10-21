#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define EDITOR_X 200

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int PLAYER = -2;
const int BACKGROUND = -1;
const int ROAD = 0;
const int WALL = 1;
const int UPSTAIR = 2;
const int DOWNSTAIR = 3;
const int DOOR = 4;
const int KEY = 5;
const int SHOP = 6;
const int BLUEGEM = 7;
const int REDGEM = 8;
const int SMALLMED = 9;
const int BIGMED = 10;
const int GREENSLIME = 11;
const int REDSLIME = 12;
const int BLACKSLIME = 13;
const int SKELETON = 14;
const int SKELETONSOLDIER = 15;
const int SKELETONCAPTAIN = 16;
const int SMALLBAT = 17;
const int BIGBAT = 18;
const int REDBAT = 19;

#define dim(x) (sizeof(x)/sizeof(x[0]))

#endif