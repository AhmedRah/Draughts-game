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

#define Sizebuf 100

#include "headerFile.h"
#include "identification.h"
#include "game.h"
#include "com_functions.h"



int main ()
{
	// cote client
	struct hostent *serveur_host ;
	static struct sockaddr_in addr_serveur ;
	socklen_t lg ;
	int s ;
	char buffer[Sizebuf];
	int nb_octets ;

	s = socket(AF_INET,SOCK_DGRAM,0);
	if (s == -1)
	{
		perror("Erreur dans la creation du socket !!");
		exit(1);
	}

	serveur_host = gethostbyname("AhmedBackup");
	if(serveur_host == NULL)
	{
		perror("erreur avec l'adresse serveur");
		exit(1);
	} 
	

	// Partie du BIND
	int i, ret;

	addr_serveur.sin_family = AF_INET;
	addr_serveur.sin_port = htons(8000);

	addr_serveur.sin_addr.s_addr = htonl(INADDR_ANY);

	// bzero(&addr_serveur, sizeof(struct sockaddr_in));
	for (i=0; i<8; i++) 
	{
		addr_serveur.sin_zero[i] = 0;
	}

	memcpy(&addr_serveur.sin_addr.s_addr,serveur_host -> h_addr, serveur_host -> h_length);


	// --------- Communication avec le serveur ______________________
	// Allocation de memoire pour le message qu'on va envoyer
	char *mes = (char*)malloc(50);
	char *rep = (char*)malloc(50);

	// les donnes d'identification/enregistrement
	char email[30] ;
	char usern[20] ;
	char passw[16] ;

  //recevoir le menu
  receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
  // envoie du choix du menu
	fgets(mes,50,stdin);
	mes[strcspn(mes, "\n")] = 0 ;
  sendMessage(s,mes,0,(struct sockaddr*)&addr_serveur,lg);

  // Si l'utlisateure veut se connecter
	if(strcmp(mes,"1")==0)
	{// Connexion
    receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    
    receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    fgets(usern,20,stdin);
	  usern[strcspn(usern, "\n")] = 0 ;
		sendMessage(s,usern,0,(struct sockaddr*)&addr_serveur,lg);
		
    receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    fgets(passw,16,stdin);
	  passw[strcspn(passw, "\n")] = 0 ;
    sendMessage(s,passw,0,(struct sockaddr*)&addr_serveur,lg);
	}
	else if(mes == "2")
	{// Enregistrement
		receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    
    receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    fgets(email,30,stdin);
	  email[strcspn(email, "\n")] = 0 ;
    sendMessage(s,email,0,(struct sockaddr*)&addr_serveur,lg);

    receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    fgets(usern,20,stdin);
	  usern[strcspn(usern, "\n")] = 0 ;
		sendMessage(s,usern,0,(struct sockaddr*)&addr_serveur,lg);
		
    receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    fgets(passw,16,stdin);
	  passw[strcspn(passw, "\n")] = 0 ;
    sendMessage(s,passw,0,(struct sockaddr*)&addr_serveur,lg);
	}
	else
	{ // Erreur de choix
		printf("Choix non valide !!\n");
		exit(1);
	}
  // recvoire la permission pour entrer a jouer
  receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
  if(strcmp(rep,"AG")) // AG : Access Granted
  {
    // recevoir le menu
    receive(s,rep,sizeof(rep),0,(struct sockaddr*)&addr_serveur,&lg);
    //envoi du choix
    fgets(mes,50,stdin);
	  mes[strcspn(mes, "\n")] = 0 ;
    sendMessage(s,mes,0,(struct sockaddr*)&addr_serveur,lg);

    if(strcmp(buffer,"1"))
		{

		}
		else if (strcmp(buffer,"2"))
		{
			
		}
		else if (strcmp(buffer,"3"))
		{
			// Pour l'instant ca marche pas
		}
		else if (strcmp(buffer,"quit"))
		{
			printf("Demande de terminaison recu !\n");
			exit(0);
		}

  }

// 	do
// 	{	
// 		printf("\n message : ");
// 		fgets(mes,50,stdin);
// 		mes[strcspn(mes, "\n")] = 0 ;
		
// 		// envoie de message
// 		lg = sizeof(struct sockaddr_in);
// 		nb_octets = sendto(s,mes,strlen(mes)+1,0,(struct sockaddr*)&addr_serveur,lg);
// 		if(nb_octets == -1)
// 		{
// 			perror("Erreur d'envoi \n");
// 			exit(1);
// 		}
// 		printf(" Client : Packet envoye \n");

// 		// Attendre la reponse du serveur
// 		nb_octets = recvfrom(s,buffer,Sizebuf,0,(struct sockaddr*)&addr_serveur,&lg);
// 		if(nb_octets == -1)
// 		{
// 			perror("Erreur reponse serveur");
// 			exit(1);
// 		}

// 		printf(" Reponse recu : %s \n", buffer);
		
// 		// tester si le messsage recu est Quit
// 		if(strcmp(mes,"quit") == 0)
// 		{
// 			printf("Demande d'arret saisie : Fermeture du Client \n");
// 			close(s);
// 			exit(1);
// 		}

// 	}while(1);

	close(s);
	return 0;
}