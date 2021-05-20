/*
 ============================================================================
 Name        : primerParcial.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "bicicleteria.h"
#include "funcionesGet.h"
#define TAM_ESTRUCTURA 25
#define TAM_SERVICIO 10
#define TAM_BICICLETA 10
#define TAM_BICICLETAS 10
#define COMIENZO_ID_TRABAJOS 0
#define COMIENZO_ID_SERVICIOS 20000
#define COMIENZO_ID_BICICLETAS 25

int main(void)
{

	int opc = 0;
	int criterioDeOrdenamiento;
	int Trabajo_idIncremental = COMIENZO_ID_TRABAJOS;
	int Servicio_idIncremental = COMIENZO_ID_SERVICIOS;
	int Bicicleta_idIncremental = COMIENZO_ID_BICICLETAS;

	eTrabajo trabajos[TAM_ESTRUCTURA];
	eBicicleta bicicletas[TAM_BICICLETAS];
	eServicio servicios[TAM_SERVICIO];

	inicializarTodo(trabajos, TAM_ESTRUCTURA, servicios, TAM_SERVICIO, bicicletas ,TAM_BICICLETA);
	hardcodeoTodo(trabajos, servicios, bicicletas, &Trabajo_idIncremental, &Servicio_idIncremental, &Bicicleta_idIncremental);

	fflush(stdin);
	//BUCLE DE MENU
	do {
		puts("1- ALTA trabajo");
		puts("2- MODIFICAR trabajo");
		puts("3- BAJA trabajo");
		puts("4- LISTAR trabajos");
		puts("5- LISTAR servicios");
		puts("6- TOTAL en pesos por los servicios");
		puts("7- LISTAR ordenado por marca");
		puts("8- SERVICIOS con MAS TRABAJOS");
		puts("9- SERVICIOS con SUS BICICLETAS Y DATOS");
		puts("10- CANTIDAD BICICLETAS ROJAS");
		puts("0- SALIR del programa");
		getIntNumber(&opc, "Ingrese una opcion del menu:",
				"Error opcion invalida", 0, 10, ATTEMPS);
		//MENU SWITCH
		switch(opc)
		{
		case 1:
			//ALTA
			if(eTrabajo_Alta(trabajos, TAM_ESTRUCTURA, servicios, TAM_SERVICIO, &Trabajo_idIncremental, bicicletas, TAM_BICICLETA, &Bicicleta_idIncremental))
			{
				puts(" * Trabajo DADO DE ALTA EXITOSAMENTE");
			}else
			{
				puts(" * Trabajo cancelado");
			}
			break;
		case 2:
			//MODIFICACION
			if(eTrabajo_Modificacion(trabajos, TAM_ESTRUCTURA))
			{
				puts("\n * MODIFICACION DE Producto EXITOSA\n");
				eTrabajo_MostrarTodos(trabajos, TAM_ESTRUCTURA);
			}else
			{
				puts("\n * MODIFICACION DE Producto CANCELADA");
			}
			break;
		case 3:
			//BAJA
			if (eTrabajo_Baja(trabajos, TAM_ESTRUCTURA)) {
				puts("\n * BAJA DE Producto EXITOSA");
				eTrabajo_MostrarTodos(trabajos, TAM_ESTRUCTURA);
			} else {
				puts("\n * BAJA DE Producto CANCELADA O NO HAY PRODUCTOS");
			}
			break;
		case 4:
			//ORDENAR Producto
			getIntNumber(&criterioDeOrdenamiento,"Ingrese\n1-Ordenar menor a mayor\n2-Ordenar mayor a menor",
							"Error ingrese una opcion correcta", 1, 2, ATTEMPS);
			eTrabajo_Sort(trabajos, TAM_ESTRUCTURA, criterioDeOrdenamiento);
			if(eTrabajo_MostrarTodos(trabajos, TAM_ESTRUCTURA))
			{
			}else{
				puts("\n *NO HAY TRABAJOS QUE MOSTRAR");
			}
			break;
		case 5:
			puts("\n *TODOS LOS SERVICIOS DISPONIBLES:");
			if(eServicio_MostrarTodos(servicios, TAM_SERVICIO)==0)
			{
				puts("\n *NO HAY SERVICIOS QUE MOSTRAR");
			}
			break;
		case 6:
			//servicioConMasTrabajos(servicios, trabajos, TAM_SERVICIO, TAM_ESTRUCTURA);
			serviciosPrestados(trabajos, TAM_ESTRUCTURA, servicios, TAM_SERVICIO);
			break;
		case 7:

			break;
		case 8:
			servicioConMasTrabajos(servicios, trabajos, TAM_SERVICIO, TAM_ESTRUCTURA);
			break;
		case 9:
			if(mostrarTrabajoConServicio(trabajos, TAM_ESTRUCTURA, servicios, TAM_SERVICIO, bicicletas, TAM_BICICLETAS) == 0)
			{
				puts("\n *NO HAY TRABAJOS QUE MOSTRAR");
			}
			break;
		case 0:
			/** PREGUNTAR SI DESEA SALIR */
			opc = 0;
			break;
		}
	} while(opc != 0);

	puts("\n... FIN PROGRAMA");

	return 0;
}
