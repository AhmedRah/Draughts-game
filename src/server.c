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

#include "headerFile.h"
#include "identification.h"
#include "game.h"
#include "com_functions.h"


#define Sizebuf 100

#define Menu "\n------ Bonjour au jeu de dame ------\n--- 1) creer une partie\n--- 2) joindre ue partie\n--- 3) reagrder une partie active\n--- 'quit' pour quitter\n------ Votre choix ?\n"
#define LOG_MENU "\n------ Bonjour au jeu de dame ------\n------ 1) Se connecter\n------ 2) S'inscire\n--------> Votre choix : "

// void sendtoall(char* msg,int curr)
// {
// 	int i;
// 	for(i=0;i<)
// }





int main()
{
	// Liste des clients qui vont communiquer avec le serveur
	int clients[MAX_CLIENTS];

	static struct sockaddr_in addr_local ;
	static struct sockaddr_in addr_client ;
	struct hostent *host_client ;
	socklen_t lg;
	
	char * rep = "Well recieved" ;
	char buffer[Sizebuf];

	char *chaine;
	int nb_octets;

	// inialisation d'un socket
	int s;
	s = socket(AF_INET,SOCK_DGRAM,0);
	if (s == -1)
	{
		perror("Erreur dans la creation du socket !!");
		exit(1);
	}

	// Partie du BIND
	struct sockaddr_in sin;
	int ret;
  fun_bind(s,sin,ret);

	lg = sizeof(struct sockaddr_in);

	// ______________________Partie d'indentifaction et acceuil__________________________
	// les donnes d'identification/enregistrement
	char email[30] ;
	char usern[20] ;
	char passw[16] ;

	int accessGranted = 0 ;

	// receive(s,buffer,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);
	host_client = gethostbyaddr(&(addr_client.sin_addr),sizeof(long),AF_INET);
	if(host_client == NULL)
	{
		perror("Erreur gethostbyaddr \n");
		exit(1);
	}	
	// Presenter le menu d'identification au client
	sendMessage(s,LOG_MENU,0,(struct sockaddr *)&addr_client,lg);
	// Recevoir le choix de connexion
	receive(s,buffer,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);
	
	// Si l'utlisateure veut se connecter
	if(strcmp(buffer,"1")==0)
	{// Connexion
		sendMessage(s,"------ Identification ------ \n",0,(struct sockaddr *)&addr_client,lg);
		
		sendMessage(s,"--> Username     : ",0,(struct sockaddr *)&addr_client,lg);
		receive(s,usern,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);

		sendMessage(s,"--> Mot de passe : ",0,(struct sockaddr *)&addr_client,lg);
		receive(s,passw,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);

		if(log_in(usern,passw))
		{
			accessGranted = 1 ;
		}
	}
	else if(buffer == "2")
	{// Enregistrement
		sendMessage(s,"------ Enregistrement ------ \n",0,(struct sockaddr *)&addr_client,lg);

		sendMessage(s,"--> Email       : ",0,(struct sockaddr *)&addr_client,lg);
		receive(s,email,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);

		sendMessage(s,"--> Username    : ",0,(struct sockaddr *)&addr_client,lg);
		receive(s,usern,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);

		sendMessage(s,"--> Mot de passe: ",0,(struct sockaddr *)&addr_client,lg);
		receive(s,passw,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);

		if(sign_up(email,usern,passw))
		{
			accessGranted = 1 ;
		}
	}
	else
	{ // Erreur de choix
		printf("Choix non valide !!\n");
		exit(1);
	}

	// ______________________FIN d'indentifaction et acceuil__________________________

	// Le client n'accedent pas aux jeux sauf si a l'autorisation
	if(accessGranted == 1)
	{
		sendMessage(s,"AG",0,(struct sockaddr *)&addr_client,lg);		
		//envoie Du menu au client
		sendMessage(s,Menu,0,(struct sockaddr *)&addr_client,lg);
		// Recevoir le choix de l'utlisateure
		receive(s,buffer,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);
		
		// si le client veut quitter , on sort
		if (strcmp(buffer,"quit"))
		{
			printf("Demande de terminaison recu !\n");
			exit(0);
		}
	// ------------------------ DEBUT JEU ------------------------

		// Initialisier une table de jeux 
  	pieces Arr_Table[XSIZE_TABLE][YSIZE_TABLE]={0};
		
		if(strcmp(buffer,"3") != 0)
		{
			if(strcmp(buffer,"1"))
			{
				create_game();
				load_game(Arr_Table);
			}
			if (strcmp(buffer,"2"))
			{
				//importer une partie
				load_game(Arr_Table);
			}

			// do
			// {
				
			// } while ({/* condition */});
			




		}
		else // Pour spectater
		{
			// Pour l'instant ca fait 
		}
		
		
		

	// ------------------------ FIN JEU ------------------------  
		
	}
		printf("**************** Arret du serveur ****************\n");
		close(s);
		return 0;
	
}

		// Boucle pour le jeux
		// Attente des donnees emises par le client
		// do
		// {
		// 	receive(s,buffer,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);
		// 	sendMessage(s,Menu,0,(struct sockaddr *)&addr_client,lg);
			
		// 	// Affichage des messages recu
		// 	printf(" Le message recu : %s \n",buffer);
			
		// 	host_client = gethostbyaddr(&(addr_client.sin_addr),sizeof(long),AF_INET);
		// 	if(host_client == NULL)
		// 	{
		// 		perror("Erreur gethostbyaddr \n");
		// 		exit(1);
		// 	}
			

		// 	// Envoie des messages

		// 	//envoie reponse au client
		// 	nb_octets = sendto(s,rep,strlen(rep)+1,0,(struct sockaddr *)&addr_client,lg);
		// 	if(nb_octets == -1)
		// 	{
		// 		perror("erreur d'envoie de message");
		// 		exit(1);
		// 	}

		// } while (1);
