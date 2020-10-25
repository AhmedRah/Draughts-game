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

// Function to communnicate with a client 
void comm_client(int nb_octets ,int s , char* buffer , struct sockaddr_in addr_local , struct sockaddr_in addr_client ,struct hostent *host_client, socklen_t lg, char * rep)
{
  nb_octets = recvfrom(s,buffer,Sizebuf,0,(struct sockaddr *)&addr_client,&lg);
		if(nb_octets == -1)
		{
			perror("Erreur de reception \n");
			exit(1);
		}
		
		host_client = gethostbyaddr(&(addr_client.sin_addr),sizeof(long),AF_INET);
		if(host_client == NULL)
		{
			perror("Erreur gethostbyaddr \n");
			exit(1);
		}

		// Affichage des messages recu
		printf(" Le message recu : %s \n",buffer);

		// Envoie des messages
		nb_octets = sendto(s,rep,strlen(rep)+1,0,(struct sockaddr *)&addr_client,lg);
		if(nb_octets == -1)
		{
			perror("erreur d'envoie de message");
			exit(1);
		}

		// tester si le messsage recu est Quit
		if(strcmp(buffer,"quit") == 0)
		{
			printf("Demande d'arret recu : Fermeture du serveur\n");
			exit(1);
		}
}

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
	do{
		comm_client(nb_octets ,s ,buffer ,addr_local ,addr_client ,host_client,lg,rep);

	}while(1);

	printf("**************** Arret du serveur ****************\n");

	close(s);
	return 0;
}