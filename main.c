#include "main.h"

typedef struct {
	char original;
	char special[5];
}encod;

encod *ChargerEncodage(char *fichier) {
	FILE *F = fopen(fichier, "r");
	if (F == NULL) {
		printf(">>%s not found\n",fichier);
		return NULL;
	} else {
		printf(">>loading %s\n",fichier);
		int n;
		encod tmp;
		for (n = 0; n < 256 && fscanf(F,"%c %s\n", &tmp.original, tmp.special) == 2; n++) {}
		printf("il y a %d caracteres\n",n);

		fseek(F, 0, SEEK_SET);
		encod *Encodage = malloc(sizeof(encod) * n);
		int i;
		for (i = 0; i < n && fscanf(F,"%c %s\n", &Encodage[i].original, Encodage[i].special) == 2; i++) {
			if (strcmp(Encodage[i].special,"?") == 0){
				Encodage[i].special[0] = ' ';
				Encodage[i].special[1] = '\0';
			}
			printf("%c <-> %s\n", Encodage[i].original, Encodage[i].special);
		}
		fclose(F);
		return Encodage;
	}
}

map **LoadMap(char *fichier){
	FILE *F = fopen(fichier, "r");
	if (F == NULL) {
		printf(">>%s not found\n", fichier);
		return NULL;
	} else {
		int nbcol, nblin, x = 0, y = 0;
		fscanf(F,"%d %d\n", &nbcol, &nblin);
		map **M = malloc(sizeof(map*) * nblin);
		for (int i = 0; i < nblin; i++) {
			M[i] = malloc(sizeof(map) * nbcol);
		}
		printf(">>loading %s\n", fichier);
		for (char c = fgetc(F); c != EOF; c = fgetc(F), x++){
			if (c == '\n') {
				printf("\n");
				x = 0;
				y ++;
			} else if (c & 128) {
				M[y][x].disp = malloc(sizeof(char) * 4);
				M[y][x].disp[0] = c;
				M[y][x].disp[1] = fgetc(F);
				M[y][x].disp[2] = fgetc(F);
				M[y][x].disp[3] = '\0';
				printf("%s", M[y][x].disp);
			} else {
				M[y][x].disp = malloc(sizeof(char) * 2);
				M[y][x].disp[0] = c;
				M[y][x].disp[1] = '\0';
				printf("%s", M[y][x].disp);
			}
		}
		printf("\n");
		return NULL;
	}
}

int main(int argc, char **argv) {
	// ChargerEncodage("data/special_chars_encoding");
	LoadMap("data/map_rendu");
	return 0;
}

//devoirs: Ticy: charger towncode dans un tableau 2D de caracteres et l'afficher (1 fonction LoadMap)