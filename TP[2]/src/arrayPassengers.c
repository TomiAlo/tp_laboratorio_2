/*
 * source.c
 *
 *  Created on: 7 may. 2022
 *      Author: Usuario
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arrayPassengers.h"

#define ELEMENTS 51
#define FLYCODE_MAX 10

int validacionPrecio;
int validacionTipo;
/**
 *\brief verifica que se ingresen numeros
 * @param cadena Puntero al espacio de memoria donde se verifica lo ingresado
 * @return retorna 0 si se ejecuto correctamente
 */
static int esNumerica(char* cadena);

/**
  *\brief Lee de stdin hasta que encuentra un '\n'o hasta que haya copiado en cadena
           un máximo de 'longitud 1' caracteres.
 *\param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
  *\return Retorna(EXITO) si se obtiene una cadenay-1 (ERROR) si no
*/
static int myGets(char* cadena, int longitud);

/**
 *
 * \brief transforma los caracteres obtenidos a numeros enteros
	\param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
	\return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
 */
static int getInt(int* pResultado);

/**
 * transforma los caracteres obtenidos a numeros flotantes
 * @param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * @return retorna 0 si se ejecuto correctamente la funcion
 */
static int getFloat(float* pResultado);

/**
 * se asegura de que se este ingresando un numero flotante
 * @param cadena Puntero al espacio de memoria donde se verifica lo ingresado
 * @return retorna 0 si se ejecuto correctamente
 */
static int esFlotante(char* cadena);

/**
 * actua como un scanf para numero flotante con mensaje para decirle al usuario que ingresar, un mensaje de error por si ingresa mal y un cantidad de reintentos
 * @param pResultado puntero donde se guardara lo pedido
 * @param mensaje
 * @param mensajeError
 * @param reintentos cantidad de veces que el usuario puede ingresar si cometio un error
 * @return retorna 0 si ejecuto correctamente
 */
static int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, int reintentos);


/**
 * actua como un scanf para numero entero con mensaje para decirle al usuario que ingresar, un mensaje de error por si ingresa mal y un cantidad de reintentos
 * @param pResultado puntero donde se guardara lo pedido
 * @param mensaje
 * @param mensajeError
 * @param minimo numero minimo posible
 * @param maximo numero maximo posible
 * @param reintentos cantidad de veces que el usuario puede ingresar si cometio un error
 * @return retorna 0 si ejecuto correctamente
 */
static int utn_getNumeroEntero(int* pResultado, char* mensaje, char* mensajeError,int minimo, int maximo , int reintentos);

static int myGets(char* cadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096];
	if(cadena != NULL && longitud>0)
	{
	    fflush(stdin);
	    if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
	    {
	        if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n'){
	             bufferString[strnlen(bufferString,sizeof(bufferString))-1]='\0';
			}
	        if(strnlen(bufferString,sizeof(bufferString))<=longitud){
			   strncpy(cadena, bufferString, longitud);
			   retorno=0;
			}
	    }
	}
	return retorno;
}

static int esNumerica(char* cadena)
{
	int retorno = 1;
	int i=0;

	if(cadena[0]=='-')
	{
		i=1;
	}

	for(; cadena[i] != '\0';i++)
	{

		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
	}

	return retorno;
}

static int esFlotante(char* cadena)
{
	int retorno = 1;
	int i=0;
	int contadorPuntos=0;

	if(cadena != NULL && strlen(cadena)>0){
		for(i=0; cadena[i] != '\0'; i++){
			if(i==0 && (cadena[i] == '-' || cadena[i]=='+')){
				continue;
			}
			if(cadena[i] < '0' || cadena[i] > '9'){
				if(cadena[i] < '.' && contadorPuntos == 0){
					contadorPuntos++;
				}
				else{
					retorno = 0;
					break;
				}
			}
		}
	}

	return retorno;
}

static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer)) //verifica si son numeros
	{
		retorno = 0;
		*pResultado = atoi(buffer); //los transforma
	}

	return retorno;
}

static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(myGets(buffer,sizeof(buffer))==0 && esFlotante(buffer)) //verifica si son numeros
	{
		retorno = 0;
		*pResultado = atof(buffer); //los transforma
	}

	return retorno;
}

static int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, int reintentos){
	int retorno = -1;

	float buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL){
		do{
			printf("%s",mensaje);
			getFloat(&buffer);
			if(getFloat(&buffer)==0 && (buffer >= 0)){
				*pResultado = buffer;
				retorno=0;
				break;
			}
			printf("%s", mensajeError);
			reintentos--;
		}while(reintentos>=0);
	}
	return retorno;
}

