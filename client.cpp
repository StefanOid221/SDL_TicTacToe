#include <iostream>
#include <SDL2/Globals.h>
#include <SDL2/Util.h>
#include <SDL2/SDL_net.h>
#include <cstring>

int main( int argc, char *argv[] )
{
    if (!init())
    {
        printf( "Failed to initialize!%s\n", SDL_GetError());
    }
    else
    {
        if (!loadMedia()){
            printf( "Failed to initialize!%s\n", SDL_GetError());
        }
        else {
            bool quit = false;
            bool imPlayer1 = false;
            LTexture* currentTexture = NULL;
            SDL_Event e;

            IPaddress ip;
            SDLNet_SocketSet set = SDLNet_AllocSocketSet(2);
            SDLNet_ResolveHost(&ip, "127.0.0.1", 1269);

            TCPsocket client=SDLNet_TCP_Open(&ip);

            SDLNet_TCP_AddSocket(set, client);
            char text[100];
            int position = 0;

            SDLNet_TCP_Recv(client, text, 100);  
            myTurn = text[strlen(text) - 1] == 'X';
            imPlayer1 = myTurn;
            // SDLNet_TCP_Close(client);   
            while (!quit)
            {
                if (SDLNet_CheckSockets(set, 0) > 0) {
                    SDLNet_TCP_Recv(client, text, 100);
                    myTurn = true;
                    position = text[0] - '0'; // Interesting hack
                    gButtons[position].changeSprite(imPlayer1);
                }
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
                        SDLNet_TCP_Close(client);
					}
					
                    if (myTurn){
                        for( int i = 0; i < TOTAL_BUTTONS; ++i )
                        {
                            gButtons[ i ].handleEvent( &e, imPlayer1 );
                        }
                    }
					//Handle button events
				}
                if (lastButton != nullptr){
                    int position = lastButton->getPosition();
                    sprintf(text, "%d", position);
                    SDLNet_TCP_Send(client, text, strlen(text) + 1);
                    lastButton = nullptr;
                }
                SDL_RenderClear( gRenderer );
                currentTexture = &gBackgroundTexture;
                currentTexture->render(0,0);
                gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, SCREEN_HEIGHT + 100);
                //Render buttons
				for( int i = 0; i < TOTAL_BUTTONS; ++i )
				{
					gButtons[ i ].render();
				}
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    
    close();

            
    return 0;
}