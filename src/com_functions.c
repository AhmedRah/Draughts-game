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


// Arreter le serveur
void EndComu(char* buffer)
{
		// tester si le messsage recu est Quit
		if(strcmp(buffer,"quit") == 0)
		{
			printf("Demande d'arret recu : Fermeture du serveur\n");
			exit(1);
		}
}

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
	//sortir si le message recue est "quit"
	EndComu(buf);
}

//Fonction pour envoyer les messages aux clients
void sendMessage(int s,void * rep, int flags, const struct sockaddr *dest_addr,socklen_t addrlen)
{
		//envoie reponse au client
		int nb_octets = sendto(s,rep,strlen(rep)+1,flags,dest_addr,addrlen);
		if(nb_octets == -1)
		{
			perror("erreur d'envoie de message");
			exit(1);
		}
}



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