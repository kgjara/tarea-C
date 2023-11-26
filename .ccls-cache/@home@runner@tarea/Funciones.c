// Funciones.c
#include "Funciones.h"
#include <stdio.h>
#include <string.h>

#define USUARIOS_FILE "usuarios.txt"
#define PRODUCTOS_FILE "productos.txt"
#define VENTAS_FILE "ventas.txt"

void cargarUsuarios(Usuario usuarios[], int *numUsuarios) {
  FILE *archivo = fopen(USUARIOS_FILE, "r");

  if (archivo == NULL) {
    printf("No se pudo abrir el archivo de usuarios.\n");
    return;
  }

  *numUsuarios = 0;
  while (fscanf(archivo, "%s %c %s", usuarios[*numUsuarios].nombre,
                &usuarios[*numUsuarios].tipo,
                usuarios[*numUsuarios].clave) == 3) {
    (*numUsuarios)++;
  }

  fclose(archivo);
}

void guardarUsuarios(Usuario usuarios[], int numUsuarios) {
  FILE *archivo = fopen(USUARIOS_FILE, "w");

  if (archivo == NULL) {
    printf("No se pudo abrir el archivo de usuarios para guardar.\n");
    return;
  }

  for (int i = 0; i < numUsuarios; i++) {
    fprintf(archivo, "%s %c %s\n", usuarios[i].nombre, usuarios[i].tipo,
            usuarios[i].clave);
  }

  fclose(archivo);
}

void cargarProductos(Producto productos[], int *numProductos) {
  FILE *archivo = fopen(PRODUCTOS_FILE, "r");

  if (archivo == NULL) {
    printf("No se pudo abrir el archivo de productos.\n");
    return;
  }

  *numProductos = 0;
  while (
      fscanf(archivo, "%d %s %s %s %f %c %d", &productos[*numProductos].codigo,
             productos[*numProductos].nombre,
             productos[*numProductos].categoria, productos[*numProductos].marca,
             &productos[*numProductos].precioCompra,
             &productos[*numProductos].bodega,
             &productos[*numProductos].cantidad) == 7) {
    (*numProductos)++;
  }

  fclose(archivo);
}

void guardarProductos(Producto productos[], int numProductos) {
  FILE *archivo = fopen(PRODUCTOS_FILE, "w");

  if (archivo == NULL) {
    printf("No se pudo abrir el archivo de productos para guardar.\n");
    return;
  }

  for (int i = 0; i < numProductos; i++) {
    fprintf(archivo, "%d %s %s %s %.2f %c %d\n", productos[i].codigo,
            productos[i].nombre, productos[i].categoria, productos[i].marca,
            productos[i].precioCompra, productos[i].bodega,
            productos[i].cantidad);
  }

  fclose(archivo);
}

void cargarVentas(RegistroVenta ventas[], int *numVentas) {
  FILE *archivo = fopen(VENTAS_FILE, "r");

  if (archivo == NULL) {
    printf("No se pudo abrir el archivo de ventas.\n");
    return;
  }

  *numVentas = 0;
  while (fscanf(archivo, "%s %s %s %f %d", ventas[*numVentas].local,
                ventas[*numVentas].vendedor, ventas[*numVentas].fecha,
                &ventas[*numVentas].precioVenta,
                &ventas[*numVentas].cantidadVendida) == 5) {
    (*numVentas)++;
  }

  fclose(archivo);
}

void guardarVentas(RegistroVenta ventas[], int numVentas) {
  FILE *archivo = fopen(VENTAS_FILE, "w");

  if (archivo == NULL) {
    printf("No se pudo abrir el archivo de ventas para guardar.\n");
    return;
  }

  for (int i = 0; i < numVentas; i++) {
    fprintf(archivo, "%s %s %s %.2f %d\n", ventas[i].local, ventas[i].vendedor,
            ventas[i].fecha, ventas[i].precioVenta, ventas[i].cantidadVendida);
  }

  fclose(archivo);
}

