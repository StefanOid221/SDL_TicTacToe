#ifndef LBUTTON_H
#define LBUTTON_H

#include "Constants.h"


class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y, int pos);

		//Handles mouse event
		void handleEvent( SDL_Event* e, bool imPlayer1 );
	
		//Shows button sprite
		void render();

		int getPosition();

		void changeSprite(bool imPlayer1);

		private:
		//Top left position
		SDL_Point mPosition;

		int boardPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;

};

#endif