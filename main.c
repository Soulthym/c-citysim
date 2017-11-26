#include "main.h"
const struct color COLOR = {
  .FBLA =	"\x1b[30m",	.FRED =	"\x1b[31m",	.FGRE =	"\x1b[32m",	.FYEL =	"\x1b[33m",	.FBLU =	"\x1b[34m",	.FMAG =	"\x1b[35m",	.FCYA =	"\x1b[36m",	.FWHI =	"\x1b[37m",	.BBLA =	"\x1b[40m",	.BRED =	"\x1b[41m",	.BGRE =	"\x1b[42m",	.BYEL =	"\x1b[43m",	.BBLU =	"\x1b[44m",	.BMAG =	"\x1b[45m",	.BCYA =	"\x1b[46m",	.BWHI =	"\x1b[47m",	.RES = 	"\x1b[0m",	.BOL = 	"\x1b[1m",	.BLI = 	"\x1b[5m",	.REV = 	"\x1b[7m",	.CON = 	"\x1b[8m"
};
const struct sprite SPRITE = {
  .car = "🚘", .walker = "0"
};

int hextoi(char c) {
  if (c == '.') {
    return 0;
  }
	else if (c <= '9' && c >= '1') {
		return (int) c-'0';
	} else {
		return (int) c-'A'+10;
	}
}
void Pause() {
	getchar();
}
void AffMapElement(map *M, int y, int x) {
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
	   printf("\033[%d;%dH%s%s", y+1, x+1, M->map[y][x].color, M->map[y][x].disp);
   }
}
void AffMap(map *M) {
  printf("\033[2J\033[1;1H");
	for (int y = 0; y < M->y; y ++) {
		for (int x = 0; x < M->x; x++) {
			AffMapElement(M, y, x);
		}
		printf("\n");
	}
}
map *LoadMap(map *M, char *fmap, char *fcolor, char *fppiet, char *fpvoit, char *fptrain, char *fpmap){
	FILE *FM = fopen(fmap, "r");
	FILE *FC = fopen(fcolor, "r");
	FILE *FPP = fopen(fppiet, "r");
	FILE *FPV = fopen(fpvoit, "r");
	FILE *FPT = fopen(fptrain, "r");
	FILE *FPM = fopen(fpmap, "r");
	if (FM == NULL) {
		printf(">>%s not found\n", fmap);
	} else if (FC == NULL){
		fclose(FM);
		printf(">>%s not found\n", fcolor);
	} else if (FPP == NULL){
		fclose(FM);
		fclose(FC);
		printf(">>%s not found\n", fppiet);
	} else if (FPV == NULL){
		fclose(FM);
		fclose(FC);
		fclose(FPP);
		printf(">>%s not found\n", fpvoit);
	} else if (FPT == NULL){
		fclose(FM);
		fclose(FC);
		fclose(FPP);
		fclose(FPV);
		printf(">>%s not found\n", fptrain);
	} else if (FPM == NULL){
		fclose(FM);
		fclose(FC);
		fclose(FPP);
		fclose(FPV);
		fclose(FPT);
		printf(">>%s not found\n", fpmap);
	} else {
		fscanf(FM,"%d %d\n", &M->x, &M->y);
		M->map = malloc(sizeof(mape*) * M->y);
		for (int y = 0; y < M->y; y++) {
			M->map[y] = malloc(sizeof(mape) * M->x);
		}
    //FM,FC,FPP,FPV,FPT,FPM
		char cm,cc,cpp,cpv,cpt,cpm;
		for (int y = 0; y < M->y; y++) {
			for (int x = 0; x < M->x; x++) {
				M->map[y][x].disp = malloc(sizeof(char) * 4);
				cm = fgetc(FM);
				cc = fgetc(FC);
        cpp = fgetc(FPP);
        cpv = fgetc(FPV);
        cpt = fgetc(FPT);
        cpm = fgetc(FPM);
        M->map[y][x].walkerProp = hextoi(cpp);
        M->map[y][x].carProp = hextoi(cpv);
        M->map[y][x].trainProp = hextoi(cpt);
        M->map[y][x].mapProp = hextoi(cpm);
        M->map[y][x].occupied = 0;
        M->map[y][x].disp[0] = cm;
				if (!(cm & 128)) {
					M->map[y][x].disp[1] = '\0';
				} else {
					M->map[y][x].disp[1] = fgetc(FM);
					M->map[y][x].disp[2] = fgetc(FM);
					M->map[y][x].disp[3] = '\0';
				}
				switch (cc) {
					case 'K':
						M->map[y][x].color = COLOR.FBLA;
						break;
					case 'R':
						M->map[y][x].color = COLOR.FRED;
						break;
					case 'G':
						M->map[y][x].color = COLOR.FGRE;
						break;
					case 'Y':
						M->map[y][x].color = COLOR.FYEL;
						break;
					case 'B':
						M->map[y][x].color = COLOR.FBLU;
						break;
					case 'M':
						M->map[y][x].color = COLOR.FMAG;
						break;
					case 'C':
						M->map[y][x].color = COLOR.FCYA;
						break;
					case 'W':
						M->map[y][x].color = COLOR.FWHI;
						break;
					default :
						M->map[y][x].color = COLOR.RES;
						break;
				}
			}
			fgetc(FM);
			fgetc(FC);
			fgetc(FPP);
			fgetc(FPV);
			fgetc(FPT);
			fgetc(FPM);
		}
		fclose(FM);
		fclose(FC);
		fclose(FPP);
		fclose(FPV);
		fclose(FPT);
		fclose(FPM);
	}
	return M;
}
car* NewCar(int posx, int posy, char direction, char* color) {
	car *C = malloc(sizeof(car));
	C->x = posx;
	C->y = posy;
	C->direction = direction;
	C->disp = SPRITE.car; //["🚘","🚗"]
  C->color = color;
	return C;
}
void PrintCar(car *C) {
  printf("\033[%d;%dH  \033[%d;%dH%s%s",C->y+1, C->x+1, C->y+1, C->x+1, C->color, C->disp);
}
void PrintCars(car **C){
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    if (C[i] != NULL) {
      PrintCar(C[i]);
    }
  }
}
void EraseCar(car *C, map *M) {
  AffMapElement(M, C->y, C->x);
  AffMapElement(M, C->y, C->x+1);
}
void EraseCars(car **C, map *M) {
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    if (C[i] != NULL) {
      EraseCar(C[i], M);
    }
  }
}
int main(int argc, char **argv) {
  map M;
  LoadMap(&M,"data/map_rendu","data/map_color","data/pieton_carac","data/voiture_carac","data/train_carac","data/map_carac");
  AffMap(&M);
  car *C[NUMBEROFCARS] = {NULL};
  for (size_t i = 0; i < 54; i++) {
    C[i] = NewCar(i*2+1,0,0,COLOR.FRED);
    PrintCars(C);
    Pause();
    EraseCars(C, &M);
  }
  printf("\033[36;1H%s", COLOR.RES);
	return 0;
}
