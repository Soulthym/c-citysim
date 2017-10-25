#include "main.h"

const struct color COLOR = {
    .FBLA =	"\x1b[30m",	.FRED =	"\x1b[31m",	.FGRE =	"\x1b[32m",	.FYEL =	"\x1b[33m",	.FBLU =	"\x1b[34m",	.FMAG =	"\x1b[35m",	.FCYA =	"\x1b[36m",	.FWHI =	"\x1b[37m",	.BBLA =	"\x1b[40m",	.BRED =	"\x1b[41m",	.BGRE =	"\x1b[42m",	.BYEL =	"\x1b[43m",	.BBLU =	"\x1b[44m",	.BMAG =	"\x1b[45m",	.BCYA =	"\x1b[46m",	.BWHI =	"\x1b[47m",	.RES = 	"\x1b[0m",	.BOL = 	"\x1b[1m",	.BLI = 	"\x1b[5m",	.REV = 	"\x1b[7m",	.CON = 	"\x1b[8m"};

void AffMap(map M) {
	for (int y = 0; y < M.y; y ++) {
		for (int x = 0; x < M.x; x++) {
			printf("%s%s", M.map[y][x].color, M.map[y][x].disp);
		}
		printf("\n");
	}
}

map *LoadMap(map *M, char *fichier, char *fichiercouleur){
	FILE *F = fopen(fichier, "r");
	FILE *FC = fopen(fichiercouleur, "r");
	if (F == NULL) {
		printf(">>%s not found\n", fichier);
	} else if (FC == NULL){
		fclose(F);
		printf(">>%s not found\n", fichiercouleur);
	} else {
		fscanf(F,"%d %d\n", &M->x, &M->y);
		M->map = malloc(sizeof(mape*) * M->y);
		for (int y = 0; y < M->y; y++) {
			M->map[y] = malloc(sizeof(mape) * M->x);
		}
		printf(">>loading %s\n", fichier);
		char c,cc;
		for (int y = 0; y < M->y; y++) {
			for (int x = 0; x < M->x; x++) {
				M->map[y][x].disp = malloc(sizeof(char) * 4);
				c = fgetc(F);
				cc = fgetc(FC);
				M->map[y][x].disp[0] = c;
				if (!(c & 128)) {
					M->map[y][x].disp[1] = '\0';
				} else {
					M->map[y][x].disp[1] = fgetc(F);
					M->map[y][x].disp[2] = fgetc(F);
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
			fgetc(FC);
			fgetc(F);
		}
		fclose(F);
		fclose(FC);
	}
	return M;
}

car* NewCar(char* fichier, int posx, int posy, char direction) {
	FILE *F = fopen(fichier,"r");
	if (F == NULL) {
		printf(">>%s not found\n", fichier);
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
	printf("\033[%d;%dH%s%s%s%s", C->y, C->x, M.map[C->y][C->x].color, M.map[C->y][C->x].disp, M.map[C->y+1][C->x].color, M.map[C->y+1][C->x].disp);//C.image[C.direction%2]);
}

int main(int argc, char **argv) {
	map M ;
	LoadMap(&M, "data/map_rendu","data/map_color");
	printf("Mx = %d\nMy = %d\n", M.x, M.y);
	printf("\033[2J\033[1;1H");
	AffMap(M);
	car *C = NewCar("data/car", 40, 0, SOUTH);
	PrintCar(C);
	sleep(1);
	EraseCar(C,M);
	printf("%s\033[31;1H", COLOR.RES);
	return 0;
}