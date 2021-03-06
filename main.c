#include "main.h"
const struct color COLOR = {
  .FBLA =	"\x1b[30m",	.FRED =	"\x1b[31m",	.FGRE =	"\x1b[32m",	.FYEL =	"\x1b[33m",	.FBLU =	"\x1b[34m",	.FMAG =	"\x1b[35m",	.FCYA =	"\x1b[36m",	.FWHI =	"\x1b[37m",	.BBLA =	"\x1b[40m",	.BRED =	"\x1b[41m",	.BGRE =	"\x1b[42m",	.BYEL =	"\x1b[43m",	.BBLU =	"\x1b[44m",	.BMAG =	"\x1b[45m",	.BCYA =	"\x1b[46m",	.BWHI =	"\x1b[47m",	.RES = 	"\x1b[0m",	.BOL = 	"\x1b[1m",	.BLI = 	"\x1b[5m",	.REV = 	"\x1b[7m",	.CON = 	"\x1b[8m"
};
const struct sprite SPRITE = {
  .car = "🚘", .walker = "🚶", .riviere = {"\x1b[44m\x1b[36m~","\x1b[44m "} ,
  .train =
 {{"\x1b[33m│\x1b[36m┌─┐",
           "\x1b[36m┌┼─┼┐",
           "\x1b[36m││ ││",
           "\x1b[36m├│N│┤",
           "\x1b[36m││O││",
           "\x1b[36m├│R│┤",
           "\x1b[36m││D││",
           "\x1b[36m├│ │┤",
           "\x1b[36m││ ││",
           "\x1b[36m└┼─┼┘",
   "\x1b[33m│\x1b[36m└─┘"},
  {"\x1b[33m│\x1b[31m┌─┐",
           "\x1b[31m┌┼─┼┐",
           "\x1b[31m││ ││",
           "\x1b[31m├│ │┤",
           "\x1b[31m││S││",
           "\x1b[31m├│U│┤",
           "\x1b[31m││D││",
           "\x1b[31m├│ │┤",
           "\x1b[31m││ ││",
           "\x1b[31m└┼─┼┘",
   "\x1b[33m│\x1b[31m└─┘"}}
};

char key_pressed(){
  struct termios oldterm, newterm;
  int oldfd; char c, result = 0;
  tcgetattr (STDIN_FILENO, &oldterm);
  newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
  tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
  oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
  c = getchar();
  tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
  fcntl (STDIN_FILENO, F_SETFL, oldfd);
  if (c != EOF) {
    ungetc(c, stdin); result = getchar();
  }
  return result;
}
int  hextoi(char c) {
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
	   printf("%s%s", M->map[y][x].color,M->map[y][x].disp);
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
map  *LoadMap(map *M, char *fmap, char *fcolor, char *fppiet, char *fpvoit, char *fptrain, char *fpmap){
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
        M->map[y][x].canfree = 1;

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
      if (M->map[y][x].canfree) {
        free(M->map[y][x].disp);
      }
    }
    free(M->map[y]);
  }
  free(M->map);
}
int isOccupied(map* M, int x, int y) {
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
    return M->map[y][x].occupied;
  }
    return 0;
}
void CleanMap(map *M){
  for (size_t i = 10; i < 15; i++) {
    AffMapElement(M,13,i);
    AffMapElement(M,12,i);
  }
  for (size_t i = 21; i < 25; i++) {
    AffMapElement(M,13,i);
    AffMapElement(M,12,i);
  }
  for (size_t i = 53; i < 58; i++) {
    AffMapElement(M,13,i);
    AffMapElement(M,12,i);
  }
  for (size_t i = 24; i < 29; i++) {
    AffMapElement(M,20,i);
    AffMapElement(M,19,i);
  }
  for (size_t i = 75; i < 79; i++) {
    AffMapElement(M,20,i);
    AffMapElement(M,19,i);
  }
  for (size_t i = 93; i < 109; i++) {
    AffMapElement(M,25,i);
    AffMapElement(M,27,i);
    AffMapElement(M,29,i);
  }
  for (size_t i = 100; i < 109; i++) {
    AffMapElement(M,24,i);
    AffMapElement(M,26,i);
    AffMapElement(M,28,i);
  }
  for (size_t i = 0; i < M->y; i++) {
    AffMapElement(M,i,49);
  }

  for (size_t y = 21; y < 30; y++) {
    for (size_t x = 37; x < 43; x++) {
      AffMapElement(M,y,x);
    }
  }
  for (size_t y = 21; y < 31; y++) {
    for (size_t x = 50; x < 72; x++) {
      AffMapElement(M,y,x);
    }
  }
  for (size_t x = 50; x < 76; x++) {
    AffMapElement(M,18,x);
  }
  for (size_t x = 50; x < 54; x++) {
    AffMapElement(M,14,x);
  }
  AffMapElement(M,16,50);
}
void InitRiver(map *M) {
  for (size_t y = 21; y < 30; y++) {
    for (size_t x = 32; x < 37; x++) {
      free(M->map[y][x].disp);
      M->map[y][x].canfree = 0;
    }
    for (size_t x = 50; x < 72; x++) {
      free(M->map[y][x].disp);
      M->map[y][x].canfree = 0;
    }
  }
}
void River(int tim, map *M) {
  int t = tim / 10 % 2;
  // printf("\033[37;1H%s%d", COLOR.FRED,t);
  if(!(tim%10)){
    for (size_t y = 21; y < 30; y++) {
      for (size_t x = 32; x < 37; x++) {
        M->map[y][x].disp = SPRITE.riviere[t];
        t ^= 1;
      }
      for (size_t x = 50; x < 72; x++) {
        M->map[y][x].disp = SPRITE.riviere[t];
        t ^= 1;
      }
    }
    for (size_t y = 21; y < 30; y++) {
      for (size_t x = 32; x < 37; x++) {
        AffMapElement(M,y,x);
      }
      for (size_t x = 50; x < 72; x++) {
        AffMapElement(M,y,x);
      }
    }
  }
}

