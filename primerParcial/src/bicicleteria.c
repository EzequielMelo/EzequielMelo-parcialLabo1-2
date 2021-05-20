#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bicicleteria.h"
#include "funcionesGet.h"
#define COMIENZO_ID_SERVICIOS 20000
#define COMIENZO_ID_BICICLETAS 25

/*======================================= CARGAR TRABAJOS ==============================================*/

int eTrabajo_ObtenerID(int* ID)
{
	//INCREMENTA VARIABLE ESTATICA CADA VEZ QUE SE LLAMA ESTA FUNCION
	return *ID += 1;
}

int eServicio_ObtenerID(int* ID)
{
	//INCREMENTA VARIABLE ESTATICA CADA VEZ QUE SE LLAMA ESTA FUNCION
	return *ID += 1;
}

int eBicicleta_ObtenerID(int* ID)
{
	//INCREMENTA VARIABLE ESTATICA CADA VEZ QUE SE LLAMA ESTA FUNCION
	return *ID += 1;
}

void inicializarTodo(eTrabajo array[], int TAM, eServicio arrayS[], int TAMs, eBicicleta arrayB[], int TAMb)
{
	int i;
	int j;
	int x;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0 &&
		arrayS != NULL && TAMs > 0)
	{
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//SET ESTADO DE "LIBRE"
			array[i].isEmpty = LIBRE;
		}
		for (j = 0; j < TAMs; j++)
		{
			//SET ESTADO DE "LIBRE"
			arrayS[j].isEmpty = LIBRE;
		}
		for (x = 0; x < TAMb; x++)
		{
			//SET ESTADO DE "LIBRE"
			arrayB[x].isEmpty = LIBRE;
		}
	}
}

