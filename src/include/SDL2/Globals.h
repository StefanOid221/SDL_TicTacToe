#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"
#include "LButton.h"

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

extern bool playerXTurn;
extern bool myTurn;

extern LTexture gBackgroundTexture;
extern LTexture gXTexture;
extern LTexture g0Texture;

extern LButton gButtons[TOTAL_BUTTONS];
extern LButton* lastButton;

extern TTF_Font* gFont;
extern LTexture gTextTexture;

extern SDL_Color textColor;
#endif