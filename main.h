#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/libs.h"

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
}mape;

typedef struct {
	mape **map;
	int x;
	int y;
}map;

#endif