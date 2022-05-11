/*
 * header.h
 *
 *  Created on: 2 may. 2022
 *      Author: Usuario
 */

#ifndef ARRAYPASSENGERS_H_
#define ARRAYPASSENGERS_H_

#define ELEMENTS 51
#define FLYCODE_MAX 10

typedef struct
{
	int id;
	char name[ELEMENTS];
	char lastName[ELEMENTS];
	float price;
	char flycode[10];
	int typePassenger;
	int statusFlight;
	int isEmpty;

}Passenger;


/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initPassengers(Passenger* list, int len);

/** \brief add in a existing list of passengers the values received as parameters
* in the first empty position
* \param list passenger*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param price float
* \param typePassenger int
* \param flycode[] char
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*/
int addPassenger(Passenger* list, int len, int id, char name[],char
lastName[],float price,int typePassenger, char flycode[], int statusFlight);


/** \brief find a Passenger by Id en returns the index position in array.
*
* \param list Passenger*
* \param len int
* \param id int
* \return Return passenger index position or (-1) if [Invalid length or
NULL pointer received or passenger not found]
*
*/
int findPassengerById(Passenger* list, int len,int id);

/**
 * @brief pide al usuario un numero y lo guarda en pResultado
 * @param pResultado puntero donde va a guardar el numero
 * @param mensaje para pedir al usuario el numero
 * @param minimo numero posible a ingresar
 * @param maximo numero posible a ingresar
 * @return 0 si se ejecuto correctamente
 */
int utn_getNumero(int* pResultado,char* mensaje, int minimo, int maximo);


/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*
*/
int removePassenger(Passenger* list, int len, int id);


/** \brief Sort the elements in the array of passengers, the argument order
indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortPassengers(Passenger* list, int len, int order);

/** \brief print the content of passengers array
*
* \param list Passenger*
* \param length int
* \return int
*
*/
int printPassenger(Passenger* list, int len);



/** \brief Sort the elements in the array of passengers, the argument order
indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortPassengersByCode(Passenger* list, int len, int order);


/**
 * carga forzada de pasajeros
 * @param list passenger*
 * @param len limite
 * @param i es a partir de donde se puede cargar un pasajero
 */
void altaForzada(Passenger* list, int len , int i);
#endif /* ARRAYPASSENGERS_H_ */
