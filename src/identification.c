#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "headerFile.h"

// Return 1 if credentials are correct , 0 elswhere
int log_in(char* username, char* pass)
{
  // lecture du fichier qui continet les donnes d'identification
  FILE* data_file = fopen("data.txt","rb");
  // Initialisation/Allcoation memoire pour les string des donnees
  int valide = 0; //Output de la fonction : 1 si valide , 0 sinon
  char* str1 = malloc(sizeof(char));
  char* str2 = malloc(sizeof(char));
  char* str3 = malloc(sizeof(char));
  // On navigue tout les lignes du fichier (chaque ligne represente un utilisateure)
  char* line= malloc(sizeof(char));
  while (fgets(line,70,data_file))
  {
    sscanf(line,"%s %s %s",str1,str2,str3);
    if(strcmp(str2,username)==0 && strcmp(str3,pass)==0)
    {
      valide = 1;
      break ;
    }
  }
  // verifier les conditions
  if(valide)
  {
    printf("----| Login Successful |----\n");
  }
  else
  {
    printf("----| Login FAILED ! |----\n");
  }

  fclose(data_file);
  return valide ;
}

int sign_up(char* email,char* username,char* pass)
{
  FILE* data_file = fopen("data.txt","a+");
  if(data_file == NULL)
  {
    perror("failed to open data file");
    exit(1);
  } 
  // enregistrer les donnees dans notre base de donnees
  fprintf(data_file,"%s\t%s\t%s\n",email,username,pass);
  // fprintf(data_file,"%d",EOF); // indiquer la fin du fichier
  fclose(data_file);

  return EXIT_SUCCESS;
}
