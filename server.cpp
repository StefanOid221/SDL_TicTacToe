#include <iostream>
#include <SDL2/Globals.h>
#include <SDL2/Util.h>
#include <SDL2/SDL_net.h>
#include <cstring>

int main( int argc, char *argv[] )
{
    int nPlayers = 0;
    bool playerXTurn = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    IPaddress ip;
    IPaddress *addrs = nullptr;
    int num_addrs = 0;
    num_addrs = SDLNet_GetLocalAddresses(addrs, 0);
    SDLNet_ResolveHost(&ip, nullptr, 1269);

    SDLNet_SocketSet set = SDLNet_AllocSocketSet(2);
    
    TCPsocket server=SDLNet_TCP_Open(&ip);
    TCPsocket client1;
    TCPsocket client2; 

    char text[100] = "Hello client!\n";

    while(1)
    {
        if (nPlayers == 0)
        {
            client1 = SDLNet_TCP_Accept(server);
            
            if (client1) {
                SDLNet_TCP_AddSocket(set, client1);
                nPlayers += 1;
                strcpy(text, "Hello player X");
                SDLNet_TCP_Send(client1, text, strlen(text) + 1);
            }
        }
        if (nPlayers == 1)
        {
            client2 = SDLNet_TCP_Accept(server);
            if (client2) {
                SDLNet_TCP_AddSocket(set, client2);
                nPlayers += 1;
                strcpy(text, "Hello player 0");
                SDLNet_TCP_Send(client2, text, strlen(text) + 1);
            }
        }
        if (nPlayers == 2)
        {
            if (playerXTurn) {
                if (SDLNet_CheckSockets(set, 0) > 0){
                    SDLNet_TCP_Recv(client1, text, 100);
                    SDLNet_TCP_Send(client2, text, strlen(text) + 1);
                    playerXTurn = false;
                }
            }
            else{
                if (SDLNet_CheckSockets(set, 0) > 0){
                    SDLNet_TCP_Recv(client2, text, 100);
                    SDLNet_TCP_Send(client1, text, strlen(text) + 1);
                    playerXTurn = true;
                }
            }
        }
    }
    SDLNet_TCP_Close(server);
    SDLNet_TCP_Close(client1);
    SDLNet_TCP_Close(client2);
    SDLNet_FreeSocketSet(set);
    SDLNet_Quit();
    SDL_Quit();
}