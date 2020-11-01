// ------------------------------------------------------------------
//  Projet Reseau 
//  Realiser par BAH Elhadj Oumar et  RAHMOUNI Ahmed
// ------------------------------------------------------------------

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
#include "game.h"


int create_game()
{
  // Creer une table de jeux vide
  pieces Arr_Table[XSIZE_TABLE][YSIZE_TABLE] = {0};
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
  FILE* file = fopen("gameTable.txt","w");
  for (int j = 0; j < YSIZE_TABLE; j++)
  {
    for (int i = 0; i < XSIZE_TABLE; i++)
    {
      fprintf(file,"%d",Arr_Table[i][j].team);
    }
  }
  fclose(file);
  return 0;
}
int load_game(pieces Arr_Table[XSIZE_TABLE][YSIZE_TABLE])
{
  // pieces* empty = malloc(1*sizeof(pieces));
  // pieces* joueur1 = malloc(1*sizeof(pieces));
  // pieces* joueur2 = malloc(1*sizeof(pieces));
  // joueur1->team = 1;joueur1->statut = 0;
  // joueur2->team = 2;joueur2->statut = 0;
  // empty->team   = 0;empty->statut   = 0;
  // charger le table de jeux
  char fileline[XSIZE_TABLE*YSIZE_TABLE]  = {0};
  
  FILE *file = fopen("gameTable.txt","r");
  if(file == NULL)
    return 0;
  fgets(fileline,XSIZE_TABLE*YSIZE_TABLE,file);
  
  for(int y=0;y<YSIZE_TABLE; y++)
  {
    for (int x = 0; x < XSIZE_TABLE; x++)
    {
      switch (fileline[y*YSIZE_TABLE + x])
      {
        case '0':
          Arr_Table[x][y].team = 0;
          Arr_Table[x][y].statut = 0;
          break;
        case '1':
          Arr_Table[x][y].team = 1;
          Arr_Table[x][y].statut = 0;
          break;
        case '2':
          Arr_Table[x][y].team = 2;
          Arr_Table[x][y].statut = 0;
          break;  
      }
    }
  }

  fclose(file);
  return 1;
} 


// return 0 si la piece ne peut pas se deplacer a la case suivante
//        1 si c'est possible
//        2 si la piece mange la piece de la case suivante
int moveValid(pieces ArrayTable[XSIZE_TABLE][YSIZE_TABLE],int xDep , int yDep, int xArr, int yArr)
{
  int valid = 0;
  if((xArr % 2 == 0 && yArr % 2 != 0) || (xArr % 2 != 0 && yArr % 2 == 0)) //verifie si la case est noir c'est-a-dire valide
  {

    //Implementation pour la piece dame.........................

    if(ArrayTable[xArr][yArr].team != 0) //verifie si la case n'est pas vide
    {
      if(ArrayTable[xDep][yDep].team == ArrayTable[xArr][yArr].team) //verifie si la case est occupee par une piece de la meme equipe
        valid = 0;

      // if(ArrayTable[xDep][yDep].team != ArrayTable[xArr][yArr].team) //verifie si la case est occupee par une piece de l'equipe adverse
      //   valid = 2;
    }
    else{
      if(ArrayTable[xDep][yDep].team == 1)
      {
        if((xArr == xDep+2) && (ArrayTable[xArr+1][yArr-1].team != ArrayTable[xDep][yDep].team) )
          valid=2;
        if((xArr == xDep-2) && (ArrayTable[xArr-1][yArr-1].team != ArrayTable[xDep][yDep].team) )
          valid=2;
      }
      else if(ArrayTable[xDep][yDep].team == 2)
      {
        if((xArr == xDep+2) && (ArrayTable[xArr-1][yArr+1].team != ArrayTable[xDep][yDep].team) )
          valid=2;
        if((xArr == xDep-2) && (ArrayTable[xArr+1][yArr+1].team != ArrayTable[xDep][yDep].team) )
          valid=2;
      }
      valid = 1; //si la case est vide et valide
    }

  }
  return valid;
}

int movePiece(pieces ArrayTable[XSIZE_TABLE][YSIZE_TABLE],int xDep , int yDep, int xArr, int yArr)
{
  if(moveValid(ArrayTable,xDep,yDep,xArr,yArr) == 1)
  {
    //printf("ici");
    pieces temp = ArrayTable[xDep][yDep] ;
    ArrayTable[xDep][yDep].team = 0 ;
    ArrayTable[xDep][yDep].statut = 0;
    ArrayTable[xArr][yArr] = temp ;
  }else if(moveValid(ArrayTable,xDep,yDep,xArr,yArr) == 2)
  {
    
    if(ArrayTable[xDep][yDep].team == 1)
    {
      if(xArr == xDep+2)
      {
        ArrayTable[xArr+1][yArr-1].statut = 1;
      }
      if(xArr == xDep-2)
      {
        ArrayTable[xArr+1][yArr-1].statut = 1;
      }
    }
    else if(ArrayTable[xDep][yDep].team == 2)
    {
      if(xArr == xDep+2)
      {
        ArrayTable[xArr-1][yArr+1].statut = 1;
      }
      if(xArr == xDep-2)
      {
        ArrayTable[xArr+1][yArr+1].statut = 1;
      }
    } 
    pieces temp = ArrayTable[xDep][yDep] ;
    ArrayTable[xArr][yArr] = temp ;
    ArrayTable[xDep][yDep].team = 0 ;
    ArrayTable[xDep][yDep].statut = 0;
    
  }else printf("Deplacement impossible");
  return 0 ;
}


// int main()
// {
//   create_game();

//   // Creer une table de jeux vide
//   pieces Arr_Table[XSIZE_TABLE][YSIZE_TABLE]={0};

//   load_game(Arr_Table);
  
//   return EXIT_SUCCESS;
// }
