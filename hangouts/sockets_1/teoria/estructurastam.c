/*	

	COMPILACION Y OUTPUT DEL PROGRAMA.

$ gcc -Wall estructurastam.c -o estructurastam
$ ./estructurastam 

Sockaddr: 16 bytes y Sockaddr_in: 16 bytes
]$

*/


#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(){
	
	struct sockaddr estructura1;
	struct sockaddr_in estructura2;

	printf("\nSockaddr: %ld bytes y Sockaddr_in: %ld bytes\n", sizeof(estructura1), sizeof(estructura2));

	return 0;
}
