#include <SDL2/Globals.h>
#include <SDL2/SDL_net.h>

bool init()
{
	//Initialization flag
	bool success = true;
    playerXTurn = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else if (SDLNet_Init() < 0){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT + 200, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	gFont = TTF_OpenFont( "lazy.ttf", 28 );

	//Load press texture
	if( !gBackgroundTexture.loadFromFile( "tablero.png" ) )
	{
		printf( "Failed to load tablero texture!%s\n", SDL_GetError() );
		success = false;
	}
	
	//Load up texture
	if( !gXTexture.loadFromFile( "XButton.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}

    if( !g0Texture.loadFromFile( "0Button.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	//Open the font
    
    if( gFont == nullptr )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else{
        gButtons[ 0 ].setPosition( 0, 0, 0);
        gButtons[ 1 ].setPosition( SCREEN_WIDTH/3, 0, 1);
        gButtons[ 2 ].setPosition( 2*SCREEN_WIDTH/3, 0, 2);
        gButtons[ 3 ].setPosition( 0, SCREEN_HEIGHT/3, 3);
        gButtons[ 4 ].setPosition( SCREEN_WIDTH/3, SCREEN_HEIGHT/3, 4);
        gButtons[ 5 ].setPosition( 2*SCREEN_WIDTH/3, SCREEN_HEIGHT/3, 5);
        gButtons[ 6 ].setPosition( 0, 2*SCREEN_HEIGHT/3, 6);
        gButtons[ 7 ].setPosition( SCREEN_WIDTH/3, 2*SCREEN_HEIGHT/3, 7);
        gButtons[ 8 ].setPosition( 2*SCREEN_WIDTH/3, 2*SCREEN_HEIGHT/3, 8);
        
        if( !gTextTexture.loadFromRenderedText( "Player 1 turn", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

	return success;
}

void close()
{
	//Free loaded images
	gBackgroundTexture.free();
	gXTexture.free();
	g0Texture.free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = nullptr;
	gRenderer = nullptr;
	lastButton = nullptr;

	TTF_CloseFont( gFont );
    gFont = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	SDLNet_Quit();
}