void registrarProducto(Producto productos[], RegistroVenta ventas[],
                       int *numVentas, int *numProductos) {
  int codigo;
  printf("Ingrese el código del producto a vender: ");
  scanf("%d", &codigo);

  int indiceProducto = -1;
  for (int i = 0; i < *numProductos; i++) {
    if (productos[i].codigo == codigo) {
      indiceProducto = i;
      break;
    }
  }

  if (indiceProducto != -1) {
    // Se ha encontrado el producto, proceder con la venta
    printf("Ingrese el nombre del local: ");
    scanf("%s", ventas[*numVentas].local);

    printf("Ingrese el nombre del vendedor: ");
    scanf("%s", ventas[*numVentas].vendedor);

    printf("Ingrese la fecha de la venta: ");
    scanf("%s", ventas[*numVentas].fecha);

    printf("Ingrese el precio de venta: ");
    scanf("%f", &ventas[*numVentas].precioVenta);

    int cantidadVendida;
    do {
      printf("Ingrese la cantidad vendida: ");
      scanf("%d", &cantidadVendida);

      if (cantidadVendida > productos[indiceProducto].cantidad) {
        printf("Error: La cantidad vendida supera la cantidad disponible en "
               "stock.\n");
      }
    } while (cantidadVendida > productos[indiceProducto].cantidad);

    // Actualizar el stock del producto
    productos[indiceProducto].cantidad -= cantidadVendida;

    // Actualizar la cantidad vendida en la venta
    ventas[*numVentas].cantidadVendida = cantidadVendida;

    // Incrementar el número de ventas
    (*numVentas)++;

    printf("Venta registrada con éxito.\n");
  } else {
    printf("No se encontró un producto con ese código.\n");
  }
}

void venderProducto(Producto productos[], RegistroVenta ventas[],
                    int *numVentas, int *numProductos) {
  printf("Ingrese el código del producto a vender: ");
  int codigo;
  scanf("%d", &codigo);

  int indiceProducto = -1;
  for (int i = 0; i < *numProductos; i++) {
    if (productos[i].codigo == codigo) {
      indiceProducto = i;
      break;
    }
  }

  if (indiceProducto == -1) {
    printf("No se encontró un producto con ese código.\n");
    return;
  }

  printf("Ingrese la cantidad a vender: ");
  int cantidadVendida;
  scanf("%d", &cantidadVendida);

  if (cantidadVendida > productos[indiceProducto].cantidad) {
    printf("No hay suficiente cantidad en stock para realizar la venta.\n");
    return;
  }

  // Realizar la venta
  strcpy(ventas[*numVentas].local, "Local1");
  strcpy(ventas[*numVentas].vendedor, "Vendedor1");

  ventas[*numVentas].precioVenta = productos[indiceProducto].precioCompra;
  ventas[*numVentas].cantidadVendida = cantidadVendida;

  // Actualizar el stock del producto
  productos[indiceProducto].cantidad -= cantidadVendida;

  (*numVentas)++;
  printf("Venta realizada con éxito.\n");
}

void mostrarProductos(Producto productos[], int numProductos) {
  printf("\nLista de Productos:\n");
  printf("-------------------------------------------------------------\n");
  printf("| Código | Nombre            | Categoría       | Marca       | "
         "Precio   | Bodega | Cantidad |\n");
  printf("-------------------------------------------------------------\n");

  for (int i = 0; i < numProductos; i++) {
    printf("| %-6d | %-17s | %-15s | %-11s | %-8.2f | %-6c | %-8d |\n",
           productos[i].codigo, productos[i].nombre, productos[i].categoria,
           productos[i].marca, productos[i].precioCompra, productos[i].bodega,
           productos[i].cantidad);
  }

  printf("-------------------------------------------------------------\n");
}

void mostrarVentas(RegistroVenta ventas[], int numVentas) {
  printf("\nLista de Ventas:\n");
  printf("-------------------------------------------------------------\n");
  printf("| Local            | Vendedor         | Fecha            | Precio   "
         "| Cantidad |\n");
  printf("-------------------------------------------------------------\n");

  for (int i = 0; i < numVentas; i++) {
    printf("| %-17s | %-15s | %-16s | %-8.2f | %-8d |\n", ventas[i].local,
           ventas[i].vendedor, ventas[i].fecha, ventas[i].precioVenta,
           ventas[i].cantidadVendida);
  }

  printf("-------------------------------------------------------------\n");
}

