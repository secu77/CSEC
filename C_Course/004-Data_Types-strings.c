#include <stdio.h>

int main(int argc, char *argv[])
{
	// Tamaño fijo, 11 + '\0' (que lo coloca al final por defecto) = 12.
	char message[12] = "Hello World";
	// Tamaño que calcula al declararlo.
	char message2[] = {'H','e','l','l','o',' ','W','o','r','l','d','\0'};
	char message3[] = "Hello World";
	// Utilizando un puntero a char.
	char *message4 = "Hello World";


	/*
	 *  Una cadena de carácteres, se resume
	 *  en un bloque contiguo de elementos
	 *  en memoria (en este caso de char's).
	 *
	 *   char cadena[] = "abc"; (en memoria)
	 *  +-----------------------------------+
	 *  |  Pos 0 |  Pos 1 |  Pos 2 |  Pos 3 |
	 *  +-----------------------------------+
	 *  | 0x0001 | 0x0002 | 0x0003 | 0x0004 |
	 *  +-----------------------------------+
	 *  |   a    |    b   |    c   |   \0   |   
	 *  +-----------------------------------+
	 *
	 *
	 *  El compilador reserva un bloque de
	 *  memoria suficiente para almacenar los
	 *  elementos que se han especificado como
	 *  indice, o directamente los calculados
	 *  en la declaración.
	 *
	 *  A continuación mostraremos la cadena "abc",
	 *  y como se almacena en memoria, para esto,
	 *  es necesario mostrar las direcciones de
	 *  memoria correspondientes a cada posición
	 *  de la cadena de carácteres.
	 */
	char array[4] = "abc";
	
	printf("\nImprimiendo cadena {%s}\n", array);
	printf("\nValor %c con Dirección de memoria %p",array[0],&array[0]);
	printf("\nValor %c con Dirección de memoria %p",array[1],&array[1]);
	printf("\nValor %c con Dirección de memoria %p",array[2],&array[2]);
	printf("\nValor %c con Dirección de memoria %p",array[3],&array[3]);


	/*
	 *  Con `&` tomamos la dirección de memoria del elemento (0) del array,
	 *  con el +2 sumamos 0x02 (en hexadecimal) a la posición del elemento
	 *  0 del array que teníamos, por tanto, si la posición del elemento 0
	 *  era 0x0001 (las direcciones de memoria van en hexadecimal), entonces
	 *  la operación (&array[0])+2) será igual a 0x0003. Y con `*` accedemos al
	 *  contenido de esa posición de memoria. Por tanto, al char de esa cadena.
	 *
	 *  Si no se entiende aún no os preocupeis, más adelante veremos una
	 *  explicación más detallada de memoria dinámica y punteros.
	 *
	 *  Pero me parecía adecuado dejarlo como curiosidad en este código. 
	 */
	printf("\nValor %c con Dirección de memoria %p\n", *((&array[0])+2),(&array[0])+2);


	/*
	 *  Y ahora, mostraremos la cadena completa,
	 *  como constaba inicialmente este ejercicio.
	 *  Fijaros que la cadena no cambia, que a pesar
	 *  de declararla de formas diferentes, nos arroja
	 *  el resultado buscado.
	 */
	printf("\nmessage is %s\n", message);
	printf("message2 is %s\n", message2);
	printf("message3 is %s\n", message3);
	printf("message4 is %s\n", message4);
	printf("message4 is %s\n",&message4[0]);

	printf("array position 7 is %c\n", message[6]);

	return 0;
}