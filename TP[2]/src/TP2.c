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
	int opcion;
	int respuesta;
	int i = 0;

	Passenger arrayPasajeros[PASAJEROS];

	validacionInit = initPassengers(arrayPasajeros, PASAJEROS);

	if(validacionInit==0){
		do{
			respuesta=utn_getNumero(&opcion, "\n1-cargar pasajeros. \n2-Buscar pasajero. ",0,4);
			if(respuesta == 0){
				switch(opcion){
				case 1:
						validacionAgregado=addPassenger(arrayPasajeros, PASAJEROS, arrayPasajeros[i].id, arrayPasajeros[i].name,arrayPasajeros[i].lastName,
							arrayPasajeros[i].price, arrayPasajeros[i].typePassenger, arrayPasajeros[i].flycode);
						i++;
					break;

				case 2:
						validacionBusca=findPassengerById(arrayPasajeros, PASAJEROS, arrayPasajeros[i].id);
				}
			}
		}while(opcion != 3);
	}
/*
	for(int j = 0; j<PASAJEROS;j++){
		printf("id: %d\n",arrayPasajeros[j].id);
		printf("nombre: %s\n",arrayPasajeros[j].name);
		printf("apellido: %s\n",arrayPasajeros[j].lastName);
		printf("precio: %2.f\n",arrayPasajeros[j].price);
		printf("tipo: %d\n",arrayPasajeros[j].typePassenger);
		printf("code: %s\n",arrayPasajeros[j].flycode);
	}
*/
	return EXIT_SUCCESS;
}
