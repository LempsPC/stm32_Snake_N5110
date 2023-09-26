# stm32_Snake_N5110
This is solution for embedded software engineer task. 
In short task is to develop a snake game that could be playes on an embedded device. 
The device in this case is STM32 NUCLEO-F030R8 development board.
Output can be seen on Nokia N5110 screen.
Inputs are read from microswitch-style pushbuttons. 

## Game features
* Game screen and separate endgame screen
* Game playfield is wrapper-type: if you go to border it will pop out from the other side "wrapping" the map
* Snake has collision detection with fruit and itself
* Game ends when snake collides with itself
* For each collected fruit you get 1 point
* Snake speed is currently constant throught the game

## Wiring
When hooking up wiring, check out wiring diagram for this development board:
https://os.mbed.com/platforms/ST-Nucleo-F030R8/

In this case wiring to screen is done as:
RST - GPIO_B3
CE - GPIO_B5
DC - GPIO_B4
DIN - GPIO_B10
CLK - GPIO_A8

Wiring to pushbuttons is done as:
UP - GPIO_A9
DOWN - GPIO_C7
LEFT - GPIO_B6
RIGHT - GPIO_A7

## LCD Driving
LCD driver used in this project is Zeldax64's N5110 driver which works well in this application.
more information in: https://github.com/Zeldax64/Nokia-LCD5110-HAL

