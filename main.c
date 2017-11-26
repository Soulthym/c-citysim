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
  printf("\033[37;1H%s", COLOR.RES);
	getchar();
}
void AffMapElement(map *M, int y, int x) {
  printf("\033[%d;%dH", y+1, x+1);
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
	   printf("%s%d", M->map[y][x].color,(int)M->map[y][x].carProp );//M->map[y][x].disp);
   }
   printf("%s ",COLOR.RES);
}
void AffMapLine(map *M, int y) {
  for (int x = 0; x < M->x; x++) {
    AffMapElement(M, y, x);
  }
}
void AffMap(map *M) {
  printf("\033[2J\033[1;1H");
	for (int y = 0; y < M->y; y ++) {
    AffMapLine(M,y);
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
	}
  else if (FC == NULL){
		fclose(FM);
		printf(">>%s not found\n", fcolor);
	}
  else if (FPP == NULL){
		fclose(FM);
		fclose(FC);
		printf(">>%s not found\n", fppiet);
	}
  else if (FPV == NULL){
		fclose(FM);
		fclose(FC);
		fclose(FPP);
		printf(">>%s not found\n", fpvoit);
	}
  else if (FPT == NULL){
		fclose(FM);
		fclose(FC);
		fclose(FPP);
		fclose(FPV);
		printf(">>%s not found\n", fptrain);
	}
  else if (FPM == NULL){
		fclose(FM);
		fclose(FC);
		fclose(FPP);
		fclose(FPV);
		fclose(FPT);
		printf(">>%s not found\n", fpmap);
	}
  else {
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
void freemap(map* M) {
  for (size_t y = 0; y < M->y; y++) {
    for (size_t x = 0; x < M->x; x++) {
      free(M->map[y][x].disp);
    }
    free(M->map[y]);
  }
  free(M->map);
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
void PrintCar(car *C, map *M) {
  if (C){
    if (C->y < M->y && C->y >= 0 && C->x < M->x && C->x >= 0)  {
      if (!(hasprop(M->map[C->y][C->x].mapProp,HIDDEN))) {
        printf("\033[%d;%dH \033[%d;%dH%s%d",C->y+1, C->x+1, C->y+1, C->x+1, COLOR.BRED/*C->color*/, C->direction);
      }
    }
  }
}
void PrintCars(car **C, map *M){
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    if (C[i] != NULL) {
      PrintCar(C[i],M);
    }
  }
}
void EraseElements(car **C, map* M) {
  int linesused[M->y];
  for (size_t i = 0; i < M->y; i++) {
    linesused[i] = 0;
  }
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    if(C[i] != NULL && C[i]->y < M->y) {
      linesused[C[i]->y] = 1;
    }
  }
  for (size_t i = 0; i < M->y; i++) {
    if (linesused[i] == 1){
      AffMapLine(M,i);
    }
  }
}
void OccupyCar(map *M, int x, int y, int occupy){
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
    M->map[y][x].occupied = occupy;
    if (x+1 < M->x){
      M->map[y][x+1].occupied = occupy;
    }
  }
}
int isOccupied(map* M, int x, int y) {
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
    return M->map[y][x].occupied;
  }
    return 0;
}
void AddCar(car **C, int x, int y, char dir, map *M) {
  char *Colors[8] = {COLOR.FBLA,COLOR.FRED,COLOR.FGRE,COLOR.FYEL,COLOR.FBLU,COLOR.FMAG,COLOR.FCYA,COLOR.FWHI};
  for(size_t i = 0; i < NUMBEROFCARS; i++) {
    if (!(C[i])) {
      C[i] = NewCar(x,y,dir,Colors[rand()%8]);
      OccupyCar(M,x,y,1);
      // printf("\033[36;1H%s>>New car added @ %p", COLOR.RES,C[i]);
      return;
    }
  }
}
void PrintCarTab(car **C) {
  printf("\033[33;1H%s[", COLOR.RES);
  for (int i = 0; i < NUMBEROFCARS; i++) {
    if(C[i]) {
      printf("%d,",C[i]->direction);
    } else {
      printf("%d,",0);
    }
  }
  printf("\033[1D]\n");
}
void RemoveCar(car **C, map *M) {
  if (*C) {
    // OccupyCar(M,C->x,C->y,0);
    free(*C);
    *C = NULL;
  }
}
int CarIsAt(car* C, int x, int y) {
  if (C) {
    if (C->x == x && C->y == y){
      return 1;
    }
  }
  return 0;
}
void RemoveCarsAt(car **C, int x, int y,map *M) {
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    if (CarIsAt(C[i],x,y)) {
      RemoveCar(&C[i],M);
    }
  }
}
void RemoveCars(car **C,map *M) {
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    RemoveCar(&C[i],M);
  }
}
void MoveCar(car *C, map *M, char dir) {
  if (C){
    switch (dir) {
      case NORTH:
        if (!(isOccupied(M,C->x,C->y-1))) {
          OccupyCar(M,C->x,C->y,0);
          C->y--;
          OccupyCar(M,C->x,C->y,1);
        }
        break;
      case SOUTH:
        if (!(isOccupied(M,C->x,C->y+1))) {
          OccupyCar(M,C->x,C->y,0);
          C->y++;
          OccupyCar(M,C->x,C->y,1);
        }
        break;
      case EAST:
        if (!(isOccupied(M,C->x+1,C->y))) {
          OccupyCar(M,C->x,C->y,0);
          C->x++;
          OccupyCar(M,C->x,C->y,1);
        }
        break;
      case WEST:
        if (!(isOccupied(M,C->x-1,C->y))) {
          OccupyCar(M,C->x,C->y,0);
          C->x--;
          OccupyCar(M,C->x,C->y,1);
        }
        break;
    }
  }
}
void UpdateCar(car *C, map *M) { // source du probleme...
  if (C) {
    if (hasprop(C->direction,M->map[C->y][C->x].carProp) == C->direction) {
      MoveCar(C,M,C->direction);
      printf("\033[35;1H%sGOING\n", COLOR.RES);
    } else if (M->map[C->y][C->x].carProp != 0){
      int dir[4] = {NORTH,EAST,SOUTH,WEST};
      int r;
      do {
        r = rand()%4;
      } while((hasprop(dir[r], M->map[C->y][C->x].carProp)) != 0);
      printf("\033[35;1H%s%d", COLOR.RES,dir[r]);
      C->direction = dir[r];
      MoveCar(C,M,dir[r]);
    } else {
      RemoveCar(&C,M);
    }
  }
}
void UpdateCars(car **C, map *M) {
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    UpdateCar(C[i],M);
  }
}
void RemoveCarsOutside(car **C, map *M){
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    if (C[i]) {
      if (C[i]->y >= M->y || C[i]->y < 0 || C[i]->x >= M->x || C[i]->x < 0) {
        RemoveCar(&C[i],M);
      }
    }
  }
}
void AddCars(car **C, map *M, int timer) {
  if (!(rand()%10)) {
    AddCar(C,54,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddCar(C,25,29,NORTH,M);
  }
  if (!(rand()%10)) {
    AddCar(C,108,15,WEST,M);
  }
  if (!(rand()%10)) {
    AddCar(C,0,17,EAST,M);
  }
}
int main1(int argc, char **argv) {
  srand(0);
  map M;
  LoadMap(&M,"data/map_rendu","data/map_color","data/pieton_carac","data/voiture_carac","data/train_carac","data/map_carac");
  AffMap(&M);
  car *C[NUMBEROFCARS] = {NULL};
  // AddCar(C,54,0,SOUTH,&M);
  AddCar(C,25,29,NORTH,&M);
  PrintCarTab(C);
  for (size_t i = 0; i < 200; i++) {
    //AddCars(C,&M,i);
    EraseElements(C,&M);
    UpdateCars(C,&M);
    RemoveCarsOutside(C,&M);
    PrintCarTab(C);
    PrintCars(C,&M);
    Pause();
    AffMap(&M);
    PrintCars(C,&M);
    printf("\033[37;1H%s%zu", COLOR.RES,i);
    // fflush(stdout);
    // usleep(100000);
  }
  RemoveCars(C,&M);
  printf("\033[37;1H%s", COLOR.RES);
  freemap(&M);
	return 0;
}

int main(int argc, char const *argv[]) {
  printf("%d\n",hasprop(4,2));
  return 0;
}
