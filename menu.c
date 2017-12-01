#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define color(param) printf("\033[%sm", param);


char key_pressed(){
	
	struct termios oldterm, newterm;
	int oldfd; char c, result=0;
	tcgetattr(STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c=getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (	STDIN_FILENO, F_SETFL, oldfd);
	
	if(c!=EOF){
		ungetc(c, stdin);
		result=getchar();
	}

	return result;
}

void modefluide(){

	int c, j=0;
	FILE *menuf=NULL;

	menuf=fopen("mnf", "r");
	if (menuf == NULL) {
		printf("not found\n");
		return 0;
	} 
	else {
		//system("clear");
		while(c!=EOF){
			//c=fgetc(menuf);	
			if (c<700){	
				color("32");
				c=fgetc(menuf);				
				printf("%c",c);
				color("0");
			}
			else {
				color("0");
				c=fgetc(menuf);
				printf("%c",c);
			}
			j=c;
		}
	}
	printf("j=%d",j);
	fclose(menuf);
	c=0;
}

void modedanger(){

	int z, i=0;	
	FILE *menud=NULL;

	menud=fopen("mnd", "r");
	if (menud == NULL) {
		printf("not found\n");
		return 0;
	} 

	else {
		//system("clear");
		color("31");
		while(z!=EOF){
			z=fgetc(menud);						
			printf("%c",z);
			i=i+z;
		}
	}
	printf("i=%d",i);
	fclose(menud);
	z=0;

}

int main(){

	int mode;
	char choix;
	int scrut=1 ;
		
	//system ("play -q tetris.mp3 &");
	modefluide();

 	while(scrut){

		choix=key_pressed();
		printf("\b");
		
		if (choix!=NULL){
			switch(choix){
		
				case '8':
					system("clear");					
					modefluide();
					mode=1;
					break;
		
				case'2':
					system("clear");		
					modedanger();
					mode=2;
					break;

				case '5': 
					scrut=0;
					break;

				default:
					//printf("\033[K");
					printf("\b");
					break;
			}
		}
	}


	switch(mode){
		case 1: printf("mode normal\n");break;//mode normale
		case 2: printf("mode DANZZZ\n");break;//mode normale
	}
	

	return 0;

}
