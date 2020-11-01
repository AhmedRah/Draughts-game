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

#define Sizebuf 100

#define Menu "\n------ Bonjour au jeu de dame ------\n--- 1) creer une partie\n--- 2) joindre ue partie\n--- 3) reagrder une partie active\n------ Votre choix ?\n"

// void sendtoall(char* msg,int curr)
// {
// 	int i;
// 	for(i=0;i<)
// }


// Fonction pour recevoire les message des clients
void receive(int s,void* buf,ssize_t len,int flags,struct sockaddr* srcaddr,socklen_t* addrlen)
{
	// recevoire les instructions de clinet
	int nb_octets = recvfrom(s,buf,Sizebuf,0,srcaddr,addrlen);
	if(nb_octets == -1)
	{
		perror("Erreur de reception \n");
		exit(1);
	}
}
//Fonction pour envoyer les messages aux clients
// void sendmsg()

// Fonction du bind
void fun_bind(int s, struct sockaddr_in sin , int ret)
{
  sin.sin_family = AF_INET;
	sin.sin_port = htons(8000);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	for (int i=0; i<8; i++) 
	{
		sin.sin_zero[i] = 0;
	}
	ret = bind(s, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));
	if (ret<0) 
	{
		printf("error");
	}
}



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



  printf("**************** Serveur local UDP ****************\n");
	// Attente des donnees emises par le client
	listen(s,20);
	// do
	// {
	// 	receive(s,buffer,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);

	// 	// tester si le messsage recu est Quit
	// 	if(strcmp(buffer,"quit") == 0)
	// 	{
	// 		printf("Demande d'arret recu : Fermeture du serveur\n");
	// 		exit(1);
	// 	}
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
	// 	nb_octets = sendto(s,Menu,strlen(Menu)+1,0,(struct sockaddr *)&addr_client,lg);
	// 	if(nb_octets == -1)
	// 	{
	// 		perror("erreur d'envoie de message");
	// 		exit(1);
	// 	}
	// 	//envoie reponse au client
	// 	nb_octets = sendto(s,rep,strlen(rep)+1,0,(struct sockaddr *)&addr_client,lg);
	// 	if(nb_octets == -1)
	// 	{
	// 		perror("erreur d'envoie de message");
	// 		exit(1);
	// 	}

	// } while (1);

	printf("**************** Arret du serveur ****************\n");

	close(s);
	return 0;
}