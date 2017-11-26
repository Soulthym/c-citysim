#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "lib/libs.h"

#define NUMBEROFCARS 60

#define NORTH 1
#define EAST  2
#define SOUTH 4
#define WEST  8

#define cango(dir, a) a & dir

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
}mape;

typedef struct {
	mape **map;
	int x;
	int y;
}map;

typedef struct{
	int x;
	int y;
	char direction;
	char *color;
	char *disp;
}car;

#endif