car* NewCar(int posx, int posy, char direction, char* color) {
	car *C = malloc(sizeof(car));
	C->x = posx;
	C->y = posy;
	C->direction = direction;
	C->disp = SPRITE.car; //["🚘","🚗"]
  C->color = color;
  C->canPark = 1;
	return C;
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
    printf("\033[%d;%dH%s %s", y+1, x+1, COLOR.BWHI, COLOR.RES);
  }
}
void RemoveCars(car **C,map *M) {
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    RemoveCar(&C[i],M);
  }
}
void PrintCar(car *C, map *M) {
  if (C){
    if (C->y < M->y && C->y >= 0 && C->x < M->x && C->x >= 0)  {
      if (!(hasprop(M->map[C->y][C->x].mapProp,HIDDEN))) {
        printf("\033[%d;%dH  \033[%d;%dH%s%s",C->y+1, C->x+1, C->y+1, C->x+1,C->color, C->disp);
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
void EraseCar(car *C, map* M) {
  if (!(hasprop(M->map[C->y][C->x].mapProp,HIDDEN))) {
    AffMapElement(M,C->y,C->x);
    // AffMapElement(M,C->y,C->x+1);
  }
}
void EraseCars(car **C, map* M) {
  for (size_t i = 0; i < NUMBEROFCARS; i++) {
    if (C[i]) {
      EraseCar(C[i],M);
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
car *AddCar(car **C, int x, int y, char dir, map *M, char* color) {
  char *Colors[8] = {COLOR.FBLA,COLOR.FRED,COLOR.FGRE,COLOR.FYEL,COLOR.FBLU,COLOR.FMAG,COLOR.FCYA,COLOR.FWHI};
  for(size_t i = 0; i < NUMBEROFCARS; i++) {
    if (!(C[i])) {
      if(!(isOccupied(M,x,y))) {
        if (color == NULL){
          C[i] = NewCar(x,y,dir,Colors[rand()%8]);
        } else {
          C[i] = NewCar(x,y,dir,color);
        }
        OccupyCar(M,x,y,1);
        return C[i];
      }
    }
  }
  return NULL;
  // printf("\033[%d;%dH%s %s", y+1, x+1, COLOR.BRED, COLOR.RES);
}
void AddCars(car **C, map *M, int timer,int speed) {
  if (!(rand()%(RATEOFSPAWNCARS/speed))) {
    AddCar(C,55,0,SOUTH,M,NULL);
  }
  // printf("\033[1;56H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNCARS/speed))) {
    AddCar(C,26,29,NORTH,M,NULL);
  }
  // printf("\033[30;27H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNCARS/speed))) {
    AddCar(C,108,15,WEST,M,NULL);
  }
  // printf("\033[16;109H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNCARS/speed))) {
    AddCar(C,0,17,EAST,M,NULL);
  }
  // printf("\033[18;1H%s %s",COLOR.BGRE, COLOR.RES);
}
void MoveCar(car *C, map *M, char dir) {
  if (C){
    switch (dir) {
      case NORTH:
        OccupyCar(M,C->x,C->y,0);
          if (!(isOccupied(M,C->x,C->y-1))) {
          C->y--;
        }
        OccupyCar(M,C->x,C->y,1);
        break;
      case SOUTH:
        OccupyCar(M,C->x,C->y,0);
        if (!(isOccupied(M,C->x,C->y+1))) {
          C->y++;
        }
        OccupyCar(M,C->x,C->y,1);
        break;
      case EAST:
        OccupyCar(M,C->x,C->y,0);
        if (!(isOccupied(M,C->x+2,C->y))) {
          C->x++;
        }
        OccupyCar(M,C->x,C->y,1);
        break;
      case WEST:
        OccupyCar(M,C->x,C->y,0);
        if (!(isOccupied(M,C->x-1,C->y))) {
          C->x--;
        }
        OccupyCar(M,C->x,C->y,1);
        break;
    }
  }
}
void UpdateCar(car *C, map *M) {
  if (C) {
    if (C->y < M->y && C->y >= 0 && C->x < M->x && C->x >= 0) {
      if (M->map[C->y][C->x].carProp != 0){
        int dir[4] = {NORTH,EAST,SOUTH,WEST};
        int r;
        while (1) {
          r = rand()%4;
          if (hasprop(dir[r], M->map[C->y][C->x].carProp)) {
            break;
          }
        }
        C->direction = dir[r];
        MoveCar(C,M,C->direction);
      }
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

walker* NewWalker(int posx, int posy, char direction, char* color) {
	walker *W = malloc(sizeof(walker));
	W->x = posx;
	W->y = posy;
	W->direction = direction;
	W->disp = SPRITE.walker; //["🚘","🚗"]
  W->color = color;
	return W;
}
void RemoveWalker(walker **W, map *M) {
  if (*W) {
    free(*W);
    *W = NULL;
  }
}
int  WalkerIsAt(walker* W, int x, int y) {
  if (W) {
    if (W->x == x && W->y == y){
      // printf("\033[37;1H%sFound Walker!", COLOR.RES);
      return 1;
    }
  }
  return 0;
}
void OccupyWalker(map *M, int x, int y, int occupy){
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
    M->map[y][x].occupied = occupy;
    // if (x+1 < M->x){
    //   M->map[y][x+1].occupied = occupy;
    // }
  }
}
void RemoveWalkersAt(walker **W, int x, int y,map *M) {
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    if (WalkerIsAt(W[i],x,y)) {
      OccupyWalker(M,x,y,0);
      RemoveWalker(&W[i],M);
    }
  }
  // printf("\033[%d;%dH%s %s", y+1, x+1, COLOR.BRED, COLOR.RES);
}
void RemoveWalkers(walker **W,map *M) {
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    RemoveWalker(&W[i],M);
  }
}
void PrintWalker(walker *W, map *M) {
  if (W){
    if (W->y < M->y && W->y >= 0 && W->x < M->x && W->x >= 0)  {
      if (!(hasprop(M->map[W->y][W->x].mapProp,HIDDEN))) {
        printf("\033[%d;%dH \033[%d;%dH%s%s",W->y+1, W->x+1, W->y+1, W->x+1,W->color, W->disp);
      }
    }
  }
}
void PrintWalkers(walker **W, map *M){
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    if (W[i] != NULL) {
      PrintWalker(W[i],M);
    }
  }
}
void PrintWalkerTab(walker **W) {
  printf("\033[33;1H%s[", COLOR.RES);
  for (int i = 0; i < NUMBEROFWALKERS; i++) {
    if(W[i]) {
      printf("%d,",W[i]->direction);
    } else {
      printf("%d,",0);
    }
  }
  printf("\033[1D]\n");
}
void EraseWalker(walker *W, map* M) {
  if (!(hasprop(M->map[W->y][W->x].mapProp,HIDDEN))) {
    AffMapElement(M,W->y,W->x);
  }
}
void EraseWalkers(walker **W, map* M) {
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    if (W[i]) {
      EraseWalker(W[i],M);
    }
  }
}
void AddWalker(walker **W, int x, int y, char dir, map *M) {
  char *Colors[8] = {COLOR.FBLA,COLOR.FRED,COLOR.FGRE,COLOR.FYEL,COLOR.FBLU,COLOR.FMAG,COLOR.FCYA,COLOR.FWHI};
  for(size_t i = 0; i < NUMBEROFWALKERS; i++) {
    if (!(W[i])) {
      if(!(isOccupied(M,x,y))) {
        W[i] = NewWalker(x,y,dir,Colors[rand()%8]);
        OccupyWalker(M,x,y,1);
        // printf("\033[36;1H%s>>New walker added @ %p", COLOR.RES,W[i]);
        return;
      }
    }
  }
}
void AddWalkers(walker **W, map *M, int timer, int speed) {
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,8,0,SOUTH,M);
  }//printf("\033[1;9H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,16,0,SOUTH,M);
  }//printf("\033[1;17H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,26,0,SOUTH,M);
  }//printf("\033[1;27H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,51,0,SOUTH,M);
  }//printf("\033[1;52H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,59,0,SOUTH,M);
  }//printf("\033[1;60H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,66,0,SOUTH,M);
  }//printf("\033[1;67H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,85,0,SOUTH,M);
  }//printf("\033[1;86H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,106,0,SOUTH,M);
  }//printf("\033[1;107H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,108,13,SOUTH,M);
  }//printf("\033[14;109H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,0,19,SOUTH,M);
  }//printf("\033[20;1H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,0,26,SOUTH,M);
  }//printf("\033[27;1H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,21,29,SOUTH,M);
  }//printf("\033[30;22H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,29,29,SOUTH,M);
  }//printf("\033[30;30H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,108,20,SOUTH,M);
  }//printf("\033[21;109H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,93,29,SOUTH,M);
  }//printf("\033[30;94H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,72,29,SOUTH,M);
  }//printf("\033[30;73H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,80,29,SOUTH,M);
  }//printf("\033[30;81H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,3,26,SOUTH,M);
  }//printf("\033[27;4H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,10,26,SOUTH,M);
  }//printf("\033[27;11H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,17,26,SOUTH,M);
  }//printf("\033[27;18H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,7,4,SOUTH,M);
  }//printf("\033[5;8H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,33,12,SOUTH,M);
  }//printf("\033[13;34H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,93,24,SOUTH,M);
  }//printf("\033[25;94H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,93,26,SOUTH,M);
  }//printf("\033[27;94H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,93,28,SOUTH,M);
  }//printf("\033[29;94H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,99,24,SOUTH,M);
  }//printf("\033[25;100H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,99,26,SOUTH,M);
  }//printf("\033[27;100H%s %s",COLOR.BGRE, COLOR.RES);
  if (!(rand()%(RATEOFSPAWNWALKERS/speed))) {
    AddWalker(W,99,28,SOUTH,M);
  }//printf("\033[29;100H%s %s",COLOR.BGRE, COLOR.RES);
}
void MoveWalker(walker *W, map *M, char dir) {
  if (W){
    switch (dir) {
      case NORTH:
        OccupyWalker(M,W->x,W->y,0);
          if (!(isOccupied(M,W->x,W->y-1))) {
          W->y--;
        }
        OccupyWalker(M,W->x,W->y,1);
        break;
      case SOUTH:
        OccupyWalker(M,W->x,W->y,0);
        if (!(isOccupied(M,W->x,W->y+1))) {
          W->y++;
        }
        OccupyWalker(M,W->x,W->y,1);
        break;
      case EAST:
        OccupyWalker(M,W->x,W->y,0);
        if (!(isOccupied(M,W->x+2,W->y))) {
          W->x++;
        }
        OccupyWalker(M,W->x,W->y,1);
        break;
      case WEST:
        OccupyWalker(M,W->x,W->y,0);
        if (!(isOccupied(M,W->x-1,W->y))) {
          W->x--;
        }
        OccupyWalker(M,W->x,W->y,1);
        break;
    }
  }
}
void UpdateWalker(walker *W, map *M) {
  if (W) {
    if (W->y < M->y && W->y >= 0 && W->x < M->x && W->x >= 0) {
      if (M->map[W->y][W->x].walkerProp != 0){
        int dir[4] = {NORTH,EAST,SOUTH,WEST};
        int r;
        while (1) {
          r = rand()%4;
          if (hasprop(dir[r], M->map[W->y][W->x].walkerProp)) {
            break;
          }
        }
        // printf("\033[35;1H%s%d", COLOR.RES,dir[r]);
        W->direction = dir[r];
        MoveWalker(W,M,W->direction);
      }
    }
  }
}
void UpdateWalkers(walker **W, map *M) {
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    UpdateWalker(W[i],M);
  }
}
void RemoveWalkersOutside(walker **W, map *M){
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    if (W[i]) {
      if (W[i]->y >= M->y || W[i]->y < 0 || W[i]->x >= M->x || W[i]->x < 0) {
        RemoveWalker(&W[i],M);
      }
    }
  }
  RemoveWalkersAt(W,6,5,M);
  RemoveWalkersAt(W,31,11,M);
  RemoveWalkersAt(W,2,25,M);
  RemoveWalkersAt(W,9,25,M);
  RemoveWalkersAt(W,16,25,M);
  RemoveWalkersAt(W,92,24,M);
  RemoveWalkersAt(W,92,26,M);
  RemoveWalkersAt(W,92,28,M);
  RemoveWalkersAt(W,100,24,M);
  RemoveWalkersAt(W,100,26,M);
  RemoveWalkersAt(W,100,28,M);
}

