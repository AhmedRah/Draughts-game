#ifndef MY_DEFINES_H
#define MY_DEFINES_H

  #define NB_PLAYERS 2

  #define NB_PIECES 40  
  #define NB_PIECES1 20
  #define NB_PIECES2 20

  #define XSIZE_TABLE 10
  #define YSIZE_TABLE 10

  #ifndef SOME_HEADER_GUARD_WITH_UNIQUE_NAME
  #define SOME_HEADER_GUARD_WITH_UNIQUE_NAME

  typedef struct Piece {
    int team ; //l'equipe : 1 pour premier joueur  , 2 pour deuxieme joueur.
    int statut ; // 0 pour piece normale , 1 pour hors-jeux , 2 pour dame
  } pieces;

  #endif

#endif