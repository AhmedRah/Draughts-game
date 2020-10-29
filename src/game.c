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
    //positionner les cases de joueur 1
    for(int x=0;x<XSIZE_TABLE;x++)
    {  
      if((x % 2 == 0 && y % 2 != 0) || (x % 2 != 0 && y % 2 == 0))
      {
        if(y<4)
          Arr_Table[x][y]= joueur1 ;
        if(y>5)
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
  play();
  return 0 ;
}