int eTrabajo_ObtenerIndexLibre(eTrabajo array[], int TAM)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array!=NULL && TAM>0)
	{
		//RECORRO TODO EL ARRAY
		for (i=0; i <TAM; i++)
		{
			//PREGUNTO POR EL ESTADO "LIBRE"
			if (array[i].isEmpty == LIBRE)
			{
				//OBTENGO EL PRIMER INDEX DEL VECTOR "LIBRE" Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

eTrabajo eTrabajo_CargarDatos(eServicio servicio[], int tamServicio, eBicicleta bicicleta[], int tamBicicleta)
{
	eTrabajo auxiliar;
	int auxiliarIdServicio;
	int auxiliarIdBicicleta;
	setbuf(stdout, NULL);
	/** CARGAR DATOS NECESARIOS PARA EL ALTA*/
	eBicicleta_MostrarTodos(bicicleta, tamBicicleta);
	getIntNumber(&auxiliarIdBicicleta, "Ingrese el id de la bicicleta que desea que sea revisada",
			"Error la bicicleta no existe", COMIENZO_ID_BICICLETAS, 99999, ATTEMPS);
	while(eBicicleta_BuscarPorID(bicicleta, tamBicicleta, auxiliarIdBicicleta)==-1)
	{
		puts("NO EXISTE ID.");
		getIntNumber(&auxiliarIdBicicleta, "Ingrese el id de la bicicleta que desea que sea revisada",
					"Error la bicicleta no existe", COMIENZO_ID_BICICLETAS, 99999, ATTEMPS); /**USAR FUNCION GET_INT DE LIBRERIA DE INPUTS*/
	}
	eServicio_MostrarTodos(servicio, tamServicio);
	getIntNumber(&auxiliarIdServicio, "Ingrese el id del servicio que desea realizar",
			"Error el servicio no existe", COMIENZO_ID_SERVICIOS, 99999, ATTEMPS);
	while(eServicio_BuscarPorID(servicio, tamServicio, auxiliarIdServicio)==-1)
	{
		puts("NO EXISTE ID.");
		getIntNumber(&auxiliarIdServicio, "Ingrese el id del servicio que desea realizar",
					"Error el servicio no existe", COMIENZO_ID_SERVICIOS, 99999, ATTEMPS); /**USAR FUNCION GET_INT DE LIBRERIA DE INPUTS*/
	}
	auxiliar.idBicicleta=auxiliarIdBicicleta;
	auxiliar.idServicio = auxiliarIdServicio;
	auxiliar.fechaTrabajo = pedirFechaTrabajo();

	/** IMPORTANTE - NO CARGAR ID NI ESTADO - SE HACE EN EL eProducto_Alta() */
	return auxiliar;
}

eFecha pedirFechaTrabajo()
{
    eFecha miFecha;
    setbuf(stdout, NULL);
    getIntNumber(&miFecha.dia, "Ingrese el dia",
			"Error el dia no existe", 1, 31, ATTEMPS);
    getIntNumber(&miFecha.mes, "Ingrese el mes",
			"Error la fecha no existe", 1, 12, ATTEMPS);
    getIntNumber(&miFecha.anio, "Ingrese el año",
			"Error año fuera de rango", 1980, 2021, ATTEMPS);

    return miFecha;
}

int eTrabajo_Alta(eTrabajo array[], int TAM, eServicio servicio[], int tamServicio, int* ID1, eBicicleta bicicleta[], int tamBicicleta, int* ID2)
{
	int rtn = 0;
	int respuesta;
	eTrabajo auxTrabajo;
	int index = eTrabajo_ObtenerIndexLibre(array, TAM);

	//SI INDEX == -1 ARRAY LLENO
	//SI INDEX != -1 TENGO EN INDEX POSICION DE ARRAY LIBRE
	if (index != -1)
	{
		//PIDO DATOS - CARGO Producto AUXILIAR
		auxTrabajo = eTrabajo_CargarDatos(servicio, tamServicio, bicicleta, tamBicicleta);
		//SETEO ID UNICO - VARIABLE AUTOINCREMENTAL
		auxTrabajo.id = eTrabajo_ObtenerID(ID1);
		//CAMBIO SU ESTADO A "OCUPADO"
		auxTrabajo.isEmpty = OCUPADO;

		getIntNumber(&respuesta,"Ingrese:\n1-SI desea cargar los datos\n2-NO desea cargar los datos",
				"Error ingrese una opcion correcta",
				1, 2, ATTEMPS);

		if(respuesta==1)
		{
		//SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		array[index] = auxTrabajo;
		rtn = 1;
		}else
		{
			rtn = 0;
		}

	}

	return rtn;
}
/*======================================= BAJA TRABAJOS ==============================================*/

int eTrabajo_Baja(eTrabajo array[], int TAM)
{
	int rtn = 0;
	int idTrabajo;
	int index;
	int flag = 0;
	int continuar=0;

	//LISTO TODOS LOS Producto
	if (eTrabajo_MostrarTodos(array, TAM))
	{
		//BANDERA EN 1 SI HAY Producto DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	//SI HAY Producto PARA DAR DE BAJA
	if (flag)
	{
		//PIDO ID A DAR DE BAJA
		getIntNumber(&idTrabajo,"Ingrese el id del producto que desea modificar",
				"Error producto fuera de rango", 0, 99999, ATTEMPS);

		//BUSCO INDEX POR ID EN ARRAY
		while (eTrabajo_BuscarPorID(array, TAM, idTrabajo) == -1)
		{
			puts("NO EXISTE ID.");
			getIntNumber(&idTrabajo,"Ingrese el id del producto que desea modificar",
					"Error producto fuera de rango", 0, 99999, ATTEMPS); /**USAR FUNCION GET_INT DE LIBRERIA DE INPUTS*/
		}

		//OBTENGO INDEX DEL ARRAY DE Producto A DAR DE BAJA
		index = eTrabajo_BuscarPorID(array, TAM, idTrabajo);

		/**PREGUNTAR SI DESEA CONTINUAR*/
		eTrabajo_MostrarUno(array[index]);
		getIntNumber(&continuar,"Ingrese:\n1-SI desea eliminar trabajo\n2-NO desea eliminar trabajo",
				"Error ingrese una opcion correcta",
				1, 2, ATTEMPS);
		if(continuar == 1)
		{
			array[index].isEmpty = BAJA;
			//RETORNO 1 SI SE DIO DE BAJA CORRECTAMENTE
			rtn = 1;
		}else
		{
			rtn = 0;
		}
	}
	return rtn;
}
/*======================================= MODIFICAR TRABAJOS ==============================================*/

int eTrabajo_BuscarPorID(eTrabajo array[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO TODO EL ARRAY
		for (i=0; i<TAM; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].id == ID && array[i].isEmpty == OCUPADO)
			{
				//SI ENCONTRE EL ID
				//DEVUELVO EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

int eServicio_BuscarPorID(eServicio array[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO TODO EL ARRAY
		for (i=0; i<TAM; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].id == ID && array[i].isEmpty == OCUPADO)
			{
				//SI ENCONTRE EL ID
				//DEVUELVO EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

int eBicicleta_BuscarPorID(eBicicleta array[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO TODO EL ARRAY
		for (i=0; i<TAM; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].id == ID && array[i].isEmpty == OCUPADO)
			{
				//SI ENCONTRE EL ID
				//DEVUELVO EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

eTrabajo eTrabajo_ModificarUno(eTrabajo trabajo)
{
	eTrabajo auxiliar = trabajo;
	/** MODIFICAR DATOS NECESARIOS PARA EL "MODIFICAR" */
	/** IMPORTANTE - MODIFICAR EL AUXILIAR QUE ES LA COPIA DEL ORIGINAL */
	//getStringChar(auxiliar.marcaBicicleta,"ingrese la nueva marca",
		//	"Error se supero el limite de caracters", LIMIT_CHARACTERS, ATTEMPS);
	getIntNumber(&auxiliar.idBicicleta,"Ingrese nueva bicicleta",
			"Error opcion invalida", COMIENZO_ID_BICICLETAS, 99999, ATTEMPS);
	getIntNumber(&auxiliar.idServicio,"Ingrese el nuevo servicio",
			"Error opcion invalida", 1, 4, ATTEMPS);
	return auxiliar;
}

int eTrabajo_Modificacion(eTrabajo array[], int TAM)
{
	eTrabajo auxiliar;
	int rtn = 0;
	int idTrabajo;
	int index=0;
	int flag = 0;
	int continuar;

	//LISTO TODOS LOS Producto
	if(eTrabajo_MostrarTodos(array, TAM))
	{
		//BANDERA EN 1 SI HAY Producto DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	//SI HAY Producto PARA MODIFICAR
	if(flag)
	{
		//PIDO ID A MODIFICAR
		getIntNumber(&idTrabajo,"Ingrese el id del producto que desea modificar",
				"Error producto fuera de rango", 0, 99999, ATTEMPS);

		//BUSCO INDEX POR ID EN ARRAY
		while(eTrabajo_BuscarPorID(array, TAM, idTrabajo) == -1)
		{
			puts("NO EXISTE ID.");
			getIntNumber(&idTrabajo,"Ingrese el id del producto que desea modificar",
					"Error producto fuera de rango", 0, 99999, ATTEMPS);
		}

		//OBTENGO INDEX DEL ARRAY DE Producto A MODIFICAR
		index = eTrabajo_BuscarPorID(array, TAM, idTrabajo);

		//LLAMO A FUNCION QUE MODIFICA Producto
		auxiliar = eTrabajo_ModificarUno(array[index]);

		/**PREGUNTAR SI DESEA CONTINUAR*/

		getIntNumber(&continuar,"Ingrese\n1-SI desea MODIFICAR\n2-NO desea MODIFICAR",
						"Error ingrese una opcion correcta", 1, 2, ATTEMPS);
		if(continuar == 1)
		{
			//MODIFICACION ACEPTADA
			array[index] = auxiliar;
			//RETORNO 1 SI SE MODIFICO CORRECTAMENTE
			rtn = 1;
		}else
		{
			rtn = 0;
		}
	}
	return rtn;
}


/*=============================== MOSTRAR TRABAJOS Y/O SERVICIOS ==================================*/

void eTrabajo_MostrarUno(eTrabajo Trabajo)
{
	//PRINTF DE UN SOLO Producto
	printf("%d %d %d %d/%d/%d\n", Trabajo.id,
									  Trabajo.idBicicleta,
									  //Trabajo.marcaBicicleta,
			                          //Trabajo.rodadoBicicleta,
									  Trabajo.idServicio,
									  Trabajo.fechaTrabajo.dia,
									  Trabajo.fechaTrabajo.mes,
									  Trabajo.fechaTrabajo.anio);
}

int eTrabajo_MostrarTodos(eTrabajo array[], int TAM)
{
	int i;
	int rtn = 0;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (array[i].isEmpty == OCUPADO)
			{
				//MUESTRO UN SOLO Producto
				eTrabajo_MostrarUno(array[i]);
				//CONTADOR DE Producto
				rtn+=1;
			}
		}
	}

	return rtn;
}

void eServicio_MostrarUno(eServicio Servicio)
{
	//PRINTF DE UN SOLO Servicio
	printf("%d %10s %5.2f\n", Servicio.id,
						    Servicio.descripcion,
							Servicio.precio);
}

int eServicio_MostrarTodos(eServicio array[], int TAM)
{
	int i;
	int rtn = 0;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (array[i].isEmpty == OCUPADO)
			{
				//MUESTRO UN SOLO Producto
				eServicio_MostrarUno(array[i]);
				//CONTADOR DE Servicios
				rtn+=1;
			}
		}
	}

	return rtn;
}

void eBicicleta_MostrarUno(eBicicleta Bicicleta)
{
	//PRINTF DE UN SOLO Servicio
	printf("%d %10s %5d %10s\n", Bicicleta.id, Bicicleta.marca, Bicicleta.rodado, Bicicleta.color);
}

int eBicicleta_MostrarTodos(eBicicleta array[], int TAM)
{
	int i;
	int rtn = 0;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (array[i].isEmpty == OCUPADO)
			{
				//MUESTRO UN SOLO Producto
				eBicicleta_MostrarUno(array[i]);
				//CONTADOR DE Producto
				rtn+=1;
			}
		}
	}

	return rtn;
}

int mostrarTrabajoConServicio(eTrabajo arrayTrabajo[], int TAM, eServicio arrayServicio[], int TAMServicio, eBicicleta arrayBicicleta[], int TAMBicicleta)
{
	int rtn = 0;
	int i;
	int j;
	int x;

	for(i=0; i<TAMServicio; i++)
	{
		if(arrayServicio[i].isEmpty == OCUPADO)
		{
		printf("%4d %13s $%5.2f\n",arrayServicio[i].id, arrayServicio[i].descripcion, arrayServicio[i].precio);
		}
		for(j=0; j<TAM; j++)
		{
			for(x=0; x<TAMBicicleta; x++)
			{
				if(arrayTrabajo[j].idServicio == arrayServicio[i].id && arrayTrabajo[j].isEmpty == OCUPADO && arrayTrabajo[j].idBicicleta== arrayBicicleta[x].id)
				{
					printf("%5d %s %d %s %d/%d/%d\n", arrayTrabajo[j].id,
													arrayBicicleta[x].marca,
													arrayBicicleta[x].rodado,
													arrayBicicleta[x].color,
													arrayTrabajo[j].fechaTrabajo.dia,
													arrayTrabajo[j].fechaTrabajo.mes,
													arrayTrabajo[j].fechaTrabajo.anio);
					rtn = 1;
				}
			}
		}
	}
	return rtn;
}

int serviciosPrestados(eTrabajo array[], int TAM, eServicio arrayServicio[], int TAMServicio)
{
	int rtn = 0;
	int idTrabajo;
	int index=0;
	int flag = 0;
	int i;
	//LISTO TODOS LOS Productos
	if(eTrabajo_MostrarTodos(array, TAM))
	{
		flag = 1;
	}

	//SI HAY Producto PARA VER
	if(flag)
	{
		//PIDO ID A VER
		getIntNumber(&idTrabajo,"Ingrese el id del trabajo que desea ver",
				"Error producto fuera de rango", 0, 99999, ATTEMPS);

		//BUSCO INDEX POR ID EN ARRAY
		while(eTrabajo_BuscarPorID(array, TAM, idTrabajo) == -1)
		{
			puts("NO EXISTE ID.");
			getIntNumber(&idTrabajo,"Ingrese el id del trabajo que desea ver",
					"Error producto fuera de rango", 0, 99999, ATTEMPS);
		}

		//OBTENGO INDEX DEL ARRAY DE Producto A VER
		index = eTrabajo_BuscarPorID(array, TAM, idTrabajo);

		//eTrabajo_MostrarUno(array[index]);

		for(i=0; i<TAMServicio; i++)
		{
			if(array[index].idServicio == arrayServicio[i].id && array[i].isEmpty == OCUPADO)
			{
			printf("%13s $%5.2f\n", arrayServicio[i].descripcion, arrayServicio[i].precio);
			eTrabajo_MostrarUno(array[index]);
			rtn=1;
			break;
			}
		}


	}
	return rtn;

}
/*======================================= ORDENAR TRABAJOS ==============================================*/

int eTrabajo_Sort(eTrabajo array[], int TAM, int criterio)
{
	int rtn = 0;
	int i;
	int j;
	eTrabajo aux;

	/** EJEMPLO DE SORT CON ID DE Producto */
	/** MODIFICAR "CRITERIO DE ORDENAMIENTO" PARA OTROS CASOS DE ORDENAMIENTO */

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		switch (criterio)
		{
		case 1:
			for (i = 0; i < TAM - 1; i++)
			{
				for (j = i + 1; j < TAM; j++)
				{
					//PREGUNTO POR ESTADO "OCUPADO" DE AMBOS
					if (array[i].isEmpty == OCUPADO
							&& array[j].isEmpty == OCUPADO)
					{
						//CRITERIO DE ORDENAMIENTO
						if (array[i].idBicicleta > array[j].idBicicleta)
						{
							//INTERCAMBIO POSICIONES EN ARRAY
							aux = array[i];
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			rtn = 1;
			break;
		case 2:
			for (i = 0; i < TAM - 1; i++)
			{
				for (j = i + 1; j < TAM; j++)
				{
					//PREGUNTO POR ESTADO "OCUPADO" DE AMBOS
					if (array[i].isEmpty == OCUPADO
							&& array[j].isEmpty == OCUPADO)
					{
						//CRITERIO DE ORDENAMIENTO
						if (array[i].fechaTrabajo.anio < array[j].fechaTrabajo.anio)
						{
							//INTERCAMBIO POSICIONES EN ARRAY
							aux = array[i];
							array[i] = array[j];
							array[j] = aux;
						}
					}
				}
			}
			rtn = 1;
			break;
		default:
			//CRITERIO DE ORDENAMIENTO MAL INGRESADO
			rtn = 0;
			break;
		}
	}
	return rtn;
}
/*
int eTrabajo_Sort2(eTrabajo array[], int TAM, int criterio)
{
	int rtn = 0;
	int i;
	int j;
	eTrabajo aux;

	for

	return rtn;
}
*/
int servicioConMasTrabajos(eServicio servicios[], eTrabajo trabajos[], int tamListaS, int tamListaT)
{
	int rtn = 0;
	int i;
	int j;
	int maximoServicio;
	eAuxiliar auxiliar[tamListaS];

	for(i=0; i<tamListaS; i++)
	{
		auxiliar[i].id=servicios[i].id;
		auxiliar[i].contador = 0;
	}

	for(i=0; i<tamListaS; i++)
	{
		for(j=0; j<tamListaT; j++)
		{
			if(auxiliar[i].id == trabajos[j].idServicio)
			{
				auxiliar[i].contador++;
			}
		}
	}

	for(i=0; i<tamListaS; i++)
	{
		if(servicios[i].isEmpty==OCUPADO)
		{
			printf("%d-%d\n", auxiliar[i].id, auxiliar[i].contador);
		}
	}

	for(i=0; i<tamListaS; i++)
	{
		if(i==0 || auxiliar[i].contador>maximoServicio)
		{
			maximoServicio = auxiliar[i].contador;

		}
	}

	for(i=0; i<tamListaS; i++)
	{
		if(auxiliar[i].contador == maximoServicio)
		{
			for(j=0; j<tamListaS; j++)
			{
				if(auxiliar[i].id == servicios[j].id)
				{
					printf("Maximo servicio: %d %s\n", maximoServicio,servicios[j].descripcion);
				}
			}
		}
	}

	return rtn;
}

/*======================================= ORDENAR TRABAJOS ==============================================*/
void hardcodeoTodo(eTrabajo trabajos[], eServicio servicios[], eBicicleta bicicletas[], int* ID1, int* ID2, int* ID3)
{
	int idBicicleta[15] = {28,26,29,30,26,27,32,27,29,28,30,31,27,26,29};
	int idServicio[15] = {20001,20001,20002,20002,20003,20004,20003,20002,20001,20003,20004,20004,20004,20004,20004};
	eFecha fechaTrabajo[15]={{25,01,2006},{25,01,1998},{25,01,2009},{25,01,2003},{25,01,1998},{25,01,1998},
			{25,01,1996},{25,01,1996},{25,01,2010},{25,01,2010},{25,01,2020},{25,01,2020},{25,01,1997},{25,01,2020},{25,01,2020}};
	int i;
	for(i=0; i<15; i++)
	{
		trabajos[i].id = eTrabajo_ObtenerID(ID1);
		trabajos[i].idBicicleta = idBicicleta[i];
		trabajos[i].idServicio = idServicio[i];
		trabajos[i].fechaTrabajo = fechaTrabajo[i];
		trabajos[i].isEmpty = OCUPADO;
	}

	char descripcion[4][25] = {"LIMPIEZA","PARCHE","CENTRADO","CADENA"};
	float precio[4] = {250,300,400,350};

	int j;
	for(j=0; j<4; j++)
	{
		servicios[j].id=eServicio_ObtenerID(ID2);
		strcpy(servicios[j].descripcion,descripcion[j]);
		servicios[j].precio=precio[j];
		servicios[j].isEmpty= OCUPADO;
	}


	char marcaBicicleta[7][25] = {"VAIRO","VENZO","MEGA","TRINX","CANYON","BMC","ORBEA"};
	int rodadoBicicleta[7] = {28,26,24,24,20,16,15};
	char colorBicicleta[7][25] = {"ROJO","BLANCO","AZUL","AMARILLO","VERDE","GRIS","NEGRO"};
	int x;
	for(x=0; x<7; x++)
	{
		bicicletas[x].id=eBicicleta_ObtenerID(ID3);
		strcpy(bicicletas[x].marca,marcaBicicleta[x]);
		bicicletas[x].rodado=rodadoBicicleta[x];
		strcpy(bicicletas[x].color,colorBicicleta[x]);
		bicicletas[x].isEmpty= OCUPADO;

	}
}
