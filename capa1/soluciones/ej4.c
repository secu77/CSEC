/*
 *  Ejercicio 4. Capa 1.
 *  CSEC - Programación en C.
 */

#include <stdio.h>
#define NUMINT 10

// Prototipo de la Función de Reordenar.
void reordenar(int numeros[NUMINT], char option);


// Función principal del programa.
int main(int argc, char **argv){
  int numeros[NUMINT];
  char option;

  printf("Introduce 10 enteros\n\n");

  // Bucle con contador para recibir los NUMINT enteros.
  for(int i=0; i < NUMINT; i++){
    
    // Comprueba que el numero esta entre el intervalo 1-32.
    do{
      printf("Numero %d: ", i);
      fflush(stdin);
      scanf("%d", &numeros[i]);
    }while( (numeros[i] < 1) || (numeros[i] > 32) );
  }

  // Comprueba que el caracter leido sea 'a' o 'd' (Mayus o Minus).
  do{
      printf("\nAscendente o Descendente (A/D): ");
      scanf(" %c",&option);
  }while( (option != 'A') && (option != 'a') && (option != 'D') && (option != 'd') );


  // Muestra el arreglo de enteros tal y como se han introducido.
  printf("\nNO Ordenados:{");
  for (int j = 0; j < NUMINT; j++){
    printf("%d ",numeros[j]);
  }
  printf("}\n");

  // Llama a la función para reordenar el arreglo.
  reordenar(numeros, option);

  // Muestra el arreglo ordenador de Forma Ascendente o Descendente.
  printf("\nOrdenados %s:{", (option == 'A' || option == 'a' ? "Ascendentemente" : "Descendentemente"));
  for (int k = 0; k < NUMINT; k++){
    printf("%d ",numeros[k]);
  }
  printf("}\n");

  return 0;
}



/*
 *  Función que recibe un arreglo de enteros junto
 *  con una opción, y en base a dicha opción,
 *  reordena el arreglo de enteros en forma
 *  ascendente o descendente.
 */
void reordenar(int numeros[NUMINT], char option){
  int temp = 0;

  /*
   *  El Algoritmo de la Burbuja reordena el arreglo
   *  mediante comparaciones sucesivas entre el elemento
   *  actual y los posteriores. A base de iteraciones,
   *  va intercambiando los valores resultante inferiores o
   *  superiores de la comparacion principal*, a su izquierda
   *  dejando así los elementos ordenados de mayores a menores
   *  dependiendo de cómo lo elijas.
   *
   *  Referencia: http://c.conclase.net/orden/?cap=burbuja
   */
  for (int i = 1; i < NUMINT; i++){
    // Recorriendo todos los numeros posteriores al actual.
    for (int j = 0; j < NUMINT-1; j++){
      // Verificando si en forma Ascendente o Descentente
      if((option == 'A') || (option == 'a')){
        // Intercambiando los numeros, arrastrando el menor hacia la izquierda.
        if(numeros[j] > numeros[j+1]){
          temp = numeros[j];
          numeros[j] = numeros[j+1];
          numeros[j+1] = temp;
        }
      }else{
        // Intercambiando los numeros, arrastrando el mayor a la izquierda.
        if(numeros[j] < numeros[j+1]){
          temp = numeros[j];
          numeros[j] = numeros[j+1];
          numeros[j+1] = temp;
        }
      }
    }
  }





}