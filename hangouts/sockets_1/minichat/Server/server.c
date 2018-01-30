/*
	Eagle14 - MiniChat PoC
		Server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#define PUERTO 10000		//Puerto de escucha por default
#define Ncox 2			//Por el momento una única conexion

int main(int argc, char *argv[]){

	struct sockaddr_in cliente, servidor;
	int lensckadd = sizeof(struct sockaddr);
	int recsocket = 0, recsock = 0, recvresp = 0;
	int conectado = 0, right = 0;
	unsigned int lens = sizeof(struct sockaddr_in);
	unsigned char buffer[256];
	char sender[100];
	time_t ttime;
	time(&ttime);

	/*Validacion insignificante de parametros*/
	if(argc != 1){
		printf("\n[+]Uso: %s\n\n", argv[0]);
		exit(-1);
	}

	/*Validaciones con la creacion y apertura del socket*/
	if((recsocket = socket(AF_INET, SOCK_STREAM,0)) == -1){
		printf("\n[!]Error abriendo el socket\n");
		exit(-1);
	}

	/*Rellenando datos del Servidor*/
	servidor.sin_family = AF_INET;				//Socket no interno, sino a internet
	servidor.sin_port = htons(PUERTO);			//pasar el puerto a el formato de Bytes de Red
	servidor.sin_addr.s_addr = INADDR_ANY;		//coloca ip auto
	memset(servidor.sin_zero,0,8);				//Todo a ceros


	/*Validacion de la asociacion con el puerto de la máquina*/
	if(bind(recsocket,(struct sockaddr*) &servidor, lensckadd) == -1){
		printf("\n[!]Error en la fase de asociacion\n");
		exit(-1);
	}

	/*Validacion por si falla la puesta en escucha*/
	if(listen(recsocket,Ncox) == -1){
		printf("\n[!]Error en la fase de escucha\n");
		exit(-1);
	}


	/*A la espera de una conexion*/
	while(!conectado){
		printf("\n[/]Esperando conexion...\n");

		/*Validacion por si hay problemas con el recibimiento*/
		if((recsock = accept(recsocket,(struct sockaddr *) &cliente, &lens)) == -1){
			
			printf("\n[!]Error en la fase de aceptacion\n");
			exit(-1);
		}else{
			printf("\n> %s",ctime(&ttime));
			printf("  [*]Se conectó un cliente con IP:%s\n",inet_ntoa(cliente.sin_addr));

			/*Enviar mensaje de bienvenida*/
			send(recsock,"Bienvenido al Eagle14!\n",24,0);

			while(!right){

			  recvresp = recv (recsock, &buffer, sizeof (buffer), 0);

			  /*Comprobacion de recepcion de clave*/
			  if(recvresp <= 0){

			  }else{
			  	printf("\n> [%s]: %s",inet_ntoa(cliente.sin_addr), buffer);

			  	printf("\n< [You]: ");
			  	/*Consiguiendo el mensaje del teclado*/
      			fgets(sender, sizeof(sender), stdin);

      			/*Enviando mesaje*/
			    if((send(recsock, sender, sizeof(sender), 0)) == -1){
			      printf("\nError al enviar el mensaje\n");
			  	  exit(-1);
			    }else{
			      printf("\n");
			    }
			  }

			}
			
		}
		close(recsocket);
		close(recsock);
	}
	return 0;
}
