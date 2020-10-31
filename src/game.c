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
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_net.h>
#include "headerFile.h"

// typedef struct Piece {
//   int team ; //l'equipe : 1 pour premier joueur  , 2 pour deuxieme joueur.
//   int statut ; // 0 pour piece normale , 1 pour hors-jeux , 2 pour dame
// } pieces;


// typedef struct Games
// {
//   pieces* Arr_Table ; // Tableaux de jeux
//   pieces* Arr_pieces ;// Tableaux des peices
// } game ;

//

int create_game()
{
  // Creer une table de jeux vide
  pieces Arr_Table[XSIZE_TABLE][YSIZE_TABLE] = {0,0};
  // Initialise les joueurs 
  pieces joueur1 = {1,0};
  pieces joueur2 = {2,0}; 

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
  FILE* file = fopen("game.txt","a+");
  for (int j = 0; j < YSIZE_TABLE; j++)
  {
    for (int i = 0; i < XSIZE_TABLE; i++)
    {
      fprintf(file,"%d",Arr_Table[i][j].team);
    }
  }
  fclose(file);

  for (int j = 0; j < YSIZE_TABLE; j++)
  {
    for (int i = 0; i < XSIZE_TABLE; i++)
    {
      printf("%d ",Arr_Table[i][j].team);
    }
  }
  return 0;
}
int load_game(pieces* Arr_Table[XSIZE_TABLE][YSIZE_TABLE])
{
  pieces* joueur1 = (pieces*)(1*sizeof(pieces));
  pieces* joueur2 = (pieces*)(1*sizeof(pieces));
  joueur1->team = 1;joueur1->team = 0;
  joueur2->team = 1;joueur2->team = 0;
  // charger le table de jeux
  char fileline[XSIZE_TABLE*YSIZE_TABLE]  = {0};
  
  FILE *file = fopen("game.txt","r");
  if(file == NULL)
    return 0;
  fgets(fileline,XSIZE_TABLE*YSIZE_TABLE,file);
  
  for(int y=0;y<YSIZE_TABLE;y++)
  {
    for (int x = 0; x < XSIZE_TABLE; x++)
    {
      switch (fileline[y*YSIZE_TABLE + x])
      {
        case '1':
          Arr_Table[x][y] = joueur1;
          break;
        case '2':
          Arr_Table[x][y] = joueur2;
          break;  
      }
    }
  }
  fclose(file);
  return 1;
} 

int main()
{
  create_game();

  // // Creer une table de jeux vide
  pieces *Arr_Table[XSIZE_TABLE][YSIZE_TABLE] = {0,0};
  load_game(Arr_Table);
  
  // for (int j = 0; j < YSIZE_TABLE; j++)
  // {
  //   for (int i = 0; i < XSIZE_TABLE; i++)
  //   {
  //     printf("%d ",Arr_Table[i][j]->team);
  //   }
  // }
  return EXIT_SUCCESS;
}