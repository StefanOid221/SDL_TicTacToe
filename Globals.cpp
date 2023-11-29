#include <SDL2/Globals.h>

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

bool playerXTurn = true;
bool myTurn = false;
LTexture gBackgroundTexture;
LTexture gXTexture;
LTexture g0Texture;

LButton gButtons[TOTAL_BUTTONS]; 
LButton* lastButton = nullptr;

LTexture gTextTexture;
TTF_Font* gFont = nullptr;

SDL_Color textColor = { 0, 0, 0 };