static int utn_getNumeroEntero(int* pResultado, char* mensaje, char* mensajeError,int minimo, int maximo ,int reintentos){
	int retorno = -1;

	int buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo){
		do{
			printf("%s",mensaje);
			getInt(&buffer);
			if(getInt(&buffer)==0 && (buffer >= minimo && buffer <= maximo)){
				*pResultado = buffer;
				retorno=0;
				break;
			}
			printf("%s", mensajeError);
			reintentos--;
		}while(reintentos>=0);
	}
	return retorno;
}


int initPassengers(Passenger* list, int len)
{
	int retorno=-1;
	int i;

	if(!(list==NULL && len <= 0)){

		for(i=0; i < len; i++){
			list[i].id=i;
			strcpy(list[i].name,"name");
			strcpy(list[i].lastName,"lastName");
			list[i].price=0;
			strcpy(list[i].flycode,"flycode");
			list[i].typePassenger=0;
			list[i].isEmpty=0;
		}
		retorno=0;
	}

	return retorno;
}


int addPassenger(Passenger* list, int len, int id, char name[],char
lastName[],float price,int typePassenger, char flycode[])
{
	int retorno = -1;

	if(!(list==NULL || len <= 0 || list[id].isEmpty == 1)){

		printf("ingrese nombre: ");
		myGets(list[id].name, ELEMENTS);

		if(myGets(list[id].name, ELEMENTS) != 0){
			printf("error, ingrese nombre: ");
			myGets(list[id].name, ELEMENTS);
		}

		printf("ingrese apellido: ");
		myGets(list[id].lastName, ELEMENTS);

		if(myGets(list[id].lastName, ELEMENTS) != 0){
			printf("error, ingrese apellido: ");
			myGets(list[id].lastName, ELEMENTS);
		}

		validacionPrecio=utn_getNumeroFlotante(&list[id].price,"ingrese precio: ","error ",2);

		validacionTipo=utn_getNumeroEntero(&list[id].typePassenger,"ingrese tipo de pasajero: 1-CLASE ECONOMICA O 2-EJECUTIVO O 3-PRIMERA CLASE: ","error ",0,3,2);

		printf("ingrese codigo de vuelo: ");
		myGets(list[id].flycode, FLYCODE_MAX);

		if(myGets(list[id].flycode, FLYCODE_MAX) != 0){
			printf("error, ingrese codigo de vuelo: ");
			myGets(list[id].flycode, FLYCODE_MAX);
		}

		list[id].isEmpty=1;
	}
	else if(list==NULL || len <= 0 || list[id].isEmpty == 1){
		printf("no hay espacio disponible");
		retorno=-1;
	}

	return retorno;
}

int utn_getNumero(int* pResultado,char* mensaje, int minimo, int maximo)
{
	int retorno=-1;
	int bufferInt;

		if(pResultado != NULL && mensaje != NULL && minimo <= maximo)
		{
			printf("%s", mensaje);

			if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
			}
		}
		return retorno;
}


int findPassengerById(Passenger* list, int len,int id){

	int retorno=-1;
	int buffer;
	int validacion;

	validacion=utn_getNumero(&buffer, "Que id quiere buscar? ", 0, len);
	if(validacion==0){
		if(list[buffer].isEmpty==0){
			printf("no hay pasajero registrado con ese id");
			retorno=-1;
		}
		else{
			printf("id: %d\n",list[buffer].id);
			printf("nombre: %s\n",list[buffer].name);
			printf("apellido: %s\n",list[buffer].lastName);
			printf("precio: %2.f\n",list[buffer].price);
			printf("tipo: %d\n",list[buffer].typePassenger);
			printf("codigo de vuelo: %s\n",list[buffer].flycode);

			retorno=buffer;
		}
	}

	return retorno;
}


int removePassenger(Passenger* list, int len, int id){

	int retorno=-1;
	int buffer;
	int validacion;

	validacion=utn_getNumero(&buffer, "Que id quiere eliminar? ", 0, len);
	if(validacion==0){
		if(list[buffer].isEmpty==1){
			list[buffer].isEmpty=0;
			printf("Eliminado correctamente");
			retorno=0;
		}
		else if(list[buffer].isEmpty==0){
			printf("En este id no hay registrado ningun pasajero");
			retorno=-1;
		}
	}

	return retorno;
}


int sortPassengers(Passenger* list, int len, int order){

	int retorno=-1;
	int contadorPasajeros;
	int contadorLetrasDeApellidos;

	for(contadorPasajeros=0; contadorPasajeros<len; contadorPasajeros++){
		if(list[contadorPasajeros].isEmpty!=0){
			if(order==1){
				for(contadorLetrasDeApellidos=0; contadorLetrasDeApellidos < strlen(list[contadorPasajeros].lastName);contadorLetrasDeApellidos++){
					tolower(&list[contadorPasajeros].lastName[contadorLetrasDeApellidos]);
				}
			}
		}
	}



	return retorno;
}
