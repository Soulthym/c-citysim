#include "main.h"
const struct color COLOR = {
  .FBLA =	"\x1b[30m",	.FRED =	"\x1b[31m",	.FGRE =	"\x1b[32m",	.FYEL =	"\x1b[33m",	.FBLU =	"\x1b[34m",	.FMAG =	"\x1b[35m",	.FCYA =	"\x1b[36m",	.FWHI =	"\x1b[37m",	.BBLA =	"\x1b[40m",	.BRED =	"\x1b[41m",	.BGRE =	"\x1b[42m",	.BYEL =	"\x1b[43m",	.BBLU =	"\x1b[44m",	.BMAG =	"\x1b[45m",	.BCYA =	"\x1b[46m",	.BWHI =	"\x1b[47m",	.RES = 	"\x1b[0m",	.BOL = 	"\x1b[1m",	.BLI = 	"\x1b[5m",	.REV = 	"\x1b[7m",	.CON = 	"\x1b[8m"
};
const struct sprite SPRITE = {
  .walker = "🚘", .walker = "00"
};
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
	   printf("%s%s", M->map[y][x].color,M->map[y][x].disp );//M->map[y][x].disp);
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
void RemoveWalkersAt(walker **W, int x, int y,map *M) {
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    if (WalkerIsAt(W[i],x,y)) {
      RemoveWalker(&W[i],M);
    }
  }
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
        printf("\033[%d;%dH  \033[%d;%dH%s%s",W->y+1, W->x+1, W->y+1, W->x+1,W->color, W->disp);
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
  AffMapElement(M,W->y,W->x);
  AffMapElement(M,W->y,W->x+1);
}
void EraseWalkers(walker **W, map* M) {
  for (size_t i = 0; i < NUMBEROFWALKERS; i++) {
    if (W[i]) {
      EraseWalker(W[i],M);
    }
  }
}
void OccupyWalker(map *M, int x, int y, int occupy){
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
    M->map[y][x].occupied = occupy;
    if (x+1 < M->x){
      M->map[y][x+1].occupied = occupy;
    }
  }
}
int  isOccupied(map* M, int x, int y) {
  if (y < M->y && y >= 0 && x < M->x && x >= 0) {
    return M->map[y][x].occupied;
  }
    return 0;
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
void AddWalkers(walker **W, map *M, int timer) {
  if (!(rand()%10)) {
    AddWalker(W,8,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,16,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,26,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,51,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,59,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,66,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,85,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,106,0,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,108,13,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,0,19,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,0,26,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,21,29,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,29,29,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,108,20,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,93,29,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,72,29,SOUTH,M);
  }
  if (!(rand()%10)) {
    AddWalker(W,80,29,SOUTH,M);
  }

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
        printf("\033[35;1H%s%d", COLOR.RES,dir[r]);
        W->direction = dir[r];
        MoveWalker(W,M,W->direction);
      } else {
        RemoveWalker(&W,M);
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
  RemoveWalkersAt(W,6,4,M);
  RemoveWalkersAt(W,6,5,M);
  RemoveWalkersAt(W,31,11,M);
  RemoveWalkersAt(W,32,11,M);
  RemoveWalkersAt(W,2,25,M);
  RemoveWalkersAt(W,3,25,M);
  RemoveWalkersAt(W,9,25,M);
  RemoveWalkersAt(W,10,25,M);
  RemoveWalkersAt(W,16,25,M);
  RemoveWalkersAt(W,17,25,M);
  RemoveWalkersAt(W,17,25,M);
  RemoveWalkersAt(W,92,24,M);
  RemoveWalkersAt(W,92,26,M);
  RemoveWalkersAt(W,92,28,M);
  RemoveWalkersAt(W,99,24,M);
  RemoveWalkersAt(W,99,26,M);
  RemoveWalkersAt(W,99,28,M);
}

int main(int argc, char **argv) {
  srand(1);
  map M;
  LoadMap(&M,"data/map_rendu","data/map_color","data/pieton_carac","data/voiture_carac","data/train_carac","data/map_carac");
  AffMap(&M);
  walker *W[NUMBEROFWALKERS] = {NULL};
  PrintWalkerTab(W);
  // AddWalker(W,8,4,SOUTH,&M);
  for (size_t i = 0; i < 500; i++) {
    AddWalkers(W,&M,i);
    EraseWalkers(W,&M);
    UpdateWalkers(W,&M);
    RemoveWalkersOutside(W,&M);
    PrintWalkerTab(W);
    PrintWalkers(W,&M);

    printf("\033[37;1H%s", COLOR.RES);
    fflush(stdout);
    // usleep(150000);
    Pause();
  }
  RemoveWalkers(W,&M);
  printf("\033[37;1H%s", COLOR.RES);
  freemap(&M);
	return 0;
}