void PrintPark(parking P,map *M) {
  if (P.occupied) {
    printf("\033[%d;%dH  \033[2D%s🚗", P.spawnWalkery+1, P.spawnWalkerx-3, P.carColor);
    // printf("\033[%d;%dH  \033[2D%s%d", P.spawnWalkery+1, P.spawnWalkerx-2, P.carColor, P.occupied);
  } else {
    printf("\033[%d;%dH  \033[2D%s‗‗│", P.spawnWalkery+1, P.spawnWalkerx-3, COLOR.RES);
    // printf("\033[%d;%dH  \033[2D%s%d", P.spawnWalkery+1, P.spawnWalkerx-2, COLOR.RES, P.occupied);
  }
}
void SetParking(parking *P, int y) {
  P->occupied = 0;
  P->spawnWalkerx = 26;
  P->spawnWalkery = y;
  P->spawnCarx = 19;
  P->spawnCary = y;
}
void SetParkings(parking *P) {
  for (size_t y = 0; y < 10; y++) {
    SetParking(&P[y],y);
  }
}
void Park(parking *P,car **C, walker **W, map *M) {
  if (*C) {
    if (!(P->occupied) && (*C)->canPark){
      if (CarIsAt(*C, P->spawnCarx, P->spawnCary) && !(rand()%7)) { //
        // printf("\033[1;1H%sPARK", COLOR.FGRE);
        EraseCar(*C,M);
        AddWalker(W,P->spawnWalkerx,P->spawnWalkery,SOUTH,M);
        OccupyCar(M,P->spawnCarx, P->spawnCary,0);
        P->occupied = 1;
        P->carColor = (*C)->color;
        RemoveCar(C, M);
      }
    }
  }
}
void UnPark(parking *P, walker **W, car **C, map *M) {
  if (*W) {
    if (P->occupied){
      if (WalkerIsAt(*W, P->spawnWalkerx-1, P->spawnWalkery ) && !(rand()%13)/*&& !(rand()%15)*/) {
        EraseWalker(*W,M);
        car *c = AddCar(C,P->spawnCarx,P->spawnCary,SOUTH,M,P->carColor);
        if (c) {
          c->canPark = 0;
        }
        OccupyWalker(M,P->spawnWalkerx-1, P->spawnWalkery,0);
        P->occupied = 0;
        RemoveWalker(W, M);
      }
    }
  }
}
void Parks (parking *P,car **C, walker **W, map *M){
  for (size_t j = 0; j < NUMBEROFCARS; j++) {
    for (size_t i = 0; i < 10; i++) {
      Park(&P[i],&C[j],W,M);
    }
  }
  for (size_t j = 0; j < NUMBEROFWALKERS; j++) {
    for (size_t i = 0; i < 10; i++) {
      UnPark(&P[i],&W[j],C,M);
    }
  }
  for (size_t i = 0; i < 10; i++) {
    PrintPark(P[i],M);
  }
}

