#include "main.h"
//comment
const struct color COLOR = {
    .FBLA =	"\x1b[30m",	.FRED =	"\x1b[31m",	.FGRE =	"\x1b[32m",	.FYEL =	"\x1b[33m",	.FBLU =	"\x1b[34m",	.FMAG =	"\x1b[35m",	.FCYA =	"\x1b[36m",	.FWHI =	"\x1b[37m",	.BBLA =	"\x1b[40m",	.BRED =	"\x1b[41m",	.BGRE =	"\x1b[42m",	.BYEL =	"\x1b[43m",	.BBLU =	"\x1b[44m",	.BMAG =	"\x1b[45m",	.BCYA =	"\x1b[46m",	.BWHI =	"\x1b[47m",	.RES = 	"\x1b[0m",	.BOL = 	"\x1b[1m",	.BLI = 	"\x1b[5m",	.REV = 	"\x1b[7m",	.CON = 	"\x1b[8m"};

int hextoi(char c) {
	if (c <= '9' && c >= '0') {
		return (int) c-'0';
	} else {
		return (int) c-'A'+10;
	}
}

void Pause() {
	getchar();
}

void AffMapElement(map M, int y, int x) {
	printf("\033[%d;%dH%s%s", y+1, x+1, M.map[y][x].color, M.map[y][x].disp);
}

void AffMap(map M) {
	for (int y = 0; y < M.y; y ++) {
		for (int x = 0; x < M.x; x++) {
			// printf("%s%s", M.map[y][x].color, M.map[y][x].disp);
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
			//fgetc(FPM);			
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

car* NewCar(char* f, int posx, int posy, char direction) {
	FILE *F = fopen(f,"r");
	if (F == NULL) {
		printf(">>%s not found\n", f);
		return NULL;
	} else {
		car *C = malloc(sizeof(car));
		C->x = posx;
		C->y = posy;
		C->direction = 2;
		C->image = malloc(sizeof(char*) * 2); //["🚘","🚗"]
		for(int i = 0; i < 2; i++){
			C->image[i] = calloc(5 ,sizeof(char));
		}
		int j;
		for(int i = 0; i < 2; i++) {
			j = 0;
			for(char c = fgetc(F); c != '\n' && c!= EOF && j < 4; c = fgetc(F), j++){
				C->image[i][j] = c;
			}
		}
		fclose(F);
		return C;
	}
}

void PrintCar(car *C){
	printf("\033[%d;%dH  ", C->y, C->x);
	printf("\033[%d;%dH%s", C->y, C->x, C->image[C->direction%2]);
}

void EraseCar(car *C, map M){
	AffMapElement(M, C->y, C->x-1);
	AffMapElement(M, C->y, C->x);
}

int main(int argc, char **argv) {
	map M ;
	LoadMap(&M, "data/map_rendu","data/map_color","data/pieton_carac","data/voiture_carac","data/train_carac","data/map_carac");
	printf("Mx = %d\nMy = %d\n", M.x, M.y);
	printf("\033[2J\033[1;1H");
	AffMap(M);
	car *C = NewCar("data/car", 40, 0, SOUTH);
	// PrintCar(C);
	// Pause();
	// EraseCar(C, M);
	printf("\033[31;1H%s", COLOR.RES);
	return 0;
}
