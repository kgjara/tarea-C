#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "Funciones.h"
#define CantidadUsuarios 10
#define CantidadProducto 50

int main(void) { 
  //Creacion de usuario Admin
  struct Usuario admin;
  strcpy(admin.nombre,"admin");
  strcpy(admin.user,"admin");
  strcpy(admin.pswrd,"admin");
  strcpy(admin.rol,"admin");

  FILE *archivo = fopen("usuarios.txt", "a");
  if (archivo == NULL) {
      printf("Archivo vacio.\n");
      exit(EXIT_FAILURE);
  }

  // Escribir el admin en el archivo
  fprintf(archivo, "%s %s %s %s\n",admin.nombre, admin.user, admin.pswrd, admin.rol);

  fclose(archivo);
  // Agregar el usuario "Admin" al arreglo de usuarios
  usuarios[0] = admin;

//-------------  MENU  --------------------
  
  //variable que mantiene activo el ciclo do-while
  int entrada=1;
  do{
    //Ingreso y validacion de credenciales
    printf("MENU DE INGRESO\n");
    char userIngreso[40],paswrdIngreso[40],rol[10];
    printf("Usuario: ");
    scanf("%s",userIngreso);
    printf("Contraseña: ");
    scanf("%s",paswrdIngreso);
    strcpy(rol,validarUser(userIngreso,paswrdIngreso));
    //Variables usadas en los metodos de cada rol
    int opcion;
    int codigoProducto;
    char usuario[20];
    //Mostrar menu de acuerdo al rol del usuario entrante
    //Menu de Admin
    if(strcmp(rol,"admin") == 0){
        printf(">> Bienvenido Administrador <<\n");
        printf(">> Menu Administrador <<\n");
        printf("1. Crear Usuario\n2.Actualizar Usuario\n3.Salir\n");
        printf("Escoja una opcion: ");
        scanf("%d",&opcion);
        if(opcion==1){
          registrarUsuario();
        }
        else if(opcion==2){
          mostrarUsarios();
          printf("\nIngrese el usuario del Usuario a modificar:  ");
          scanf(" %s",usuario);
          updateUsuario(usuario);
        }
    }
      //Menu de bodeguero
    if(strcmp(rol,"bodeguero") == 0){
      printf(">> Bienvenido Bodeguero <<\n");
      printf(">> Menu Bodeguero <<\n");
      printf("1.Crear Producto\n2.Actualizar producto\n3.Salir\n");
      printf("Escoja una opcion: ");
      scanf("%d",&opcion);
      if(opcion==1){
        registrarProducto();
      }
      else if(opcion==2){
        //metodo que muestra todos los productos
        mostrarBodega();
        printf("\nIngrese el codigo del producto a actualizar: ");
        scanf(" %d",&codigoProducto);
        updateProducto(codigoProducto);
      }
    }
    
    //Menu de vendedor
    if(strcmp(rol,"vendedor") == 0){
      printf(">> Bienvenido Vendedor <<\n");
      printf(">> Menu de Ventas <<\n");
      printf("Mostrando productos existentes:");
      mostrarBodega();
      printf("\nIngrese el codigo del producto a vender de la lista: ");
      scanf(" %d",&codigoProducto);
      venderProducto(codigoProducto);
    }
    
    //Consulta si desea realizar otro ingreso de usuario
    int opcReiniciar;
    printf("Desea ingresar de nuevo al sistema?\n");
    printf("1.Si\n2.No\n");
    printf("Escoja una opcion(1 o 2): ");
    scanf("%d",&opcReiniciar);
    //Si dice no se cambia la variable de entrada para dar fin al ciclo do-while y finalizar el programa
    if(opcReiniciar==2){
      entrada=0;
      printf("FIN DEL PROGRAMA");
    }
    
  }while(entrada!=0);
  return 0;
}