train *NewTrain(int x, int y, char dir) {
  train *T = malloc(sizeof(train));
  T->x = x;
  T->y = y;
  T->timer = 0;
  T->dir = dir;
  if (T->dir == 0){
    for (size_t i = 0; i < 5; i++) {
      T->spawn[i] = (i+2)*2;
    }
  } else {
    for (size_t i = 0; i < 5; i++) {
      T->spawn[i] = -1;
    }
  }
  return T;
}
void RemoveTrain(train **T) {
  if (*T) {
    free(*T);
    *T = NULL;
  }
}
void RemoveTrains(train **T) {
  for (size_t i = 0; i < 2; i++) {
    RemoveTrain(&T[i]);
  }
}
int  TrainIsAt(train* T, int x, int y) {
  if (T) {
    if (T->x == x && T->y == y){
      // printf("\033[37;1H%sFound Walker!", COLOR.RES);
      return 1;
    }
  }
  return 0;
}
void PrintTrainLine(train *T,int l, map *M){
  if (T){
    if (T->y+l >= 0 && T->y+l < M->y){
      printf("\033[%d;%dH%s",T->y+1+l, T->x+1,SPRITE.train[T->dir][l]);
    }
  }
}
void PrintTrain(train *T, map *M) {
  if (T){
    for (size_t i = 0; i < 11; i++) {
      PrintTrainLine(T,i,M);
    }
    // printf("\033[37;1H%s%d", COLOR.RES, T->y);
  }
}
void PrintTrains(train **T, map *M) {
  for (size_t i = 0; i < 2; i++) {
    PrintTrain(T[i],M);
  }
}
void PrintTrainsTab(train **T) {
  printf("\033[33;1H%s[", COLOR.RES);
  for (int i = 0; i < 2; i++) {
    if(T[i]) {
      printf("%d,",T[i]->timer);
    } else {
      printf("N,");
    }
  }
  printf("\033[1D]    \n");
}
void EraseTrain(train *T,map *M) {
  if (T) {
    for (size_t y = 0; y < 11; y++) {
      for (size_t x = 0; x < 5; x++) {
        if(T->y+y >= 0 && T->y+y < M->y) {
          AffMapElement(M,T->y+y,T->x+x);
        }
      }
    }
  }
}
void EraseTrains(train **T, map *M) {
  for (size_t i = 0; i < 2; i++) {
    EraseTrain(T[i],M);
  }
}
void MoveTrain(train *T){
  if (T) {
    if ((T->y == 2 && T->dir == 0) || (T->y == 0 && T->dir == 1)) {
      T->timer = 15;
      T->y += T->dir*2-1;
    }
    if (T->timer == 0) {
      T->y += T->dir*2-1;
    } else {
      T->timer --;
    }
  }
}
void MoveTrains(train **T){
  for (size_t i = 0; i < 2; i++) {
    MoveTrain(T[i]);
  }
}
void UpdateTrains(train **T, int tim){
  MoveTrains(T);
  if (T[0]){
    if (T[0]->y <= -11){
      RemoveTrain(&T[0]);
    }
  } else if (!(tim % 150)) {
    T[0] = NewTrain(44,30,0);
  }
  if (T[1]){
    if (T[1]->y >=30){
      RemoveTrain(&T[1]);
    }
  } else if (!((tim + 50) %150)) {
    T[1] = NewTrain(38,-11,1);
  }
}
void TrainWalkerSpawn(train **T, walker **W, map *M) {
  for (size_t t = 0; t < 2; t++) {
    for (size_t i = 0; i < 5; i++) {
      if (T[t]){
        if (T[t]->timer > 0) {
          if (T[t]->spawn[i] > 0) {
            if (!(rand()%3)) AddWalker(W,50,T[t]->spawn[i],NORTH,M);
            if (!(rand()%3)) AddWalker(W,51,T[t]->spawn[i],SOUTH,M);
          } else{
            if (!(rand()%3)) AddWalker(W,31,12,NORTH,M);
            if (!(rand()%3)) AddWalker(W,31,13,SOUTH,M);
          }
        }
      }
    }
  }
}

