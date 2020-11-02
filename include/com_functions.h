// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <netdb.h>
// #include <errno.h>

#ifndef DEF_COM_FUN
#define DEF_COM_FUN

  //Fonctions utiliser
  void receive(int s,void* buf,ssize_t len,int flags,struct sockaddr* srcaddr,socklen_t* addrlen);
  void sendMessage(int s,void * rep, int flags, const struct sockaddr *dest_addr,socklen_t addrlen);
  void EndComu(char* buffer);
  void fun_bind(int s, struct sockaddr_in sin);


#endif