#include <stdio.h>
#include <stdlib.h>

/*
 *	Constantes Simbólicas,
 *	Explicación:
 *
 *	#define <nombre> <texto reemplazo>
 *
 *	Digamos que simplemente, el 
 *	compilador sustituirá los
 *	nombres que encuentre en el
 *	proceso de compilación por
 *	los textos a reemplazar
 *	especificados en estas definiciones.
 *
 *	Ahora bien, ¿Y para qué vamos a
 *	utilizar esta metodología?
 *
 *	Imaginemos que hacemos un programa
 *	que tiene que recorrer un intervalo
 *	de números, desde un `Ninit` hasta un
 *	`Nend`, e imaginemos que con esos
 *	indices hacemos una serie de operaciones
 *	muy extensas. Pues... imaginemos entonces,
 *	que un día queremos cambiar ese intervalo,
 *	y en vez de ser de 2 a 10, lo queremos hacer
 *	de 2 a 10000. ¿Vas a cambiarlo a mano?
 *
 *	¡No! Tu no eres ese tipo de persona, tu eres
 *	ingeniero! Y encima programas en C, tienes
 *	que ser Inteligente!
 *
 *	Declara una constante simbólica, y así el
 *	cambio pertinente sólo lo tienes que hacer
 *	una vez y te olvidas.
 */
#define MAXFIL 2
#define MAXCOL 3

int main(int argv, char *argc[])
{
	int a[4];
	int b[4] = {54, 354, 2, 7829};

	/*
	 *	Declaramos una matriz bidimensional de 2x3:
	 *
	 *	+-------------------------------+
	 *	|	2	2	3	|
	 *	|	3	3	2	|
	 *	+-------------------------------+
	 *
	 *  Al tener las definiciones como 
	 *	MAXFIL=2 y MACOL=3, y utilizar dichas
	 *	constantes en la declaración, podemos
	 *  obtenemos una matriz bidimensional de enteros
	 */
	int c[MAXFIL][MAXCOL] = {{2,2,3},{3,3,2}};


	// Ejemplo de Matriz de 2x2x2
	int cmore[2][2][2] = { { {1,1},{2,2} },{ {1,1},{2,2} } };


	a[0] = 78;
	a[1] = 89768;
	a[2] = 379;
	a[3] = 4;

	printf("array a = %d, %d, %d, %d\n", a[0], a[1], a[2], a[3]);
	printf("array b = %d, %d, %d, %d\n", b[0], b[1], b[2], b[3]);

	/*
	 *	Al tratarse de una Matriz Bidimensional o Matriz doble,
	 *	se debe de recorrer todas las filas (en este caso utilzando
	 *	un bucle for) y posteriormente cada una de sus columnas.
	 */
	for (int i = 0; i < MAXFIL; ++i) {
		for (int j = 0; j < MAXCOL; ++j) {
			printf("Fila %d Col %d Value: %d\n", i,j,c[i][j]);
		}
	}

	/*
	 *	Iterando sobre la matriz de 2x2x2,
	 *	con la misma normalidad y facilidad,
	 *	que con cualquier otra. Ya que nos
	 *	es indifente el `nº de dimensiones`
	 *	con el que tratemos.
	 */
	printf("\n[Matriz de 2x2x2]\n");

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				printf("Fila %d Col %d Clave: %d Valor: %d\n", i,j,k,cmore[i][j][k]);
			}
		}
	}


	return 0;
}
