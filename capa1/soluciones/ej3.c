/*
 *  Ejercicio 3. Capa 1.
 *  CSEC - Programación en C.
 */

#include <stdio.h>
#include <string.h>

// Declaraciones de Constantes
#define MAXUSERS 2
#define MAXLEN 20


//Prototipo de la Función Login.
int login(char user[], char users[MAXUSERS][MAXLEN],int pass, int codes[]);


// Función principal del programa.
int main(int argc, char **argv){
  char users[MAXUSERS][MAXLEN] = {"Administrador", "Invitado"};
  int codes[MAXUSERS] = {55201, 00100};
  char user[MAXLEN];
  int pass = 0;
  int cont = 5;

  do{

  printf("\nControl de Acceso");

  // Solicitando Usuario.
  printf("\nUsuario: ");
  scanf("%s",user);

  // Solicitando Codigo.
  printf("Codigo: ");
  scanf("%d", &pass);

  /*
   *  Función que verifica si el usuario y la pass
   *  introducida por el usuario existe en el arreglo
   *  de usuarios y códigos respectivamente.
   */
  if(login(user,users,pass,codes)){
    printf("[*] Access Granted!\n");
  }else{
    printf("[!] El Usuario o Codigo es incorrecto\n");
  }

  }while(cont--);

  printf("Superado el límite de intentos\n");
  
  return 0;  
}


/*
 *  Función que busca en los arreglos de usuarios y códigos,
 *  el usuario y código introducido por el usuario.
 */
int login(char user[], char users[MAXUSERS][MAXLEN],int pass, int codes[MAXUSERS]){
  int flag = 0;

  // Bucle que recorre el arreglo de usuarios.
  for(int i = 0; i < MAXUSERS; i++){
    // Strcmp compara dos cadenas constantes y retorna 0 si son iguales.
    if(strcmp(user,users[i]) == 0){
      
      // Bucle que recorre el arreglo de códigos.
      for (int j = 0; j < MAXUSERS; j++){
        if (codes[j] == pass){
          flag = 1;
        }
      }
    }
  }

  return flag;
}