#include <stdio.h>
#include "Funciones.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define CantidadUsuarios 10
#define CantidadProducto 50

struct Producto productosBodega[CantidadProducto];
struct Usuario usuarios[CantidadUsuarios];
int indiceBodega = 0;
int indiceUsuarios = 1;

struct Producto prodVacio;
struct Usuario userVacio;




//-----------------  FUNCIONES  ----------------------

//Muestra resumidamente los productos guardados en la bodega
void mostrarBodega(){
  // for(int i=0;i<CantidadProducto;i++){
  //   if(productosBodega[i].codigo!=0){
  //     printf("- nombre: %s\tprecio: %f\tcodigo:%d\n", productosBodega[i].nombre,productosBodega[i].precio,
  // productosBodega[i].codigo);
  //   }
  // }
  FILE *archivo = fopen("productos.txt", "r");
  if (archivo == NULL) {
      printf("Error al abrir el archivo.\n");
      exit(EXIT_FAILURE);
  }

  printf("\nProductos registrados:\n");
  struct Producto p;

  while (fscanf(archivo, "%d %d %s %s %s %f", &p.codigo, &p.bodega, p.nombre, p.marca, p.categoria, &p.precio) == 6) {
      printf("Nombre: %s, Codigo: %d, Precio: %f\n", p.nombre, p.codigo, p.precio);
  }

  fclose(archivo);
};

//Añade el producto al array y suma uno al ind de bodega
void sumarBodega(struct Producto p){
  for(int i=0;i<CantidadProducto;i++){
    if(productosBodega[i].codigo == prodVacio.codigo){
      productosBodega[i] = p;
      indiceBodega++;
      break;
    }
  }
  printf("Actualmente hay %d productos en la bodega\n",indiceBodega);
};

//Elimina un producto del array y resta uno en el ind de bodega
void restarBodega(struct Producto p){
  for(int i=0;i<CantidadProducto;i++){
    if(productosBodega[i].codigo == p.codigo){
      productosBodega[i] = prodVacio;
      indiceBodega--;
      break;
    }
  }
  printf("Actualmente hay %d productos en la bodega\n",indiceBodega);
};

//Añade un usuario al array y suma uno al ind de usuarios
void addUsuario(struct Usuario u){
  for(int i=0;i<CantidadUsuarios;i++){
    if(strcmp(usuarios[i].user,userVacio.user)==0){
      usuarios[i] = u;
      indiceUsuarios++;
      break;
    }
  }
  printf("Actualmente hay %d usuarios en el sistema\n",indiceUsuarios);
};

//Elimina un usuario del array y resta uno en el ind de usuarios
void deleteUsuario(struct Usuario u){
  for(int i=0;i<CantidadUsuarios;i++){
    if(strcmp(usuarios[i].user,u.user)==0){
      usuarios[i] = userVacio;
      indiceUsuarios--;
      break;
    }
  }
  printf("Actualmente hay %d usuarios en el sistema\n",indiceUsuarios);
};

//Valida las credenciales de ingreso de un usuario
char* validarUser(char usuario[40], char pswrd[40]){
  // for(int i=0;i<CantidadProducto;i++){
  //   if(strcmp(usuarios[i].user,usuario)==0 && strcmp(usuarios[i].pswrd,pswrd)==0) {
  //     printf("Ingreso Exitoso\n");
  //     return usuarios[i].rol;
  //   }
  // }
  // printf("Error de ingreso\n");
  // return "";
  FILE *archivo = fopen("usuarios.txt", "r");
  if (archivo == NULL) {
      printf("Error al abrir el archivo de usuarios.\n");
      exit(EXIT_FAILURE);
  }

  struct Usuario u;

  while (fscanf(archivo, "%s %s %s %s", u.nombre, u.user, u.pswrd, u.rol) == 4) {
      if (strcmp(u.user, usuario) == 0 && strcmp(u.pswrd, pswrd) == 0) {
          fclose(archivo);
          return u.rol;
      }
  }

  fclose(archivo);

  printf("Error al iniciar sesion\n");
  exit(EXIT_FAILURE);
};

