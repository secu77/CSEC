/*
	Eagle14 - MiniChat PoC
		Client
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define PUERTO 10000
#define MAXDATAMSG 100



int main(int argc, char *argv[]){

  int fd, bytes;
  char msg[MAXDATAMSG];
  char sent[MAXDATAMSG];
  struct hostent *rec;
  struct sockaddr_in servidor;


  /*Validacion de IP por argumentos*/
  if (argc != 2)
  {
  	printf("\n[*]Uso: %s <SERVER IP>\n", argv[0]);
  	exit(-1);
  }

  if ((rec = gethostbyname(argv[1])) == NULL)
  {
  	printf("\nError con el gethostbyname\n");
  	exit(-1);
  }

  /*Creando el socket*/
  if ((fd = socket(AF_INET, SOCK_STREAM,0)) == -1)
  {
  	printf("\nError con la creacion del socket\n");
  	exit(-1);
  }


  /*Rellenando datos del Servidor*/
  servidor.sin_family = AF_INET;							//Socket no interno, sino a internet
  servidor.sin_port = htons(PUERTO);						//pasar el puerto a el formato de Bytes de Red
  servidor.sin_addr = *((struct in_addr *)rec->h_addr);		//coloca la ip indicada
  memset(servidor.sin_zero,0,8);							//Todo a ceros


  /*Conectandose al servidor*/
  if(connect(fd,(struct sockaddr *) &servidor, sizeof(struct sockaddr)) == -1){
  	printf("\nError intentar conectar\n");
  	exit(-1);
  }


  while(1){

    if((bytes = recv(fd,msg,MAXDATAMSG,0)) == -1){
  	  printf("\nError al recibir la respuesta del servidor\n");

    }else{

      msg[bytes]='\0';	//Finalizando la cadena
      printf("< [Server]: %s\n", msg);
      printf("> [You]: ");
      memset(msg,0,sizeof(msg));

      /*Consiguiendo el mensaje del teclado*/
      fgets(sent, sizeof(sent), stdin);

      /*Enviando mesaje*/
      if((send(fd, sent, sizeof(sent), 0)) == -1){
      	printf("\nError al enviar el mensaje\n");
  	    exit(-1);
      }else{
      	printf("\n");
      }
    }
  
  }

}
