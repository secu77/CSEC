/*########################################################
*
*  Estructuras y funciones explicadas por Secury
*  y recopiladas de la Bibliografía citada..
*
*#########################################################*/




//ESTRUCTURAS COMUNES EN EL USO DE SOCKETS


struct sockaddr
{

  unsigned short sa_family;		/* familia de la dirección */
  char sa_data[14];				/* 14 bytes de la dirección del protocolo */

}




struct sockaddr_in
{

  short int sin_family;				//Tipo de Socket (AF_INET o AF_UNIX)
  unsigned short int sin_port;		//htons(PUERTO)
  struct in_addr sin_addr;			//Dirección IP (INADDR_ANY -> la pone automaticamente)
  unsigned char sin_zero[8];		//Todo a ceros con -> bzero(&(sockadrr_in.sin_zero),8);

};




struct in_addr
{

  unsigned long s_addr;		//Direccion de Internet(IP)

};




struct hostent								// Se utiliza para Datagramas (UDP)
{

  char *h_name;								//El nombre oficial del nodo.
  char **h_aliases;							//Lista de Alias.
  int h_addrtype;							//Tipo de dirección del nodo.
  int h_length;								//Longitud de la dirección.
  char **h_addr_list;						//Lista de direcciones del nombre del servidor.
  #define h_addr_list h_addr_list[0]		//Dirección, para la compatibilidad con anteriores.

};




/*	CONVERSIONES	

• htons() -> “Nodo a variable corta de Red”
• htonl() -> “Nodo a variable larga de Red”
• ntohs() -> “Red a variable corta de Nodo”
• ntohl() -> “Red a variable larga de Nodo”

[*]Una cosa importante, es que sin_addr y sin_port , de la estructura sockaddr_in,
deben ser del tipo Ordenación de Bytes para Redes.

*/



/*	DIRECCIONES IP

	•Por un lado, la función inet_addr() convierte una dirección IP en un entero largo
	sin signo (unsigned long int), por ejemplo:

*/
	(...)
	dest.sin_addr.s_addr = inet_addr("195.65.36.12");
	(...)
/*	
	[*]Recordar que esto sería así, siempre que tengamos una estructura "dest"
	del tipo sockaddr_in


	•Por otro lado, inet_ntoa() convierte a una cadena que contiene una dirección IP en
	un entero largo. Por ejemplo:
*/
	(...)
	char *ip;
	ip=inet_ntoa(dest.sin_addr);
	printf("La dirección es: %s\n",ip);
	(...)



//ALGUNAS FUNCIONES EN EL USO DE SOCKETS


int socket(int domain,int type,int protocol);	

	/*	
		•Domain: tipo de socket, si es para conexiones internas del servidor (AF_UNIX)
			 o para conexiones a internet (AF_INET). Hay muchos más.

		•Type: el tipo de socket que queremos usar, ya sea usando TCP/IP o UDP (de Flujos o de Datagramas).
				SOCK_STREAM(flujos), SOCK_DGRAM(datagramas).

		•Protocol: se establece a 0. (Esto se hace porque se establece un sólo protocolo y no varios a la vez).


		Ej:		int sockfd = socket(AF_INET, SOCK_STREAM,0);
	*/



int bind(int fd, struct sockaddr *my_addr,int addrlen);

	/*	
		•fd: Entero que controla el valor retornado en la funcion socket, para ver si es 1 o -1. (Descriptor del Socket)

		• *my_addr: Le pasa la dirección de memoria donde esta la estructura sockaddr (la que contiene la información de socket).

		•addrlen: tamaño de la estructura 'sockaddr', es una medida de seguridad. (se suele usar sizeof(struct sockaddr)).

		Ej:  int flag =  bind(fd, (struct sockaddr*) &servidor, sizeof(sockaddr));

	*/



int listen(int fd,int backlog);

	/*	
		•fd: Entero que controla el valor retornado en la funcion socket, para ver si es 1 o -1. (Descriptor del Socket)

		•backlog: numero de conexiones que se permiten.

		Ej: int flag = listen(fd,1);

	*/




int connect(int fd, struct sockaddr *serv_addr, int addrlen);

	/*	
		•fd: Entero que controla el valor retornado en la funcion socket, para ver si es 1 o -1. (Descriptor del Socket)

		• *serv_addr: Le pasa la dirección de memoria donde esta la estructura sockaddr (contiene la ip y el puerto destino).

		•addrlen: Lo mismo que en bind().

		Ej: int flag = connect(fd,(struct sockaddr*) &cliente,sizeof(struct sockaddr))

	*/		



int accept(int fd, void *addr, int *addrlen);			

	/*	
		•fd:(Descriptor del Socket)

		• *serv_addr: Le pasa la dirección de memoria donde esta la estructura sockaddr (contiene la ip y el puerto destino).

		•addrlen: Lo mismo que en bind().

		Ej: int flag = connect(fd,(struct sockaddr*) &cliente,sizeof(struct sockaddr))

	*/		

