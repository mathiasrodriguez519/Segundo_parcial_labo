/*
 ============================================================================
 Name        : segundoParcialLabo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "UTN.h"
#include "LinkedList.h"
#include "Controller.h"
#include "Servicios.h"

int main(void) {

	int opcionMenu;
	int opcionFiltrar;
	int ordenarYGuardar = 0;
	char path[TAM_DESCRIPCION];

	LinkedList* listaServicios = ll_newLinkedList();
	LinkedList* listaServiciosMinoristas = ll_newLinkedList();
	LinkedList* listaServiciosMayoristas = ll_newLinkedList();
	LinkedList* listaServiciosExportar = ll_newLinkedList();

	setbuf(stdout, NULL);

	do{
		UTN_getInt(&opcionMenu,
				"\nMenu Principal: \n"
				"  1- Cargar archivo.\n"
				"  2- Imprimir lista.\n"
				"  3- Asignar totales.\n"
				"  4- Filtrar por tipo.\n"
				"  5- Mostrar servicios.\n"
				"  6- Guardar servicios.\n"
				"  7- Salir.\n"
				"Ingrese una opcion: ",
				"\nError, ingrese una opcion valida.\n", 1, 7);

		switch(opcionMenu)
		{
			case 1:
				if(UTN_getName(path, "\nIngrese el nombre del archivo a cargar: ", "\nError. Ingrese un nombre valido.\n") == 0)
				{
					if(controller_cargarServicios(path, listaServicios) == 0)
					{
						printf("\nLos datos han sido cargados exitosamente desde el archivo.\n");
					}
					else
					{
						printf("\nError, indique el nombre de una lista valida.\n");
					}
				}
				break;

			case 2:
				if(controller_ListServicios(listaServicios) != 0)
				{
					printf("\nError, no se pudo mostrar la lista, se encuentra vacía o es invalida.\n");
				}
				break;

			case 3:
				if(controller_asignarTotal(listaServicios) == 0)
				{
					printf("\nSe han asignado los totales de los servicios correctamente.\n");
				}
				else
				{
					printf("\nError, la lista se encuentra vacia.\n");
				}
				break;

			case 4:
				UTN_getInt(&opcionFiltrar, "\nOpciones a filtrar:\n"
						"  1- Minorista.\n"
						"  2- Mayorista.\n"
						"  3- Exportar.\n"
						"Ingrese una opcion: ", "\nError, ingrese una opcion valida.\n", 1, 3);
				switch(opcionFiltrar)
				{
				case 1:
					listaServiciosMinoristas = controller_FiltrarTipo(listaServicios, opcionFiltrar);

					if(listaServiciosMinoristas != NULL)
					{
						printf("\nSe ha filtrado por Minorista correctamente.\n");

						if(controller_guardarArchivos("minoristas.csv", listaServiciosMinoristas) == 0)
						{
							printf("\nSe ha guardado con exito la lista filtrada por Minoristas correctamente.\n");
						}
						else
						{
							printf("\nError. No se pudo guardar la lista filtrada.\n");
						}
					}
					else
					{
						printf("\nError. La lista se encuentra vacia o no hay servicios de este tipo.\n");
					}
					break;

				case 2:
					listaServiciosMayoristas = controller_FiltrarTipo(listaServicios, opcionFiltrar);

					if(listaServiciosMayoristas != NULL)
					{
						printf("\nSe ha filtrado por Mayoristas correctamente.\n");

						if(controller_guardarArchivos("mayoristas.csv", listaServiciosMayoristas) == 0)
						{
							printf("\nSe ha guardado con exito la lista filtrada por Mayoristas correctamente.\n");
						}
						else
						{
							printf("\nError. No se pudo guardar la lista filtrada.\n");
						}
					}
					else
					{
						printf("\nError. La lista se encuentra vacia o no hay servicios de este tipo.\n");
					}
					break;

				case 3:
					listaServiciosExportar = controller_FiltrarTipo(listaServicios, opcionFiltrar);

					if(listaServiciosExportar != NULL)
					{
						printf("\nSe ha filtrado por Exportar correctamente.\n");

						if(controller_guardarArchivos("exportar.csv", listaServiciosExportar) == 0)
						{
							printf("\nSe ha guardado con exito la lista filtrada por Exportar correctamente.\n");
						}
						else
						{
							printf("\nError. No se pudo guardar la lista filtrada.\n");
						}
					}
					else
					{
						printf("\nError. La lista se encuentra vacia o no hay servicios de este tipo.\n");
					}
					break;
				}
				break;

			case 5:
				if(controller_mostrarServiciosOrdenadosPorDescripcion(listaServicios) == 0)
				{
					ordenarYGuardar = 1;
				}
				else
				{
					printf("\nError. La lista se encuentra vacia.\n");
				}
				break;

			case 6:
				if(ordenarYGuardar == 1)
				{
					if(controller_guardarArchivos("data.txt", listaServicios) == 0)
					{
						printf("\nEl archivo fue guardado con exito en Modo Texto.\n");
					}
				}
				else
				{
					printf("\nError. Primero debe ordenar la lista antes de guardarla.\n");
				}
				break;
			case 7:
				printf("\nSaliendo.\n");
				break;

			default:
			printf("\nError, ingrese una opcion valida.\n");

		}

	}while(opcionMenu != 7);

	return 0;
}