// Funciones.c

// ... (código previo)

void crearUsuario(Usuario usuarios[], int *numUsuarios) {
  if (*numUsuarios < 10) {
    printf("Ingrese el nombre del nuevo usuario: ");
    scanf("%s", usuarios[*numUsuarios].nombre);

    printf("Ingrese el tipo de usuario (A/B/V): ");
    scanf(" %c", &usuarios[*numUsuarios].tipo);

    printf("Ingrese la clave del nuevo usuario: ");
    scanf("%s", usuarios[*numUsuarios].clave);

    (*numUsuarios)++;
    printf("Usuario creado con éxito.\n");
  } else {
    printf("No se pueden agregar más usuarios. Se ha alcanzado el límite.\n");
  }
}

void actualizarUsuario(Usuario usuarios[], int numUsuarios) {
  char nombreUsuario[50];
  printf("Ingrese el nombre del usuario a actualizar: ");
  scanf("%s", nombreUsuario);

  int indiceUsuario = -1;
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].nombre, nombreUsuario) == 0) {
      indiceUsuario = i;
      break;
    }
  }

  if (indiceUsuario != -1) {
    printf("Ingrese el nuevo tipo de usuario (A/B/V): ");
    scanf(" %c", &usuarios[indiceUsuario].tipo);

    printf("Ingrese la nueva clave del usuario: ");
    scanf("%s", usuarios[indiceUsuario].clave);

    printf("Usuario actualizado con éxito.\n");
  } else {
    printf("No se encontró un usuario con ese nombre.\n");
  }
}

void crearProducto(Producto productos[], int *numProductos) {
  if (*numProductos < 50) {
    printf("Ingrese el nombre del nuevo producto: ");
    scanf("%s", productos[*numProductos].nombre);

    printf("Ingrese la categoría del nuevo producto: ");
    scanf("%s", productos[*numProductos].categoria);

    printf("Ingrese la marca del nuevo producto: ");
    scanf("%s", productos[*numProductos].marca);

    printf("Ingrese el código del nuevo producto: ");
    scanf("%d", &productos[*numProductos].codigo);

    printf("Ingrese el precio de compra del nuevo producto: ");
    scanf("%f", &productos[*numProductos].precioCompra);

    printf("Ingrese la bodega del nuevo producto: ");
    scanf(" %c", &productos[*numProductos].bodega);

    printf("Ingrese la cantidad del nuevo producto: ");
    scanf("%d", &productos[*numProductos].cantidad);

    (*numProductos)++;
    printf("Producto creado con éxito.\n");
  } else {
    printf("No se pueden agregar más productos. Se ha alcanzado el límite.\n");
  }
}

void actualizarProducto(Producto productos[], int numProductos) {
  int codigo;
  printf("Ingrese el código del producto a actualizar: ");
  scanf("%d", &codigo);

  int indiceProducto = -1;
  for (int i = 0; i < numProductos; i++) {
    if (productos[i].codigo == codigo) {
      indiceProducto = i;
      break;
    }
  }

  if (indiceProducto != -1) {
    printf("Ingrese el nuevo precio de compra del producto: ");
    scanf("%f", &productos[indiceProducto].precioCompra);

    printf("Ingrese la nueva bodega del producto: ");
    scanf(" %c", &productos[indiceProducto].bodega);

    printf("Ingrese la nueva cantidad del producto: ");
    scanf("%d", &productos[indiceProducto].cantidad);

    printf("Producto actualizado con éxito.\n");
  } else {
    printf("No se encontró un producto con ese código.\n");
  }
}

void mostrarUsuarios(Usuario usuarios[], int numUsuarios) {
  printf("\nLista de Usuarios:\n");
  printf("---------------------\n");
  printf("| Nombre         | Rol |\n");
  printf("---------------------\n");

  for (int i = 0; i < numUsuarios; i++) {
    printf("| %-14s | %-3c |\n", usuarios[i].nombre, usuarios[i].tipo);
  }

  printf("---------------------\n");
}