fire *NewFire(int x1,int y1,int x2,int y2,int wx1,int wy1,int wp1,int wx2,int wy2,int wp2,int cx1,int cy1,int cp1,int cx2,int cy2,int cp2,int timer){
  fire* F = malloc(sizeof(fire));
  F->x1 = x1;
  F->y1 = y1;
  F->x2 = x2;
  F->y2 = y2;
  F->wx1 = wx1;
  F->wy1 = wy1;
  F->wx2 = wx2;
  F->wy2 = wy2;
  F->wp1 = wp1;
  F->wp2 = wp2;
  F->cx1 = cx1;
  F->cy1 = cy1;
  F->cx2 = cx2;
  F->cy2 = cy2;
  F->cp1 = cp1;
  F->cp2 = cp2;
  F->timer = timer;
  return F;
}
void UpdateFire(fire *F, map* M){
  if (F){
    F->timer++;
    if (F->timer < 5) {      //RR
      F->color1 = COLOR.FRED;
      F->color2 = COLOR.FRED;
      M->map[F->wy1][F->wx1].walkerProp &= ~F->wp1;
      M->map[F->wy2][F->wx2].walkerProp &= ~F->wp2;
      M->map[F->cy1][F->cx1].carProp &= ~F->cp1;
      M->map[F->cy2][F->cx2].carProp &= ~F->cp2;
    }
    else if (F->timer < 30) {//RV
      F->color1 = COLOR.FRED;
      F->color2 = COLOR.FGRE;
      M->map[F->wy1][F->wx1].walkerProp |= F->wp1;
      M->map[F->wy2][F->wx2].walkerProp |= F->wp2;
      M->map[F->cy1][F->cx1].carProp &= ~F->cp1;
      M->map[F->cy2][F->cx2].carProp &= ~F->cp2;
    }
    else if (F->timer < 40) {//RO
      F->color1 = COLOR.FRED;
      F->color2 = COLOR.FYEL;
      M->map[F->wy1][F->wx1].walkerProp &= ~F->wp1;
      M->map[F->wy2][F->wx2].walkerProp &= ~F->wp2;
      M->map[F->cy1][F->cx1].carProp &= ~F->cp1;
      M->map[F->cy2][F->cx2].carProp &= ~F->cp2;
    }
    else if (F->timer < 45) {//RR
      F->color1 = COLOR.FRED;
      F->color2 = COLOR.FRED;
    }
    else if (F->timer < 70) {//VR
      F->color1 = COLOR.FGRE;
      F->color2 = COLOR.FRED;
      M->map[F->wy1][F->wx1].walkerProp &= ~F->wp1;
      M->map[F->wy2][F->wx2].walkerProp &= ~F->wp2;
      M->map[F->cy1][F->cx1].carProp |= F->cp1;
      M->map[F->cy2][F->cx2].carProp |= F->cp2;
    }
    else if (F->timer < 80) {//OR
      F->color1 = COLOR.FYEL;
      F->color2 = COLOR.FRED;
      M->map[F->wy1][F->wx1].walkerProp &= ~F->wp1;
      M->map[F->wy2][F->wx2].walkerProp &= ~F->wp2;
      M->map[F->cy1][F->cx1].carProp &= ~F->cp1;
      M->map[F->cy2][F->cx2].carProp &= ~F->cp2;
    }
    else {
      F->timer = 0;
    }
  }
}
void UpdateFires(fire **F, map *M) {
  for (size_t i = 0; i < NUMBEROFFIRES; i++) {
    UpdateFire(F[i],M);
  }
}
void PrintFire(fire *F, map *M){
  if (F) {
    printf("\033[%d;%dH%s🚦",F->y1+1,F->x1+1,F->color1);
    printf("\033[%d;%dH%s🚦",F->y2+1,F->x2+1,F->color2);
    // printf("\033[%d;%dH%s%d",F->wy1+1,F->wx1+1,COLOR.FWHI,M->map[F->wy1][F->wx1].walkerProp);
    // printf("\033[%d;%dH%s%d",F->wy2+1,F->wx2+1,COLOR.FWHI,M->map[F->wy2][F->wx2].walkerProp);
    // printf("\033[%d;%dH%s%d",F->cy1+1,F->cx1+1,COLOR.FWHI,M->map[F->cy1][F->cx1].carProp);
    // printf("\033[%d;%dH%s%d",F->cy2+1,F->cx2+1,COLOR.FWHI,M->map[F->cy2][F->cx2].carProp);
  }
}
void PrintFires(fire **F, map *M) {
  for (size_t i = 0; i < NUMBEROFFIRES; i++) {
    PrintFire(F[i],M);
  }
}
void SetFires(fire **F) {
  F[0] = NewFire(15,14, 10,11, 8,12,EAST, 15,13,WEST, 15,15, WEST, 0,0,0,0);
  F[1] = NewFire(74,18, 78,21, 79,20,WEST, 73,19,EAST, 73,17,EAST, 0,0,0, 30);
}