// genera una venta validando el producto vendido por su codigo y restandolo de bodega con la funcion restarBodega
void venderProducto(int codeProducto)
{
  int i;
  for(i=0;i<CantidadProducto;i++){
    if(productosBodega[i].codigo==codeProducto){
      struct Venta v;
      printf("ingrese nombre del vendedor: ");
      scanf("%s",v.vendedor);
      printf("ingrese nombre del local: ");
      scanf(" %s",v.local);
      printf("ingrese precio del producto: ");
      fflush(stdin);
      scanf(" %f",&v.precio);
      v.fechaVenta = time(NULL);
      printf("VENTA EXITOSA\n");
      restarBodega(productosBodega[i]);

      // Abrir el archivo 
      FILE *archivo = fopen("ventas.txt", "a");
      if (archivo == NULL) {
          printf("Archivo vacio.\n");
          exit(EXIT_FAILURE);
      }

      // Escribir el nuevo producto en el archivo
      fprintf(archivo, "%s %s %s %f\n",v.vendedor, v.local, ctime(&v.fechaVenta), v.precio);

      fclose(archivo);

      printf("Venta registrada exitosamente.\n");
    }
  }
  
  

}
// actualza el producto deseaado a travez de su codigo 
void updateProducto(int codigo){
  FILE *archivo = fopen("productos.txt", "r");

  int i = 0;
  while (fscanf(archivo, "%d %d %s %s %s %f", &productosBodega[i].codigo, &productosBodega[i].bodega, productosBodega[i].nombre, productosBodega[i].marca, productosBodega[i].categoria, &productosBodega[i].precio) == 6) {
      i++;
  }
  fclose(archivo);
  int j;
  for(j=0;j<i;j++){
    if (productosBodega[j].codigo == codigo ){
      printf("ingrese nombre producto: \n");
      scanf("%s",productosBodega[j].nombre);
      printf("ingrese la categoria: \n");
      scanf(" %s",productosBodega[j].categoria);
      printf("ingrese la marca: \n");
      scanf(" %s",productosBodega[j].marca);
      printf("ingrese el precio: \n");
      scanf("%f",&productosBodega[j].precio);
      printf("ingrese la bodega 1 o 2: \n");
      scanf(" %d",&productosBodega[j].bodega);
      
      archivo = fopen("productos.txt", "w");
      if (archivo == NULL) {
          printf("error abrir archivo.\n");
          exit(EXIT_FAILURE);
      }

      for (int k = 0; k < i; k++) {
          fprintf(archivo, "%d %d %s %s %s %f\n", productosBodega[k].codigo, productosBodega[k].bodega, productosBodega[k].nombre, productosBodega[k].marca, productosBodega[k].categoria, productosBodega[k].precio);
      }

      fclose(archivo);

      printf("Producto actualizado exitosamente.\n");
      return;  
    }
  }     
}



