#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SDL.h"

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
const SDL_Rect BUTTON_SCALE_SIZE = {0,0, SCREEN_WIDTH/3, SCREEN_HEIGHT/3};

//Button constants
const int BUTTON_WIDTH = 266;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 9;

enum LButtonSprite
{
	BUTTON_SPRITE_NOT_SELECTED = 0,
	BUTTON_SPRITE_X_SELECTED = 1,
	BUTTON_SPRITE_0_SELECTED = 2,
};

#endif