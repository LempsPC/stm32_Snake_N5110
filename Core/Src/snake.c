/*
 * snake.c
 *
 *  Created on: Sep 25, 2023
 *      Author: Lembitu
 */


#include "snake.h"
#include "stdint.h"
#include "stdlib.h"
#include "nokia5110_LCD.h"

//structs that hold major data about game
struct SnakeGameAttr CurrentGame;
struct SnakeStruct ThisSnake;
struct Food meaty;

void printEndScreen()
{
	//clear screen
	LCD_clrScr();
	char scoreString[5];
	itoa(CurrentGame.score, scoreString, 10);
	LCD_print("Game over!", 10, 2);
	LCD_print("Score", 15, 3);
	LCD_print(scoreString, 50, 3);
}

void printCurrentGameScreen()
{
	//clear screen
	LCD_clrScr();

	//draw food
	LCD_setPixel(meaty.x_pos, meaty.y_pos+1, 1);
	LCD_setPixel(meaty.x_pos+1, meaty.y_pos, 1);
	LCD_setPixel(meaty.x_pos, meaty.y_pos-1, 1);
	LCD_setPixel(meaty.x_pos-1, meaty.y_pos, 1);

	//draw snake:
	for(uint16_t l = ThisSnake.length; l > 0 ; l--)
	{
		//draw snake part
		for(uint8_t i = 0; i < 3; i++)
		{
			for(uint8_t j = 0; j < 3; j++)
			{
				LCD_setPixel(
							ThisSnake.segments[l-1][0] +(i-1),
							ThisSnake.segments[l-1][1] + (j-1), 1);
			}
		}
	}
	//Send data to screen
	LCD_refreshScr();
}

void initGame()
{
	//init game
	CurrentGame.gameOver = 0;
	CurrentGame.score = 0;

	//init snake
	ThisSnake.length = 2;
	ThisSnake.segments[0][0] = 84/2;
	ThisSnake.segments[0][1] = 48/2;
	ThisSnake.segments[1][0] = ThisSnake.segments[0][0] - 3;
	ThisSnake.segments[1][1] = ThisSnake.segments[0][1];
	ThisSnake.currentDirection = right;

	//init fruit
	meaty.x_pos = (rand()%27) * 3;
	meaty.y_pos = (rand()%15) * 3;
}


uint8_t selfCollisionCheck()
{
	uint8_t collision = 0;

	for(uint16_t l = ThisSnake.length; l > 1 ; l--)
	{
		if( (ThisSnake.segments[l-1][0] == ThisSnake.segments[0][0]) &&
				(ThisSnake.segments[l-1][1] == ThisSnake.segments[0][1]) )
		{
			return 1;
		}
	}

	return collision;
}

void updateSnake()
{
	//Update snake body
	for(uint16_t l = ThisSnake.length; l > 1 ; l--)
	{
		if(!( (ThisSnake.segments[l-1][0] == ThisSnake.segments[l-2][0]) &&
				(ThisSnake.segments[l-1][1] == ThisSnake.segments[l-2][1])))
		{
			ThisSnake.segments[l-1][0] = ThisSnake.segments[l-2][0];
			ThisSnake.segments[l-1][1] = ThisSnake.segments[l-2][1];
		}
	}

	if(ThisSnake.currentDirection == right)
	{
		if(ThisSnake.segments[0][0] >= 83)
		{
			ThisSnake.segments[0][0] = 0;
		}
		else
		{
			ThisSnake.segments[0][0] = ThisSnake.segments[0][0] + 3;
		}
	}
	else if(ThisSnake.currentDirection == down)
	{
		if(ThisSnake.segments[0][1] >= 48)
		{
			ThisSnake.segments[0][1] = 0;
		}
		else
		{
			ThisSnake.segments[0][1] = ThisSnake.segments[0][1] + 3;
		}
	}
	else if(ThisSnake.currentDirection == left)
	{
		if(ThisSnake.segments[0][0] == 0)
		{
			ThisSnake.segments[0][0] = 84;
		}
		else
		{
			ThisSnake.segments[0][0] = ThisSnake.segments[0][0] - 3;
		}
	}
	else
	{
		if(ThisSnake.segments[0][1] == 0)
		{
			ThisSnake.segments[0][1] = 48;
		}
		else
		{
			ThisSnake.segments[0][1] = ThisSnake.segments[0][1] - 3;
		}
	}
}

void updateGame(uint8_t inputDirection)
{
	//autopilot
	//inputDirection = rand() % 4;

	//update direction
	if(inputDirection != 5)
	{
		if( ((inputDirection == up) && (ThisSnake.currentDirection != down)) ||
				((inputDirection == down) && (ThisSnake.currentDirection != up)) ||
				((inputDirection == left) && (ThisSnake.currentDirection != right)) ||
				((inputDirection == right) && (ThisSnake.currentDirection != left)) )
		{
			ThisSnake.currentDirection = inputDirection;
		}
	}

	updateSnake();
	if(CurrentGame.gameOver)
	{
		printEndScreen();
	}
	else
	{
		printCurrentGameScreen();
	}

	//primitive collision detection with food
	if((ThisSnake.segments[0][0] == meaty.x_pos) && (ThisSnake.segments[0][1] == meaty.y_pos))
	{
		CurrentGame.score++;
		ThisSnake.segments[ThisSnake.length][0] = ThisSnake.segments[ThisSnake.length-1][0];
		ThisSnake.segments[ThisSnake.length][1] = ThisSnake.segments[ThisSnake.length-1][1];
		ThisSnake.length++;

		meaty.x_pos = (rand()%27) * 3;
		meaty.y_pos = (rand()%15) * 3;
	}
	if(selfCollisionCheck())
	{
		CurrentGame.gameOver = 1;
	}
}
