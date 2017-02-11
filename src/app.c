#include"snake.h"
#include "app.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>     //STDIN_FILENO

char  snakeheaddirection =2;
static mysnake* snakehead;
char snake_length = 2;
void binary_conversion(unsigned char num);
void* app_main ( void *ptr ) {

	char row=0;
	char game_status = Game_On;
	//char speed = game_speed;
	char k;
	unsigned char patt[ledmatrix_rows] = {0};
	mysnake snake[max_snake_size]; //create snake matrix
	food apple =
	{
			.row=2,
			.column=2
	};
	food* applepointer;

	applepointer = &apple;

	snakehead=&snake[0];

	Microcontroller_initialization(); //initialization for the used ports at micro

	snake_intialization(snake);

	while (1) {

		if (game_status == Game_Off)

		{
			//will need re initialization
			//if it is game over

			for (row = 0; row < ledmatrix_rows; row++)
			{
				patt[row]=0;
			};
			for (row = 0; row < ledmatrix_rows; row++)
			{
				binary_conversion(patt[row]);
			};
		}

		else if (game_status == Game_On){
			//switch off all leds
			for (k = 0; k < ledmatrix_rows; k++){
				patt[k] = 0;
			}

			update_body_directions(snake);   //update body direction

			update_body(snake,patt); //update snake body location at snake matrix and at pattern

			if ((snake[0].srow == apple.row) && (snake[0].scolumn == apple.column)){

				//should check if make overflow due to wining
				//snake head should be updated
				happy_meal(snake,patt);

				snake_length++;

				//should take care of snake head position
				renew_apple(applepointer, snake,patt);

			}

			update_head(snake,snakeheaddirection); //update head location

			if (body_crash(snake)){ //check for game over
				game_status = Game_Off;
			}

			light_bit(snake[0].srow, snake[0].scolumn, patt); //switch on snake head lead
			light_bit(applepointer->row, applepointer->column, patt); //switch on apple

			printf(" ________\n");
			for (row = 0; row < ledmatrix_rows; row++){
				binary_conversion(patt[row]);
			}
			printf(" ________\n");
			sleep(1);
			system("clear");
		}
	}
}

void binary_conversion(unsigned char num){
	unsigned char bits[8] = {0};
	char loopIndex = 0;
	while (num != 0){
		bits[loopIndex] = num % 2;
		num = num/2;
		loopIndex++;
	}
	printf("|");
	for(loopIndex = 7; loopIndex >= 0; loopIndex--){
		if(bits[loopIndex] == 0){
			printf(" ");
		}
		else{
			printf("*");
		}
	}
	printf("|\n");
}


