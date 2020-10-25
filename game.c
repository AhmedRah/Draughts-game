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

typedef struct piece {
  int x; // positon sur l'axe d'abscisses
  int y; // position sur l'axe d'ordonnees
  int statut ; // 0 pour piece normale , 1 pour hors-jeux , 2 pour dame
} piece;


typedef struct table_jeux {
  struct  liste_peice ;


}table;



int main(void)
{
  


  return 0;
}