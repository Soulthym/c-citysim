#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib/libs.h"

#define NORTH 0
#define SOUTH 1
#define EAST  2
#define WEST  3

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

typedef struct {
	char *disp;
	char *color;
	int prop;
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
	char **image;
}car;

#endif