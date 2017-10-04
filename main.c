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

void LoadMap(char *fichier){

}

int main(int argc, char **argv) {
	ChargerEncodage("data/special_chars_encoding");
	return 0;
}

//devoirs: Ticy: charger towncode dans un tableau 2D de caracteres et l'afficher (1 fonction LoadMap)