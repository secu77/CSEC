/******************************************************
*
*  Estructuras y algunas funciones explicadas por Secury
*  y recopiladas de la Bibliografía citada.
*
*  Ampliación y modificación en Febrero, 14 de 2018
*
*******************************************************/




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




/*	ALGUNAS CONVERSIONES	

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



  if ((rec = gethostbyname(argv[1])) == NULL)
  {
  	printf("\nError con el gethostbyname\n");
  	exit(-1);
  }

