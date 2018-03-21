#include <stdio.h>

/*
 *  Para el tratamiento de condicionales,
 *  hemos de tener en cuenta unos aspectos
 *  relevantes:
 *
 *  A la hora de evaluar la condición
 *  se priman dos casos posibles:
 *
 *  1. Cero (se toma como FALSO).
 *  2. Distinto de Cero (se toma como Verdadero).
 *
 *  Esto es importante ya que mucha gente identifica
 *  los casos de las condiciones como 0 y 1, y no es
 *  del todo cierto, ya que un 5 sobre una condición
 *  hará saltar como VERDADERO, al igual que un -5.
 *
 *  También dejo por aquí la tabla de Verdad de los
 *  principales operadores lógicos:
 *
 *   +-------------------------------+
 *   |        TABLA DE VERDAD        |
 *   ---------------------------------
 *   |  0  |  &  |  0  |  = 0  |  F |
 *   ---------------------------------
 *   |  0  |  &  |  1  |  = 0  |  F |
 *   ---------------------------------
 *   |  1  |  &  |  0  |  = 0  |  F |
 *   ---------------------------------
 *   |  1  |  &  |  1  |  = 1  |  V |
 *   ---------------------------------
 *   |  0  |  |  |  0  |  = 0  |  F |
 *   ---------------------------------
 *   |  0  |  |  |  1  |  = 1  |  V |
 *   ---------------------------------
 *   |  1  |  |  |  0  |  = 1  |  V |
 *   ---------------------------------
 *   |  1  |  |  |  1  |  = 1  |  V |
 *   ---------------------------------
 *   |  0  |  ^  |  0  |  = 0  |  F  |
 *   ---------------------------------
 *   |  0  |  ^  |  1  |  = 1  |  V  |
 *   ---------------------------------
 *   |  1  |  ^  |  0  |  = 1  |  V  |
 *   ---------------------------------
 *   |  1  |  ^  |  1  |  = 0  |  F  |
 *   ---------------------------------
 *
 *  [*] Recordar que con `!` hacemos
 *  la negación, es decir, como un
 *  una puerta lógica `not`.
 *  Esto nos transforma los 1 en 0 y
 *  los 0 en 1. (Es decir, la inversa).
 *
 */


int main (int argc, char **argv){
	
	int n = 10;


	/* Demostrando el 0 y !0 (En la evaluación de la condición) */
	if (0) {
		printf("\nEsto no se va a ejecutar\n");
	}

	if (10) {
		printf("\nEsto Si se va a ejecutar\n");
	}

	if (-5) {
		printf("\nEsto TAMBIEN se va a ejecutar\n");
	}



	/* ¿Es la variable entera `n` mayor que 5? */
	if (n > 5) {
		printf("\nN es mayor que 5\n");
	} else {
		printf("\nN es menor (o igual) que 5\n");
	}


	/* ¿Es la variable entera `n` mayor o igual que 5? */
	if (n >= 5) {
		printf("\nN es mayor o igual que 5\n");
	} else {
		printf("\nN es menor que 5\n");
	}


	/* ¿Es la variable entera `n` mayor que 5 y menor o igual que 10? */
	if ((n > 5) && (n <= 10)) {
		printf("\nN esta entre 5 y 10 (último inclusive)\n");
	} else {
		printf("\nN no esta en el intervalo (5,10]\n");
	}


	/* Condiciones anidadas */
	if (n > 100) {
		printf("\nN es mayor que 100\n");
	} else if (n < 10) {
		printf("\nN es menor que 10\n");
	} else if ((n < 20) && (n >= 11)) {
		printf("\nN es menor que 20 y mayor o igual que 11\n");
	} else {
		printf("\nPodemos saber que N esta en el intervalo (10,100)\n");
	}


	/* 
	 *  Utilizando el operador ternario:
	 *
	 *  El operador ternario define una sentencia
	 *  condicional, es decir, actúa de la misma
	 *  forma que un `if`. La diferencia con este
	 *  es que se utiliza cuando se quiere hacer
	 *  una breve sentencia condicional.
	 *
	 *  Dicho operador precisa de 3 argumentos:
	 *    -1º: Condición a evaluar.
	 *	  -2º: Clausula en caso de Verdadero.
	 *	  -3º: Clausula en caso de Falso.
	 *
	 *	Armado quedaría de esta forma:
	 *
	 *   (condicion) ? (si verdadero) : (si falso);
	 *
	 *  Como puede verse, los delimitadores son `?` y `:`.
	 *
	 */

	int variable = 0;

	variable = (n>0) ? n : -1;

	printf("\nLa variable equivale ahora a %d\n",variable);
	printf("\nY ahora se imprime: %s\n", (n<100) ? "menor que 100": "mayor (o igual) que 100");


	/* Anidación Ternaria */
	variable = ((n>=10)||(n>=100)) ? ((n==10)^(n!=10)) ? 1 : 0 : 0;

	printf("\n¿Te esperabas este resultado? %d\n", variable);


	return 0;
}