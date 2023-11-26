// Funciones.h
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <string.h>

typedef struct {
  int codigo;
  char nombre[50];
  char categoria[50];
  char marca[50];
  float precioCompra;
  char bodega;
  int cantidad;
} Producto;

typedef struct {
  char local[50];
  char vendedor[50];
  char fecha[20];
  float precioVenta;
  int cantidadVendida;
} RegistroVenta;

typedef struct {
  char nombre[50];
  char tipo; // 'A' para Administrador, 'B' para Bodeguero, 'V' para Vendedor
  char clave[20];
} Usuario;

void cargarUsuarios(Usuario usuarios[], int *numUsuarios);
void guardarUsuarios(Usuario usuarios[], int numUsuarios);
void cargarProductos(Producto productos[], int *numProductos);
void guardarProductos(Producto productos[], int numProductos);
void cargarVentas(RegistroVenta ventas[], int *numVentas);
void guardarVentas(RegistroVenta ventas[], int numVentas);
void registrarProducto(Producto productos[], RegistroVenta ventas[],
                       int *numVentas, int *numProductos);
void venderProducto(Producto productos[], RegistroVenta ventas[],
                    int *numVentas, int *numProductos);
void mostrarProductos(Producto productos[], int numProductos);
void mostrarVentas(RegistroVenta ventas[], int numVentas);
void mostrarUsuarios(Usuario usuarios[], int numUsuarios);
void crearUsuario(Usuario usuarios[], int *numUsuarios);
void actualizarUsuario(Usuario usuarios[], int numUsuarios);
void crearProducto(Producto productos[], int *numProductos);
void actualizarProducto(Producto productos[], int numProductos);

#endif
