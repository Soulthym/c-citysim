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

int main(int argc, char **argv) {
	// ChargerEncodage("data/special_chars_encoding");
	map M ;
	LoadMap(&M, "data/map_rendu","data/map_color");
	printf("Mx = %d\nMy = %d\n", M.x, M.y);

	AffMap(M);
	printf("%s\n", COLOR.RES);
	return 0;
}

//devoirs: Ticy: charger towncode dans un tableau 2D de caracteres et l'afficher (1 fonction LoadMap)