void RemoveFire(fire **F){
  if (*F) {
    free(*F);
    *F = NULL;
  }
}
void RemoveFires(fire **F) {
  for (size_t i = 0; i < NUMBEROFFIRES; i++) {
    RemoveFire(&F[i]);
  }
}
void FlowMode() {
  int tim = 0;
  map M;
  LoadMap(&M,"data/map_rendu","data/map_color","data/pieton_carac","data/voiture_carac","data/train_carac","data/map_carac");
  walker *W[NUMBEROFWALKERS] = {NULL};
  car *C[NUMBEROFCARS] = {NULL};
  train *T[2] = {NULL};
  fire* F[NUMBEROFFIRES] = {NULL};
  SetFires(F);
  parking P[10];
  SetParkings(P);
  InitRiver(&M);
  River(0,&M);
  AffMap(&M);
  while(1) {
    UpdateFires(F,&M);
    River(tim,&M);
    AddWalkers(W,&M,tim,1);
    AddCars(C,&M,tim,1);
    EraseTrains(T,&M);
    EraseWalkers(W,&M);
    EraseCars(C,&M);
    UpdateTrains(T,tim);
    UpdateWalkers(W,&M);
    UpdateCars(C,&M);
    TrainWalkerSpawn(T,W,&M);
    Parks(P,C,W,&M);
    RemoveWalkersOutside(W,&M);
    RemoveCarsOutside(C,&M);
    CleanMap(&M);
    PrintTrains(T,&M);
    PrintWalkers(W,&M);
    PrintCars(C,&M);
    PrintFires(F,&M);
    printf("\033[37;1H%s", COLOR.RES);
    fflush(stdout);
    // usleep(300000);
    usleep(60000);
    // getchar();
    tim ++;
    if (key_pressed() == 'q')
      break;
  }
  RemoveWalkers(W,&M);
  RemoveCars(C,&M);
  RemoveTrains(T);
  printf("\033[37;1H%s", COLOR.RES);
  freemap(&M);
  RemoveFires(F);
}
void DangerMode() {
  int tim = 0;
  map M;
  LoadMap(&M,"data/map_rendu","data/map_color","data/pieton_carac","data/voiture_carac","data/train_carac","data/map_carac");
  walker *W[NUMBEROFWALKERS] = {NULL};
  car *C[NUMBEROFCARS] = {NULL};
  train *T[2] = {NULL};
  parking P[10];
  SetParkings(P);
  InitRiver(&M);
  River(0,&M);
  AffMap(&M);
  while(1) {
    River(tim,&M);
    AddWalkers(W,&M,tim,3);
    AddCars(C,&M,tim,3);
    EraseTrains(T,&M);
    EraseWalkers(W,&M);
    EraseCars(C,&M);
    UpdateTrains(T,tim);
    UpdateWalkers(W,&M);
    UpdateCars(C,&M);
    TrainWalkerSpawn(T,W,&M);
    Parks(P,C,W,&M);
    RemoveWalkersOutside(W,&M);
    RemoveCarsOutside(C,&M);
    CleanMap(&M);
    PrintTrains(T,&M);
    PrintWalkers(W,&M);
    PrintCars(C,&M);
    printf("\033[37;1H%s", COLOR.RES);
    fflush(stdout);
    usleep(150000);
    tim ++;
    if (key_pressed() == 'q')
      break;
  }
  RemoveWalkers(W,&M);
  RemoveCars(C,&M);
  RemoveTrains(T);
  printf("\033[37;1H%s", COLOR.RES);
  freemap(&M);
  // printf("\033[2J\033[1;1H%s", COLOR.RES);
  // while(1) {
  //   char *Colors[8] = {COLOR.FBLA,COLOR.FRED,COLOR.FGRE,COLOR.FYEL,COLOR.FBLU,COLOR.FMAG,COLOR.FCYA,COLOR.FWHI};
  //   printf("\033[%d;%dH%sWorkInProgress...",(rand()%35)+1,rand()%106+1, Colors[rand()%8]);
  //   fflush(stdout);
  //   usleep(10000);
  //   if (key_pressed() == 'q') break;
  // }
}

