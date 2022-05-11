/*s
 ============================================================================
 Name        : TP2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "arrayPassengers.h"

#define PASAJEROS 3

int main(void) {
	setbuf(stdout, NULL);

	int validacionInit;
	int validacionAgregado;
	int validacionBusca;
	int validacionRemover;
	int validacionOrdenar;
	int validacionMostrar;
	int validacionOrdenarDos;
	int opcionOrdenar;
	int id;
	int opcion;
	int respuesta;
	int i = 0;

	Passenger arrayPasajeros[PASAJEROS];

	validacionInit = initPassengers(arrayPasajeros, PASAJEROS);

	if(validacionInit==0){
		do{
			respuesta=utn_getNumero(&opcion, "\n1-cargar pasajeros. \n2-Buscar pasajero. \n3-Remover pasajero. \n4-Ordenar pasajeros por apellido. "
					"\n5-Mostrar pasajeros. \n6-Ordenar pasajeros por codigo de vuelo. \n7-Carga forzada de Pasajeros. \n8-Salir. \n",0,8);
			if(respuesta == 0){
				switch(opcion){
				case 1:
						validacionAgregado=addPassenger(arrayPasajeros, PASAJEROS, arrayPasajeros[i].id, arrayPasajeros[i].name,arrayPasajeros[i].lastName,
							arrayPasajeros[i].price, arrayPasajeros[i].typePassenger, arrayPasajeros[i].flycode, arrayPasajeros[i].statusFlight);
						i++;
					break;

				case 2:
						utn_getNumero(&id,"Que id quiere buscar: ", 0, PASAJEROS);
						validacionBusca=findPassengerById(arrayPasajeros, PASAJEROS, id);
						break;


				case 3:
						utn_getNumero(&id,"Que pasajeros quiere eliminar: ", 0, PASAJEROS);
						validacionRemover=removePassenger(arrayPasajeros, PASAJEROS, id);
						break;

				case 4:
						utn_getNumero(&opcionOrdenar,"0(ascendete) o 1(descendente): ", 0, 2);
						validacionOrdenar=sortPassengers(arrayPasajeros, PASAJEROS, opcionOrdenar);
						break;

				case 5:
						validacionMostrar=printPassenger(arrayPasajeros, PASAJEROS);
						break;


				case 6:
						utn_getNumero(&opcionOrdenar,"0(ascendete) o 1(descendente): ", 0, 1);
						validacionOrdenarDos=sortPassengersByCode(arrayPasajeros, PASAJEROS, opcionOrdenar);
						break;

				case 7:
						altaForzada(arrayPasajeros, PASAJEROS, i);
						break;

				}
			}
		}while(opcion != 8);
	}

	return EXIT_SUCCESS;
}
