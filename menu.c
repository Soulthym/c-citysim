int main(){
  char mode;
	FILE *menu=NULL;
	int c;
	system ("play -q tetris.mp3 &");
	menu=fopen("mn", "r");
	if (menu == NULL) {
		printf("not found\n");
		return 0;

	}
	else {
		while(c!=EOF){
			c=fgetc(menu);
			printf("%c",c);
		}

	}


    scanf("%s",&mode);
	system("killall play");

    switch(mode){
		case 'n': printf("mode normal\n");break;//mode normale
		case 'N': printf("mode normal\n");break;//mode normale
		case 'd': printf("mode DANZZZ\n");break;//mode normale
		case 'D': printf("mode DANZZZ\n");break;//mode normale
	}


	return 0;

}
