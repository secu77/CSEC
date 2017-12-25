/*
 *  Ejercicio 5. Capa 1.
 *  CSEC - Programación en C.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXNAME 30
#define MAXTYPE 20
#define MAXPRODS 15
#define NUMPRODS 9
#define NUMTYPES 3
#define MAXUSERNAME 30


// Estructura del Producto.
struct Producto
{
  char Nombre[MAXNAME];
  char Tipo[MAXTYPE];
  float Precio;
};

// Estructura de la Tienda.
struct Tienda
{
  struct Producto prods[MAXPRODS]; 
};

// Estructura de un Cliente.
struct Cliente
{
  char Usuario[MAXUSERNAME];
  float billetera;
};


// Prototipos de Funciones. 
void rellenarTienda(struct Tienda *tienda, char articulos[NUMPRODS][MAXNAME], float precios[NUMPRODS], char tipos[NUMTYPES][MAXTYPE]);
int menu();
struct Cliente nuevocliente();
void mostrarTienda(struct Tienda *tienda, char tipos[NUMTYPES][MAXTYPE]);
void pedirProducto(struct Tienda *tienda, struct Tienda *cesta, struct Cliente *cliente, int *nprods);
int comprobarbilletera(float billetera);
int comprobarProd(struct Tienda *tienda,struct Tienda *cesta, char Prod[MAXNAME], float *billetera, int *nprods);
int meterEnCesta(struct Tienda *cesta, struct Producto prod);
void mostrarCesta(struct Tienda *cesta, int flagprods, int *nprods);



// Función principal del programa.
int main(int argc, char **argv){
  int opcion = 0, flagcli = 0, flagprods = 0, nprods = 0;

  // Creando la Tienda (estructura de tipo Tienda).
  struct Tienda tienda;
  // Creando la Cesta (estructura para almacenar los productos).
  struct Tienda cesta;
  // Creando un Cliente (estructura de Cliente).
  struct Cliente cliente;

  /*
   *  Declarando nuestro Articulos con
   *  sus respectivos tipos y precios.
   */
  char articulos[NUMPRODS][MAXNAME] = {"openssh","vncviewer","proftpd","windows","linux","android","raspberrypis","vps","IoTs"};
  float precios[NUMPRODS] = {5.4, 3.3, 4.9, 2.3, 4.1, 4.8, 3.6, 7.1, 2.5};
  char tipos[NUMTYPES][MAXTYPE] = {"Exploits","Rats","Botnets"};

  // Llenando la tienda de Productos.
  rellenarTienda(&tienda,articulos,precios,tipos);

  do{

    // Mostrando el Menu y recogiendo la opcion.
    opcion = menu();

    switch(opcion){
      case 1:
        // Creando un nuevo cliente.
        cliente = nuevocliente();

        printf("\nNuevo Cliente: %s\nBilletera %.2f XMR\n", cliente.Usuario, cliente.billetera);
        flagcli = 1;
        break;

      case 2:
        // Verificando que existe un cliente.
        if(flagcli){
          mostrarTienda(&tienda,tipos);
        }else{
          printf("[!] No existe un cliente\n");
        }
        break;

      case 3:
        // Verificando que existe un cliente.      
        if(flagcli){
          mostrarTienda(&tienda,tipos);
          // Pidiendo un producto al usuario.
          pedirProducto(&tienda,&cesta,&cliente,&nprods);
          flagprods = 1;
        }else{
          printf("[!] No existe un cliente\n");
        }
        break;

      case 4:
        // Verificando que existe un cliente.
        if(flagcli){
          // Mostrando los productos de la cesta.
          mostrarCesta(&cesta, flagprods,&nprods);
          printf("\nEstos son sus Productos adquiridos, disfrute!\n");
        }else{
          printf("[!] No existe un cliente\n");
        }  
        break;

      case 5:
        printf("\n[^]Saliendo...\n");
        break;

      default:
        printf("[!] Opción Invalida\n");
    }
  }while(opcion != 5);

  return 0;  
}