// registra nuevos productos
void registrarProducto()
{
  if(indiceBodega<CantidadProducto){
    struct Producto p;
    printf("ingrese bodega del producto: ");
    scanf(" %d",&p.bodega);
    printf("ingrese nombre del producto: ");
    scanf("%s",p.nombre);
    printf("ingrese categoria del producto: ");
    scanf(" %s",p.categoria);
    printf("ingrese marca del producto: ");
    scanf(" %s",p.marca);
    printf("ingrese codigo del producto: ");
    scanf(" %d",&p.codigo);
    printf("ingrese precio del producto: ");
    scanf(" %f",&p.precio);
    sumarBodega(p);
    // Abrir el archivo 
    FILE *archivo = fopen("productos.txt", "a");
    if (archivo == NULL) {
        printf("Archivo vacio.\n");
        exit(EXIT_FAILURE);
    }

    // Escribir el nuevo producto en el archivo
    fprintf(archivo, "%d %d %s %s %s %f\n",p.codigo, p.bodega, p.nombre, p.marca, p.categoria, p.precio);

    fclose(archivo);

    printf("Producto registrado exitosamente.\n");
  }
  else{
    printf("La bodega esta llena.");
  }
  
};
// registra nuevos usuarios 
void registrarUsuario()
{
  struct Usuario u;  
  printf("ingrese nombre: ");
  scanf("%s",u.nombre);
  printf("ingrese usuario: ");
  scanf(" %s",u.user);
  printf("ingrese contraseña: ");
  scanf(" %s",u.pswrd);
  printf("ingrese su rol(vendedor, admin o bodeguero): ");
  scanf(" %s",u.rol);
  addUsuario(u);
  // Abrir el archivo 
  FILE *archivo = fopen("usuarios.txt", "a");
  if (archivo == NULL) {
      printf("Archivo vacio.\n");
      exit(EXIT_FAILURE);
  }

  // Escribir el nuevo usuario en el archivo
  fprintf(archivo, "%s %s %s %s\n",u.nombre, u.user, u.pswrd, u.rol);

  fclose(archivo);

  printf("Usuario registrado exitosamente.\n");
};

// actualiza usuarios ya sea su nombre usuario o contraseña
void updateUsuario(char user[40])
{  
  FILE *archivo = fopen("usuarios.txt", "r");
  
  int i = 0;
  while (fscanf(archivo, "%s %s %s %s", usuarios[i].nombre, usuarios[i].user, usuarios[i].pswrd, usuarios[i].rol) == 4) {
      i++;
  }
  fclose(archivo);
  for(int j=0;j<i;j++){
    if(strcmp(usuarios[j].user,user)==0){ 
      int opcion;
      printf("Que desea actualizar: ");
      printf("1. Nombre \n 2. Usuario \n 3. Contraseña \n");
      scanf("%d",&opcion);

      if(opcion == 1){
        printf("ingrese nombre nuevo: ");
        scanf("%s",usuarios[j].nombre);
      }
      else if(opcion == 2){
        printf("ingrese usuario nuevo: ");
        scanf("%s",usuarios[j].user);
      }
      else if(opcion == 3){
        printf("ingrese contraseña nueva: ");
        scanf("%s",usuarios[j].pswrd);
      }
      else{
        printf("Opcion incorrecta ");
      }
      
      archivo = fopen("usuarios.txt", "w");
      if (archivo == NULL) {
          printf("Error al abrir el archivo de usuarios.\n");
          exit(EXIT_FAILURE);
      }

      for (int k = 0; k < i; k++) {
          fprintf(archivo, "%s %s %s %s\n", usuarios[k].nombre, usuarios[k].user, usuarios[k].pswrd, usuarios[k].rol);
      }

      fclose(archivo);

      printf("Usuario actualizado exitosamente.\n");
      return;  
     
    } 
    
  }
  
  
};

void mostrarUsarios(){
  // for(int i=0;i<CantidadUsuarios;i++){
  //   if(usuarios[i].user[0] != 0){
  //     printf("- nombre: %s\tusuario: %s\tcontraseña:%s\trol:%s\n", usuarios[i].nombre, usuarios[i].user,
  //       usuarios[i].pswrd,usuarios[i].rol);
  //   }
  // }
  FILE *archivo = fopen("usuarios.txt", "r");
  if (archivo == NULL) {
      printf("Error al abrir el archivo de usuarios.\n");
      exit(EXIT_FAILURE);
  }

  printf("\nUsuarios registrados:\n");
  struct Usuario usuario;

  while (fscanf(archivo, "%s %s %s %s", usuario.nombre, usuario.user, usuario.pswrd, usuario.rol) == 4) {
      printf("Nombre: %s, Usuario: %s, Rol: %s\n", usuario.nombre, usuario.user, usuario.rol);
  }

  fclose(archivo);
}



