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
			list[i].statusFlight=0;
			list[i].isEmpty=0;
		}
		retorno=0;
	}

	return retorno;
}


int addPassenger(Passenger* list, int len, int id, char name[],char
lastName[],float price,int typePassenger, char flycode[], int statusFlight)
{
	int retorno = -1;
	int i;
	int flagName;
	int flagLastName;
	int flagType;
	int validacionPrecio;
	int validacionTipo;
	int validacionEstado;
	char auxiliar;

	if(!(list==NULL || len <= 0 || list[id].isEmpty == 1)){

		do{
			printf("ingrese nombre: ");
			myGets(list[id].name, ELEMENTS);
			flagName=0;
			for(i=0; i<strlen(list[id].name);i++){
					if(!(isalpha(list[id].name[i]))){
						printf("error al ingresar nombre\n");
						flagName=0;
						break;
					}
					else{
						flagName=1;
					}
				}

		}while(flagName==0);


		do{
			printf("ingrese apellido: ");
			myGets(list[id].lastName, ELEMENTS);
			flagLastName=0;
			for(i=0; i<strlen(list[id].lastName);i++){
					if(!(isalpha(list[id].lastName[i]))){
						printf("error al ingresar apellido\n");
						flagLastName=0;
						break;
					}
					else{
						auxiliar=tolower(list[id].lastName[i]);
						list[id].lastName[i]=auxiliar;
						flagLastName=1;
					}
				}

		}while(flagLastName==0);

		do{
			validacionPrecio=utn_getNumeroFlotante(&list[id].price,"ingrese precio: ","error ",2);
		}while(validacionPrecio!=0);

		do{
			validacionTipo=utn_getNumeroEntero(&list[id].typePassenger,"ingrese tipo de pasajero: 1-CLASE ECONOMICA O 2-EJECUTIVO O 3-PRIMERA CLASE: ","error ",1,3,2);
		}while(validacionTipo!=0);

		do{
			printf("ingrese codigo de vuelo: ");
			myGets(list[id].flycode, FLYCODE_MAX);
			flagType=0;
			for(i=0; i<strlen(list[id].flycode);i++){
					if(!(isalpha(list[id].flycode[i]))){
						printf("error al ingresar codigo de vuelo\n");
						flagType=0;
						break;
					}
					else{
						flagType=1;
					}
				}

		}while(flagType==0);

		do{
			validacionEstado=utn_getNumeroEntero(&list[id].statusFlight,"ingrese estado de vuelo: 1-ACTIVO O 2-CANCELADO O 3-DEMORADO: ","error ",1,3,2);
		}while(validacionEstado!=0);

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

	if(list!=NULL && len>0){
		if(list[id].isEmpty==0){
			printf("no hay pasajero registrado con ese id");
			retorno=-1;
		}
		else{
			printf("id: %d\n",list[id].id);
			printf("nombre: %s\n",list[id].name);
			printf("apellido: %s\n",list[id].lastName);
			printf("precio: %2.f\n",list[id].price);
			printf("tipo: %d\n",list[id].typePassenger);
			printf("codigo de vuelo: %s\n",list[id].flycode);
			printf("estado de vuelo: %d\n",list[id].statusFlight);
			retorno=id;
		}

	}
	return retorno;
}
int removePassenger(Passenger* list, int len, int id){

	int retorno=-1;

	if(list!=NULL && len>0){

			if(list[id].isEmpty==1){
				list[id].isEmpty=0;
				printf("Eliminado correctamente");
				retorno=0;
			}
			else if(list[id].isEmpty==0){
				printf("En este id no hay registrado ningun pasajero");
				retorno=-1;
			}
		}
	return retorno;
}


int sortPassengers(Passenger* list, int len, int order){

	int retorno=-1;
	int i;
	int j;
	int k;
	char bufferChar[len][ELEMENTS];
	int bufferInt[len];
	int flag=0;

	char auxiliarLastName[len][ELEMENTS];
	int auxiliarType[len];

	if(list!=NULL && len>0){
		for(k=0; k<len; k++){
			if(list[k].isEmpty!=0){
				flag=1;
			}
			if(flag==0){
				printf("no hay pasajeros cargados para ordenar");
				return -1;
			}
		}

		for(i=0;i<len;i++){
			if(list[i].typePassenger!=0){
				strcpy(auxiliarLastName[i],list[i].lastName);
				auxiliarType[i]=list[i].typePassenger;
			}
		}
		if(flag==1){
			if(order==0){
				for(i=0; i<len; i++){
					for(j=i+1; j<len-1; j++){
						if(strcmp(auxiliarLastName[i],auxiliarLastName[j])>0){

						strcpy(bufferChar[i],auxiliarLastName[i]);
						strcpy(auxiliarLastName[i],auxiliarLastName[j]);
						strcpy(auxiliarLastName[j],bufferChar[i]);

						bufferInt[i]=auxiliarType[i];
						auxiliarType[i]=auxiliarType[j];
						auxiliarType[j]=bufferInt[i];

						}
					}
				}
				printf("\nlista de pasajeros ordenada por apellido de manera ascendente: \n");
				for(i=0;i<len;i++){
					if(list[i].typePassenger!=0){
						printf("apellido: %s, tipo de pasajero: %d\n",auxiliarLastName[i], auxiliarType[i]);
					}
				}
			}

			else if(order!=0){
				for(i=0; i<len; i++){
					for(j=i+1; j<len-1; j++){
						if(strcmp(auxiliarLastName[i],auxiliarLastName[j])<0){
							strcpy(bufferChar[i],auxiliarLastName[i]);
							strcpy(auxiliarLastName[i],auxiliarLastName[j]);
							strcpy(auxiliarLastName[j],bufferChar[i]);

							bufferInt[i]=auxiliarType[i];
							auxiliarType[i]=auxiliarType[j];
							auxiliarType[j]=bufferInt[i];

						}
					}
				}
				printf("\nlista de pasajeros ordenada por apellido de manera descendente: \n");
				for(i=0;i<len;i++){
					if(list[i].typePassenger!=0){
						printf("apellido: %s, tipo de pasajero: %d\n",auxiliarLastName[i], auxiliarType[i]);
					}
				}
			}
			retorno=0;
		}
	}

	return retorno;
}

int printPassenger(Passenger* list, int len){

	int retorno=-1;
	int i;
	int k;
	int flag;

	if(list!=NULL && len>0){


		for(k=0; k<len; k++){
			if(list[k].isEmpty!=0){
				flag=1;
			}
			if(flag==0){
				printf("no hay pasajeros cargados para mostrar");
				return -1;
			}
		}


		if(flag==1){
			for(i=0;i<len;i++){
				if(list[i].isEmpty!=0){
					printf("%d - %s - %s - %2.f - %d - %s - %d \n",list[i].id, list[i].name, list[i].lastName, list[i].price, list[i].typePassenger, list[i].flycode, list[i].statusFlight);
				}
			}
			retorno=0;
		}
	}

	return retorno;
}


int sortPassengersByCode(Passenger* list, int len, int order){

	int retorno = -1;
	char bufferChar[len][FLYCODE_MAX];
	int bufferInt[len];
	int flag;
	int k;
	int i;
	int j;
	char auxiliarCode[len][FLYCODE_MAX];
	int auxiliarStatus[len];

	if(list!=NULL && len>0){

		for(k=0; k<len; k++){
			if(list[k].isEmpty!=0){
				flag=1;
			}
			if(flag==0){
				printf("no hay pasajeros cargados para ordenar");
				return -1;
			}
		}

		for(i=0;i<len;i++){
			if(list[i].statusFlight!=0){
				strcpy(auxiliarCode[i],list[i].flycode);
				auxiliarStatus[i]=list[i].statusFlight;
				printf("%s",auxiliarCode[i]);
			}
		}

		if(flag==1){
			if(order==0){
				for(i=0; i<len; i++){
					for(j=i+1; j<len-1; j++){
						if(strcmp(auxiliarCode[i],auxiliarCode[j])>0){
							strcpy(bufferChar[i],auxiliarCode[i]);
							strcpy(auxiliarCode[i],auxiliarCode[j]);
							strcpy(auxiliarCode[j],bufferChar[i]);

							bufferInt[i]=auxiliarStatus[i];
							auxiliarStatus[i]=auxiliarStatus[j];
							auxiliarStatus[j]=bufferInt[i];
						}
					}
				}
				printf("\nlista de pasajeros ordenada por codigo de vuelo de manera ascendente: \n");
				for(i=0;i<len;i++){
					if(list[i].statusFlight!=0){
						printf("codigo de vuelo: %s, estado de vuelo: %d\n",auxiliarCode[i], auxiliarStatus[i]);
					}
				}
			}
			else if(order==1){
				for(i=0; i<len; i++){
					for(j=i+1; j<len-1; j++){
						if(strcmp(auxiliarCode[i],auxiliarCode[j])<0){
							strcpy(bufferChar[i],auxiliarCode[i]);
							strcpy(auxiliarCode[i],auxiliarCode[j]);
							strcpy(auxiliarCode[j],bufferChar[i]);

							bufferInt[i]=auxiliarStatus[i];
							auxiliarStatus[i]=auxiliarStatus[j];
							auxiliarStatus[j]=bufferInt[i];
						}
					}
				}
					printf("\nlista de pasajeros ordenada por codigo de vuelo de manera descendente: \n");
					for(i=0;i<len;i++){
						if(list[i].statusFlight!=0){
							printf("codigo de vuelo: %s, estado de vuelo: %d\n",auxiliarCode[i], auxiliarStatus[i]);
						}
					}
				}
				retorno=0;
			}

		}


	return retorno;
}

void altaForzada(Passenger* list, int len , int i){

	if(!(list==NULL && len <= 0)){

		for(;i<len;i++){
			list[i].id=i;
			strcpy(list[i].name,"tomas");
			strcpy(list[i].lastName,"alonso");
			list[i].price=12500;
			strcpy(list[i].flycode,"abc");
			list[i].typePassenger=1;
			list[i].statusFlight=1;
			list[i].isEmpty=1;
		}
	}
}

