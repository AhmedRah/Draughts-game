#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

// #include "../include/SDL.h"
#include "../include/SDL_net.h"
#include <SDL2/SDL.h>


#include "headerFile.h"

typedef struct Piece {
  int team ; //l'equipe : 1 pour premier joueur  , 2 pour deuxieme joueur.
  int statut ; // 0 pour piece normale , 1 pour hors-jeux , 2 pour dame
} pieces;


typedef struct Games
{
  pieces* Arr_Table ; // Tableaux de jeux
  pieces* Arr_pieces ;// Tableaux des peices
} game ;

//

void play()
{
  // Creer une table de jeux vide
  pieces Arr_Table[XSIZE_TABLE][YSIZE_TABLE] = {0,0};
  // Initialise les joueurs 
  pieces joueur1 ={1,0};
  pieces joueur2 ={2,0}; 

  
  for(int y=0;y<YSIZE_TABLE;y++)
  {
    //positionner les cases des joueurs 1 et 2
    for(int x=0;x<XSIZE_TABLE;x++)
    {  
      if((x % 2 == 0 && y % 2 != 0) || (x % 2 != 0 && y % 2 == 0))
      {
        if(y<=3)
          Arr_Table[x][y]= joueur1 ;
        if(y>=6)
          Arr_Table[x][y]= joueur2 ;
      }
    }
  } 

  for (int j = 0; j < YSIZE_TABLE; j++)
  {
    for (int i = 0; i < XSIZE_TABLE; i++)
    {
      printf("%d ",Arr_Table[i][j].team);
    }
    printf("\n");
  }
  
} 

int main(void)
{
  TCPsocket sd, csd; 
  /* Socket descriptor, Client socket descriptor */ 
  IPaddress ip, *remoteIP; 
  int quit, quit2; 
  char buffer[512];

  if (SDLNet_Init() < 0) 
  { 
    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); 
  }

  /* Resolving the host using NULL make network interface to listen */ 
  if (SDLNet_ResolveHost(&ip, NULL, 2000) < 0) 
  {
    fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError()); exit(EXIT_FAILURE); 
  }

  /* Open a connection with the IP provided (listen on the host's port) */ 
  if (!(sd = SDLNet_TCP_Open(&ip))) 
  { 
    fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError())
    ; exit(EXIT_FAILURE); 
  }

  /* Wait for a connection, send data and term */ 
  quit = 0; 
  while (!quit) 
  { /* This check the sd if there is a pending connection. * If there is one, accept that, and open a new socket for communicating */ 
    if ((csd = SDLNet_TCP_Accept(sd))) 
    { 
      /* Now we can communicate with the client using csd socket * sd will remain opened waiting other connections */

      /* Get the remote address */ 
      if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd))) 
        /* Print the address, converting in the host format */ 
        printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port)); 
      else 
        fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());

      quit2 = 0; 
      while (!quit2) 
      { 
        if (SDLNet_TCP_Recv(csd, buffer, 512) > 0) 
        { 
          printf("Client say: %s\n", buffer);

          if(strcmp(buffer, "exit") == 0) 
          /* Terminate this connection */ 
          { 
            quit2 = 1; printf("Terminate connection\n"); 
          } 
          if(strcmp(buffer, "quit") == 0) 
          /* Quit the program */ 
          { 
            quit2 = 1; 
            quit = 1; 
            printf("Quit program\n"); 
          } 
        } 
      }

      /* Close the client socket */ 
      SDLNet_TCP_Close(csd);   
    } 
  }

  SDLNet_TCP_Close(sd); 
  SDLNet_Quit();

  return EXIT_SUCCESS; 
}