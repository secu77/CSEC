/*
	Ejercicio de número aleatorio:

	 - Con un numero maximo de intentos.
	 - Número aleatorio entre el 0 y el 100.

	 -! Metodo mediante bucle "for".

    
    Diseñado e implementado por Manza_Root.

*/

#include <stdio.h> // Incluimos la libreria Standar
#include <stdlib.h> /* Esta libreria para rand(), srand() */

int main(int argc, char *argv[]){ //Creamos la funcion main

    int num, num2, opc=0;		// Creamos las variables que vamos a usar.

    printf("\n Adivinar numero");
    printf("\n 1 - Comenzar.");
    printf("\n 2 - Salir.\n");
    printf("\n Introduce una opcion:");    //Hasta aqui mostramos dos opciones en pantalla.
    scanf("%d",&opc); 		// Pedimos al usuario, que introduzca una opcion
   
    while (opc!=2){	// Creamos un bucle "While", solo funcionaraw si la variable opc es diferente a 2. Que como hemos indicado arriba es salir
   
        num = rand() % 101; //Origina aleatoriamente numeros entre 0 y 100
       
        printf("\n Introduce numero: "); //Pedimo al usuario que introduzca un numero.
        scanf("%d",&num2);


       
        for (int intentos = 1; intentos < 10; ++intentos)  //Creamos el bucle for que contendra el numero de intentos, 
         {
         	if (num < num2){	//Si el numero introducido es mayor al numero aleatorio, la consola dira que el numero es mayor
               printf("Es mayor");

            }
           	else if (num == num2)
           	{
           		printf("\n Has acertado! \n");
           		break;	//Este printf esta fuera del bucle por que significa que hemos acertado el numero y la condicion del bucle no se cumple 
           	}

           	else if (num > num2){		//Si el numero de intentos se ha completado, se lo comunica al usuario
           		printf("Es menor");
           	}

            else			// Si la primera condicion no se cumple dira que es menor
                printf("Ha perdido") ;
            	break;
                
            printf("\n Introduce numero: "); //En caso de que no hayamos acertado el numero, nos pedira que introduzcamos otro
            scanf("%d",&num2);
         }



        printf("\n 1 - Jugar de nuevo.");
        printf("\n 2 - Salir.");
        printf("\n Introduce una opcion:"); 	//Una vez adivinado el numero nos dira que volvamos a repetirlo
       
        scanf("%d",&opc);
    }
     
    //system("PAUSE"); Esto no es necesario  
    return 0;
    }
