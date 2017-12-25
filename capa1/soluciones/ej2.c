/*
 *  Ejercicio 2. Capa 1.
 *  CSEC - Programación en C.
 */

#include <stdio.h>


// Función principal del programa.
int main(int argc, char **argv){
  
  int numdecimal = 0;
  int digit = 0;
  int numtras = 1;

  /* 
   *  Bucle do-while.
   *
   *  Se ejecuta primero lo que hay entre los corchetes
   *  del 'do', posteriormente evalua la condición del
   *  'while', y mientras sea verdadera, se ejecuta lo
   *  que hay en el bloque del 'do'.
   */
  do{
    printf("\nPor favor, introduzca un numero: ");
    scanf("%d", &numdecimal);

    /* 
     *  El operador '||' significa 'OR', es decir,
     *  o el número es menor que 0 o mayor que 64.
     *  Si una de estas dos condiciones se cumple,
     *  se evalua como "Verdadero o True".
     *  
     *  Para más información mirar al final las
     *  de verdad.
     */
  } while ( (numdecimal < 0) || (numdecimal > 64) );

  /*
   *  Al tratarse de un ejercicio típico,
   *  no he perdido tiempo en desarrollarlo,
   *  ya que esta opción es impecable,
   *  muchas gracias a Juan E. Huamani Mendoza
   *  por compartirl o en su blog:
   *  
   *  http://eracleo.blogspot.com.es/2013/05/convertir-un-numero-decimal-binario-en-c.html
   *
   *  [?]Funcionamiento:
   *  Una forma de calcular el correpondiente número binario
   *  de un número decimal, es hacer divisiones sucesivas
   *  entre dos hasta llegar al punto en el que no queda un
   *  cociente mayor 1, entonces, partiendo desde el final,
   *  se van escribiendo los restos de izquierda a derecha,
   *  formando cuando se llega hasta el principio, el
   *  número correspondiente en binario.
   *  Cada dígito binario tiene una posición, el más próximo
   *  a la derecha tiene la posición 0, y dicha posición
   *  corresponde al número al que se eleva el '2' para
   *  obtener el correspondiente número en decimal, ejemplo:
   *
   *  4 / 2 = 2 (R:0)
   *  2 / 2 = 1 (R:0)
   *  1 / 2 = 0 (R:1)
   *  [Como el Cociente es < 1 ya no se puede seguir dividiendo]
   *  
   *  Entonces tenemos de restos (0,0,1) que si le damos la vuelta
   *  es (1,0,0) = 100 que es 4 en Binario.
   *  
   *  Realizando la multiplicación del valor de la posición
   *  (que sólo puede ser 1 o 0), por 2 elevado a la posición
   *  en la que esta, haciendo un sumatorio de estos valores nos
   *  da el resultado correspondiente de nuevo en decimal.
   *
   *  Decimal: 4 que es 100 en binario.
   *   `->((2^2)*1) + ((2^1)*0) + ((2^0)*0) = 4 + 0 + 0 = 4
   */

  // Si el Número Decimal no es > 0 no es necesario seguir dividiendo.
  while(numdecimal > 0){
    // Obteniendo el Resto y dejándolo en la posición correspondiente.
    digit = digit + (numdecimal % 2) * numtras;
    // Dividiendo entre 2 para que en la siguiente iteración sea la mitad.
    numdecimal = numdecimal / 2;
    // Incrementando la posición, 1 para la primera cifra, 10 para la segunda cifra, etc.
    numtras = numtras * 10;
  }
  
  // Mostrando número final.
  printf(" `-> %d (2)\n", digit);
  
  return 0;  
}