/*
 *  Función que introduce los productos
 *  en la Tienda, que se encuentra vacía.
 */
void rellenarTienda(struct Tienda *tienda, char articulos[NUMPRODS][MAXNAME], float precios[NUMPRODS], char tipos[NUMTYPES][MAXTYPE]){
  int j = 0, cont = 2;

  // Bucle que recorre los productos pasados por parámetro metiendolos en la Tienda.
  for (int i = 0; i < NUMPRODS; i++){
    strcpy(tienda->prods[i].Nombre, articulos[i]);
    strcpy(tienda->prods[i].Tipo, tipos[j]);
    tienda->prods[i].Precio = precios[i];

    // Necesario ya que tenemos 3 tipos, e iteramos sobre 9 productos distintos.
    if((cont--) == 0){
      j++;
      cont = 2;
    }
  }
}


/*
 *  Función que muestra el Menu con 
 *  las opciones, y recogiendo la 
 *  introducida por el usuario.
 */
int menu(){
  int num = 0;

  printf("\n## Tienda Tio Paco ##");
  printf("\n1.) Nuevo Cliente.\n2.) Ver Mercancía.\n3.) Comprar Artículos.\n4.) Ver Cesta.\n5.) Salir.\n");
  printf("\nSeleccione una opcion: ");
  scanf("%d",&num);

  return num;
}



/*
 *  Función que crea un nuevo cliente,
 *  con su billetera de monero y su
 *  nombre de usuario.
 */
struct Cliente nuevocliente(){
  struct Cliente nuevocli;

  // Verificando que se introduce un nombre.
  do{
    printf("\nIntroduzca un nombre: ");
    scanf("%s",nuevocli.Usuario);
  }while(strlen(nuevocli.Usuario) < 1);

  /*
   *  Con srand(), se toma la semilla
   *  mediante un valor del tiempo.
   *
   *  Con la función rand() genero un
   *  numero aleatorio, con el módulo
   *  de 20 estableceré un máximo de 20,
   *  y con el 2 que le sumamos, 
   *  establecemos el mínimo a 2,
   *  consiguiendo nuestro intervalo 2-20. 
   */
  srand(time(NULL));
  nuevocli.billetera = (rand() % 20 + 2);

  return nuevocli;
}


/*
 *  Función para mostrar los Productos de la Tienda.
 */
void mostrarTienda(struct Tienda *tienda, char tipos[NUMTYPES][MAXTYPE]){

  // Bucle que recorre cada tipo de producto.
  for (int i = 0; i < NUMTYPES; i++){
    printf("\n[%s]:",tipos[i]);
    // Bucle que extrae cada producto del tipo seleccionado.
    for (int j = 0; j < NUMPRODS; j++){
      if (strcmp(tienda->prods[j].Tipo, tipos[i]) == 0){
        printf("\n  %s %.2f XMR", tienda->prods[j].Nombre, tienda->prods[j].Precio);
      }
    }
  }

  printf("\n");
}



/*
 *  Función que solicita un producto al Usuario,
 *  comprueba la existencia de dicho producto,
 *  verifica que alcance la billetera el importe
 *  establecido, de igual forma valida que haya
 *  espacio suficiente en la Cesta, y por último,
 *  si todo esto se cumple, se añade dicho
 *  producto a la cesta.
 */
void pedirProducto(struct Tienda *tienda,struct Tienda *cesta,struct Cliente *cliente, int *nprods){
  char Prod[MAXNAME];
  int flag = 0, flagP = 0;

  do{
  
    // Comprobando el estado de la billetera.
    flag = comprobarbilletera(cliente->billetera);

    printf("\nSeleccione su producto (eof para salir): ");
    scanf("%s", Prod);

    // Verificando si el usuario finaliza la compra.
    if((strcmp(Prod,"eof") == 0) || strcmp(Prod,"EOF") == 0){
      flag = 1;
    }else{
      // Comprobando existencias y posibilidad de compra.
      flagP = comprobarProd(tienda,cesta,Prod,&cliente->billetera,nprods);

      // Validando la respuesta de la comprobación del producto.
      if(flagP == -1){
        printf("\n[!] No existe ese producto.");
      }else if(flagP == -2){
        printf("\n[!] No te alcanza el Monero para ese producto.");
      }else if(flagP == -3){
        printf("\n[!] No hay espacio en la Cesta");
      }
    }

  }while(!flag);

}


