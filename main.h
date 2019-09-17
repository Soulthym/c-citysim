#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <fcntl.h>

#include "lib/libs.h"

#define NUMBEROFCARS 150
#define RATEOFSPAWNCARS 10//20
#define NUMBEROFWALKERS 20//200//100
#define RATEOFSPAWNWALKERS 7//75//30
#define NUMBEROFFIRES 2


#define NORTH 1
#define EAST  2
#define SOUTH 4
#define WEST  8
#define HIDDEN 8

#define hasprop(a, b) a & b

struct color{
	char *FBLA;
	char *FRED;
	char *FGRE;
	char *FYEL;
	char *FBLU;
	char *FMAG;
	char *FCYA;
	char *FWHI;

	char *BBLA;
	char *BRED;
	char *BGRE;
	char *BYEL;
	char *BBLU;
	char *BMAG;
	char *BCYA;
	char *BWHI;

	char *RES;
	char *BOL;
	char *BLI;
	char *REV;
	char *CON;
};
extern const struct color COLOR;

struct sprite{
	char *car;
	char *walker;
	char *riviere[2];
	char *train[2][11];
};
extern const struct sprite SPRITE;

typedef struct {
	char *disp;
	char *color;
	char walkerProp;
	char carProp;
	char trainProp;
	char mapProp;
	char occupied;
	char canfree;
}mape;

typedef struct {
	mape **map;
	int x;
	int y;
}map;

typedef struct{
	int x;
	int y;
	char canPark;
	char direction;
	char *color;
	char *disp;
}car;

typedef struct{
	int x;
	int y;
	char direction;
	char *color;
	char *disp;
}walker;

typedef struct{
	char occupied;
	char *carColor;
	int spawnWalkerx;
	int spawnWalkery;
	int spawnCarx;
	int spawnCary;
} parking;

typedef struct{
	int y;
	int x;
	int timer;
	char dir;
	int unspawn[5];
	int spawn[5];
} train;

typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
	int wx1;
	int wy1;
	int wx2;
	int wy2;
	int wp1;
	int wp2;
	int cx1;
	int cy1;
	int cx2;
	int cy2;
	int cp1;
	int cp2;

	int timer;
	char *color1;
	char *color2;
}fire;

#endif
