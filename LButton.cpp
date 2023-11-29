#include <SDL2/LButton.h>
#include <SDL2/Globals.h>

LButton::LButton() 
{
	mPosition.x = 0;
	mPosition.y = 0;
	boardPosition = 0;
	mCurrentSprite = BUTTON_SPRITE_NOT_SELECTED;
}

void LButton::setPosition( int x, int y, int pos)
{
	mPosition.x = x;
	mPosition.y = y;
	boardPosition = pos;
}

void LButton::handleEvent( SDL_Event* e, bool imPlayer1 )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
        
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}
		//Mouse is inside button
		if (inside & mCurrentSprite == BUTTON_SPRITE_NOT_SELECTED)
		{
            if (e->type == SDL_MOUSEBUTTONDOWN){
                if (imPlayer1 & myTurn){
                    mCurrentSprite = BUTTON_SPRITE_X_SELECTED;
                    playerXTurn = false;
					gTextTexture.loadFromRenderedText( "Player 2 turn", textColor );
					lastButton = this;
					myTurn = false;
                }
                else{
					if (myTurn){
						mCurrentSprite = BUTTON_SPRITE_0_SELECTED;
						playerXTurn = true;
						gTextTexture.loadFromRenderedText( "Player 1 turn", textColor );
						lastButton = this;
						myTurn = false;
					}

                }
            }
		}
	}
}

void LButton::render()
{
	//Show current button sprite
	switch(mCurrentSprite){
        case BUTTON_SPRITE_0_SELECTED:
        g0Texture.render(mPosition.x, mPosition.y, NULL, &BUTTON_SCALE_SIZE);
        break;
        case BUTTON_SPRITE_X_SELECTED:
        gXTexture.render(mPosition.x, mPosition.y, NULL, &BUTTON_SCALE_SIZE);
        break;
    }
}

int LButton :: getPosition(){
	return boardPosition;
}

void LButton:: changeSprite(bool imPlayer1){
	if (imPlayer1){
		mCurrentSprite = BUTTON_SPRITE_0_SELECTED;
		gTextTexture.loadFromRenderedText( "Player 1 turn", textColor );
	}
	else {
		mCurrentSprite = BUTTON_SPRITE_X_SELECTED;
		gTextTexture.loadFromRenderedText( "Player 2 turn", textColor );
	}
}