/*
 * snake.h
 *
 *  Created on: Sep 25, 2023
 *      Author: lemps
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include <stdint.h>
#include <stdlib.h>

#define MAX_SNAKE_LENGTH 448

enum direction {
	right = 0,
	down = 1,
	left = 2,
	up = 3,
	none = 5
};

struct SnakeStruct{
	uint8_t length;
	uint8_t segments[MAX_SNAKE_LENGTH][2];
	uint8_t currentDirection;
};
struct SnakeGameAttr{
	uint8_t gameOver;
	uint16_t score;
};

struct Food{
	uint8_t x_pos;
	uint8_t y_pos;
};

void printEndScreen();
void printCurrentGameScreen();

/**
 * Starts the game
 */
void initGame();

/**
 * Updates game state
 */
void updateGame(uint8_t inputDirection);

#endif /* INC_SNAKE_H_ */
