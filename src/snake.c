//#include <avr/io.h>
#include"snake.h"
//#include <avr/interrupt.h>

extern char snakeheaddirection;

extern const char snake_length;

void light_bit(char row, char column, unsigned char* p)
    {
    p[row] |= (1 << column);
    }

void update_body_directions(mysnake* snake)
    {

    char i;

    for(i = snake_length-1 ; i > 0 ; i--)

	{
	snake[i].direction = snake[i-1].direction;
	}

    }

void update_body(mysnake * snake, unsigned char* patt)
    {

    char i;

    for(i = 1 ;snake[i].direction != invalid; i++)
	{

	switch (snake[i].direction)
	    {
	case left:
	    snake[i].scolumn = ((snake[i].scolumn)+1) % ledmatrix_columns;
	    break;
	case right:
	    snake[i].scolumn = (((snake[i].scolumn)-1) < 0 ? ledmatrix_columns-1:((snake[i].scolumn)-1));
	    break;
	case down:
	    snake[i].srow = ((snake[i].srow)+1) % ledmatrix_rows;
	    break;
	case up:
	    snake[i].srow = (((snake[i].srow)-1) < 0 ? ledmatrix_rows-1:((snake[i].srow)-1));
	    break;
	    }
	}

    for(i = 1; snake[i].direction != invalid; i++)
	{
	light_bit(snake[i].srow, snake[i].scolumn, patt);
	}

    }

void update_head(mysnake* snakehead,char snakeheaddirection) {

    snakehead->direction = snakeheaddirection;

    switch (snakehead->direction)
	{

    case left:
	snakehead->scolumn =((snakehead->scolumn)+1)%ledmatrix_columns;
	break;

    case right:
	snakehead->scolumn = (((snakehead->scolumn)-1) <0 ? ledmatrix_columns-1:((snakehead->scolumn)-1));
	break;

    case down:
	snakehead->srow = ((snakehead->srow)+1) % ledmatrix_rows;
	break;

    case up:
	snakehead->srow = (((snakehead->srow)-1) <0 ? ledmatrix_rows-1:((snakehead->srow)-1));
	break;

	}
}

void happy_meal(mysnake* snake,unsigned char* patt)
    {

    switch (snake[snake_length-1].direction)
	{

    case left:

	snake[snake_length].srow = snake[snake_length -1].srow;
	snake[snake_length].scolumn = (snake[snake_length -1].scolumn) - 1;
	break;

    case right:

	snake[snake_length].srow = snake[snake_length -1].srow;
	snake[snake_length].scolumn = (snake[snake_length -1].scolumn) + 1;
	break;

    case down:

	snake[snake_length].srow = (snake[snake_length -1].srow) - 1;
	snake[snake_length].scolumn = snake[snake_length -1].scolumn;
	break;

    case up:

	snake[snake_length].srow = (snake[snake_length -1].srow) + 1;
	snake[snake_length].scolumn = snake[snake_length-1].scolumn;
	break;

	}

    snake[snake_length].direction = snake[snake_length-1].direction;

    light_bit(snake[snake_length].srow, snake[snake_length].scolumn, patt);

    }

char body_crash(mysnake *snake) {

    mysnake *temp;
    temp = snake + 1;

    while (temp->direction != invalid) {
	if ((snake->srow == temp->srow)
		&& (snake->scolumn == temp->scolumn))
	    return 1;
	temp++;
    }
    return 0;
}

void renew_apple(food* applepointer, mysnake * snake,unsigned char* patt) {


    char temparr[ledmatrix_rows] = { 0 };

    signed char i,counter=0;

    for(i=0;i<ledmatrix_rows;i++)
	{
	//may be bug at this condition
	if(patt[i]!=0x1f)
	    {
	    temparr[counter]=i;
	    counter++;
	    }
	}

    applepointer->row=temparr[rand() %counter];

    counter=0;

    for(i=0;i<ledmatrix_rows;i++)
	{
	temparr[i]=0;
	}

    for(i=0;i<ledmatrix_columns;i++)
	{
	if(((1<<i)&patt[applepointer->row])==0)
	    {
	    temparr[counter]=i;
	    counter++;
	    }
	}

    applepointer->column=temparr[rand() %counter];
}

void snake_intialization(mysnake* snake)
    {

    char  k;

    for (k = 2;k< max_snake_size; k++)

	{

	snake[k].srow = 0;
	snake[k].scolumn = 0;
	snake[k].direction = 0;

	}

    snake[0].srow = 4;
    snake[0].scolumn = 2;
    snake[0].direction =right;
    snake[1].srow = 4;
    snake[1].scolumn = 3;
    snake[1].direction =right;

    snakeheaddirection=right;

    }

void Microcontroller_initialization(void)
    {

/*    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0;

    // set up timer with prescaler = 64 and CTC mode
    TCCR1B |= (1 << WGM12)|(1 << CS11);

    // initialize counter
    TCNT1 = 0;

    // initialize compare value
    OCR1A = 1000;

    // enable compare interrupt
    TIMSK |= (1 << OCIE1A);

    // enable global interrupts
    sei();*/

    }