/*
 *  Función que comprueba el estado
 *  de la billetera del Cliente.
 */
int comprobarbilletera(float billetera){
  int ret = 0;

  if(billetera <= 1.0){
    ret = 1;
  }

  return ret;
}


/*
 *  Función que comprueba que la existencia de un producto
 *  deseado, y si es posible adquirirlo con el valor
 *  de Monero que hay en la billetera.
 */
int comprobarProd(struct Tienda *tienda,struct Tienda *cesta, char Prod[MAXNAME], float *billetera, int *nprods){
  int ret = 0;
  int rcesta = 0;

  for (int i = 0; i < NUMPRODS; i++){
    /*
     *  Si existe el producto deseado, se comprueba si
     *  hay suficiente Monero para comprarlo, si lo hay,
     *  se resta de la billetera y se añade a la cesta,
     *  si no, se devuelve error 2. En el caso de que no
     *  exista se devuelve error -1.
     */
    if (strcmp(tienda->prods[i].Nombre, Prod) == 0){
      
      // Comprobando si hay suficiente Monero.
      if(tienda->prods[i].Precio > *billetera){
        ret = -2;
        //break;
      }else{
        // Se procede a meter el Producto en la Cesta.
        rcesta = meterEnCesta(cesta, tienda->prods[i]);

        // Validando si no se puede meter el producto en la Cesta.
        if(rcesta == -1){
          ret = -3;
        }else{
          printf("\n[*] Producto Añadido a la Cesta!");
          *billetera = *billetera - tienda->prods[i].Precio;
          printf("\nEstado de la Billetera: %.2f\n", *billetera);
          *nprods = *nprods + rcesta;
          ret = 1;
        }
      }
    }
  }

  // Producto no encontrado.
  if(ret == 0)
    ret = -1;

  return ret;
}



/*
 *  Función que determina que la posición de la cesta
 *  que se encuentra vacía y sobre la que se introducirá
 *  el producto pasado por parámetros. En el caso, de
 *  no existir espacio, se devuelve error 1.
 */
int meterEnCesta(struct Tienda *cesta, struct Producto prod){
  int i = 0;
  int ret = 0;
  
  // Recorriendo la cesta en busca del indice al que añadir.
  for (; i < NUMPRODS; i++){
    // Si esta vacío (no len or len zero) tenemos hueco disponible.
    if(strlen(cesta->prods[i].Nombre) > 0){
      ret = 1;
      break;
    }
  }

  // Comprobando si se ha encontrado un hueco libre en la Cesta.
  if(ret){
    // Añadiendo el Producto a la Cesta.
    cesta->prods[i] = prod;
  }else{
    ret = -1;
  }

  return ret;
}


/*
 *  Función que recorre la Cesta,
 *  mostrando cada producto que 
 *  contiene, recorre hasta un 
 *  nº de Producto pasado por
 *  parámetros y obtenido anteriormente.
 */
void mostrarCesta(struct Tienda *cesta, int flagprods, int *nprods){

  printf("\n[Cesta]");
  // Validando si se han pedido productos al usuario.
  if(flagprods == 0){
    printf("\n  Vacía");
  }else{
    // Bucle que muestra cada articulo de la Cesta.
    for (int i = 0; i < *nprods; i++){
      printf("\n  Articulo %d %s de %.2f",i,cesta->prods[i].Nombre, cesta->prods[i].Precio);
    }
  }
  printf("\n");

}