
/*
 ============================================================================
 Name        : threads.c
 Author      : threads
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
*/


#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include "app.h"

void* ReadKeyInput( void *ptr );

int main()
{
	char direction;
	pthread_t thread1, thread2;
	int  iret1, iret2;

	iret1 = pthread_create( &thread1, NULL, ReadKeyInput, & direction);
	if(iret1)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}

	iret2 = pthread_create( &thread2, NULL, app_main, NULL);
	if(iret2)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
		exit(EXIT_FAILURE);
	}

	printf("pthread_create() for thread 1 returns: %d\n",iret1);
	printf("pthread_create() for thread 2 returns: %d\n",iret2);

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	while(1);

	exit(EXIT_SUCCESS);

	return 0;
}

void* ReadKeyInput( void *ptr )
{
	printf("**KeyInput\n");

	char* direction = (char *) ptr;
	char consoleCharacter;
	static struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON| ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);



	while(1){
		while((consoleCharacter=getchar())!= 'e'){
			switch(consoleCharacter){
			case 65:
				snakeheaddirection =up;
				break;
			case 66:
				snakeheaddirection =down;
				break;
			case 67:
				snakeheaddirection =right;
				break;
			case 68:
				snakeheaddirection =left;
				break;
			}
		}
	}
}