void PrintArrow(int x, int y, char* color){
  printf("\033[%d;%dH%s    __",y+1,x+1,color);
  printf("\033[%d;%dH%s ___\\ \\",y+2,x+1,color);
  printf("\033[%d;%dH%s(___)> >",y+3,x+1,color);
  printf("\033[%d;%dH%s    /_/",y+4,x+1,color);
  printf("\033[33;1H%s",COLOR.RES);
}
char Menu (char *FileName) {
  char *Colors[8] = {COLOR.FBLA,COLOR.FRED,COLOR.FGRE,COLOR.FYEL,COLOR.FBLU,COLOR.FMAG,COLOR.FCYA,COLOR.FWHI};
  char c;
  int x = 20, y = 20, choice = 'n';
  char *colo = COLOR.FGRE;
  while (1) {
    printf("\033[2J\033[1;1H");
    FILE *FMENU=fopen(FileName, "r");
    if (FMENU == NULL) {
      printf("%s not found\n",FileName);
      return 0;
    }
    else {
      c=fgetc(FMENU);
      printf("%s",Colors[rand()%4]);
      while(c!=EOF) {
        if (c == '\n') printf("%s",Colors[rand()%4]);
        printf("%c",c);
        c=fgetc(FMENU);
      }
      fclose(FMENU);
    }
    PrintArrow(x,y,colo);
    for (size_t i = 0; i <15; i++) {
      fflush(stdout);
      usleep(50000);
      c = key_pressed();
      switch (c) {
          case 'D':
          case 'd':
            return 'd';
            break;
          case 'N':
          case 'n':
            return 'n';
          case '\n':
            return choice;
          case 'q':
            return 'q';
          case 'A':
            choice = 'n';
            x = 20;
            y = 20;
            colo = COLOR.FGRE;
            break;
          case 'B':
            choice = 'd';
            x = 20;
            y = 26;
            colo = COLOR.FRED;
            break;
      }
    }
    printf("\033[2J\033[1;1H%s", COLOR.RES);
  }
}


int main(int argc, char **argv) {
  srand(time(NULL));
  char choice;
  do {
    choice = Menu("data/mn");
    switch (choice) {
      case 'n':
        FlowMode();
        break;
      case 'd':
        DangerMode();
        break;
    }
  } while (choice != 'q');
  printf("\033[2J\033[1;1H%s", COLOR.RES);
  return 0;
}
