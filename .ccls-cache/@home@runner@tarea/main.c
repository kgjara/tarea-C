// Main.c
#include "Funciones.h"
#include <stdio.h>
#include <string.h>

int main() {
  Producto productos[50];
  RegistroVenta ventas[50];
  Usuario usuarios[10];

  int numProductos = 0;
  int numVentas = 0;
  int numUsuarios = 0;

  // Cargar datos desde archivos al iniciar el programa
  cargarUsuarios(usuarios, &numUsuarios);
  cargarProductos(productos, &numProductos);
  cargarVentas(ventas, &numVentas);

  // Lógica del programa, interacción con el usuario, etc.
  int opcion;
  char nombreUsuario[50];
  char tipoUsuario;

  // Simulamos un inicio de sesión básico
  printf("Ingrese su nombre de usuario: ");
  scanf("%s", nombreUsuario);

  // Verificar el tipo de usuario (A: Administrador, B: Bodeguero, V: Vendedor)
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].nombre, nombreUsuario) == 0) {
      tipoUsuario = usuarios[i].tipo;
      break;
    }
  }

  do {
    printf("\n--- Menú ---\n");

    // Mostrar opciones según el tipo de usuario
    switch (tipoUsuario) {
    case 'A':
      printf("1. Crear Usuario\n");
      printf("2. Actualizar Usuario\n");
      break;
    case 'B':
      printf("1. Crear Producto\n");
      printf("2. Actualizar Producto\n");
      break;
    case 'V':
      printf("1. Registrar Venta\n");
      break;
    default:
      printf("Tipo de usuario no reconocido.\n");
      break;
    }

    printf("3. Mostrar Productos\n");
    printf("4. Mostrar Ventas\n");
    printf("5. Mostrar Usuarios\n");
    printf("0. Salir\n");

    printf("Ingrese la opción: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      if (tipoUsuario == 'A') {
        crearUsuario(usuarios, &numUsuarios);
        guardarUsuarios(usuarios, numUsuarios);
      } else if (tipoUsuario == 'B') {
        crearProducto(productos, &numProductos);
        guardarProductos(productos, numProductos);
      } else if (tipoUsuario == 'V') {
        // Lógica para registrar venta
      } else {
        printf("Opción no permitida para este tipo de usuario.\n");
      }
      break;
    case 2:
      if (tipoUsuario == 'A') {
        actualizarUsuario(usuarios, numUsuarios);
        guardarUsuarios(usuarios, numUsuarios);
      } else if (tipoUsuario == 'B') {
        actualizarProducto(productos, numProductos);
        guardarProductos(productos, numProductos);
      } else {
        printf("Opción no permitida para este tipo de usuario.\n");
      }
      break;
    case 3:
      mostrarProductos(productos, numProductos);
      break;
    case 4:
      mostrarVentas(ventas, numVentas);
      break;
    case 5:
      mostrarUsuarios(usuarios, numUsuarios);
      break;
    case 0:
      break;
    default:
      printf("Opción no válida. Intente de nuevo.\n");
    }

  } while (opcion != 0);

  // Guardar datos en archivos antes de salir del programa
  guardarUsuarios(usuarios, numUsuarios);
  guardarProductos(productos, numProductos);
  guardarVentas(ventas, numVentas);

  return 0;
}
