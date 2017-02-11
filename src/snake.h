/*
 * snake.h
 *
 *  Created on: Jan 28, 2017
 *      Author: Ahmed
 */

#ifndef SNAKE_H_
#define SNAKE_H_

/*----------------definitions------------------*/
#define Game_Off 0
#define Game_On 1
#define ledmatrix_columns 8
#define ledmatrix_rows 7
#define game_speed 100
#define max_snake_size (ledmatrix_columns * ledmatrix_rows)
/*----------------definitions------------------*/

/*----------------structures------------------*/
typedef struct snakebit {
    signed char srow;
    signed char scolumn;
    signed char direction;
} mysnake;

typedef struct food {
    char row;
    char column;
} food;
/*----------------structures------------------*/

/*----------------enums------------------*/
enum snake_directions
    {
    invalid=0,
    right,
    left,
    down,
    up
    };
/*----------------enums------------------*/

/*----------------prototypes------------------*/
void light_bit(char row, char column, unsigned char* p);
void update_body_directions(mysnake * snake);
void update_body(mysnake * snake,unsigned char* patt);
void update_head(mysnake* snakehead,char snakeheaddirection);
void happy_meal(mysnake* snake,unsigned char* patt);
char body_crash(mysnake *snake);
void renew_apple(food* applepointer, mysnake * listhead,unsigned char* patt);
char check_collision(food* applepointer, mysnake* listhead);
void snake_intialization(mysnake* snake);
void Microcontroller_initialization(void);
/*----------------prototypes------------------*/

#endif /* SNAKE_H_ */
