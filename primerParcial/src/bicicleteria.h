/*
 * bicicleteria.h
 *
 *  Created on: 13 may. 2021
 *      Author: ezequ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIBRE 0
#define OCUPADO 1
#define BAJA -1
#define LIMIT_CHARACTERS 25
#define ATTEMPS 2

#ifndef BICICLETERIA_H_
#define BICICLETERIA_H_

typedef struct
{
	int id;
	int contador;

}eAuxiliar;

typedef struct
{
	int id;
	char descripcion[LIMIT_CHARACTERS];
	float precio;
	int isEmpty;
}eServicio;

typedef struct
{
    int dia;
    int mes;
    int anio;
}eFecha;

typedef struct
{
    int id;
    char marca[LIMIT_CHARACTERS];
    int rodado;
    char color[LIMIT_CHARACTERS];
    int isEmpty;
}eBicicleta;

typedef struct
{
	int id;
	int idBicicleta;
	int idServicio;
	eFecha fechaTrabajo;
	int isEmpty;
}eTrabajo;

/*FUNCIONES GET*/
int utn_myGets(char*, int);
int utn_getEntero(int*, char*, char*, int, int, int);
int utn_getFlotante(float*, char*, char*, float, float, int);
int utn_getString(char*, char*, char*, int, int);

/** INICIO CABECERAS DE FUNCION*/
void inicializarTodo(eTrabajo array[], int TAM, eServicio arrayS[], int TAMs, eBicicleta arrayB[], int TAMb);
int eTrabajo_ObtenerID(int* ID);
int eTrabajo_ObtenerIndexLibre(eTrabajo array[], int TAM);
int eTrabajo_BuscarPorID(eTrabajo array[], int TAM, int ID);
int eServicio_BuscarPorID(eServicio array[], int TAM, int ID);
int eBicicleta_BuscarPorID(eBicicleta array[], int TAM, int ID);
void eTrabajo_MostrarUno(eTrabajo Producto);
int eTrabajo_MostrarTodos(eTrabajo array[], int TAM);
void eServicio_MostrarUno(eServicio Servicio);
int eServicio_MostrarTodos(eServicio array[], int TAM);
void eBicicleta_MostrarUno(eBicicleta Bicicleta);
int eBicicleta_MostrarTodos(eBicicleta array[], int TAM);
int eTrabajo_MostrarDadosDeBaja(eTrabajo array[], int TAM);
int mostrarTrabajoConServicio(eTrabajo arrayTrabajo[], int TAM, eServicio arrayServicio[], int TAMServicio, eBicicleta arrayBicicleta[], int TAMBicicleta);
int serviciosPrestados(eTrabajo array[], int TAM, eServicio arrayServicio[], int TAMServicio);

/** SORT */
//CRITERIO ->  1 = MENOR A MAYOR
//CRITERIO ->  2 = MAYOR A MENOR
int eTrabajo_Sort(eTrabajo array[], int TAM, int criterio);
int servicioConMasTrabajos(eServicio servicios[], eTrabajo trabajos[], int tamListaS, int tamListaT);

//ABM
eTrabajo eTrabajo_CargarDatos(eServicio servicio[], int tamServicio, eBicicleta bicicleta[], int tamBicicleta);
eFecha pedirFechaTrabajo();
eTrabajo eTrabajo_ModificarUno(eTrabajo trabajo);
int eTrabajo_Alta(eTrabajo array[], int TAM, eServicio servicio[], int tamServicio, int* ID1, eBicicleta bicicleta[], int tamBicicleta, int* ID2);
int eTrabajo_Baja(eTrabajo array[], int TAM);
int eTrabajo_Modificacion(eTrabajo array[], int TAM);
/** FIN CABECERAS DE FUNCION*/

void hardcodeoTodo(eTrabajo trabajos[], eServicio servicios[], eBicicleta bicicletas[], int* ID1, int* ID2, int* ID3);

#endif /* BICICLETERIA_H_ */
