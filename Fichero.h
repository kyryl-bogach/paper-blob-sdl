#ifndef __Fichero_H__
#define __Fichero_H__

/**
   \file Fichero.h
   \brief Permite al usuario manejar fichero para guardar y leer su contenido.
   Este TDA presenta Nodos con un array de caracteres de longitud m�xima de 100 y un entero para la puntuaci�n.
   De este modo, tenemos una array de MAX Nodos que adem�s contiene la longitud actual de la misma (n)
   */

/**
    \brief TDA Fichero
 */
typedef struct FicheroRep * Fichero;

/**
  \brief Crea un fichero vac�o. El usuario debe asegurarse de hacer un FicheroLibera()
  \return El Fichero creado.
 */
Fichero FicheroCrea ();

/**
  \brief Libera el Fichero que le pasemos como par�metro.
  \param p El Fichero a liberar.
 */
void FicheroLibera(Fichero p);

/**
  \brief Lee el fichero con el "nombre.extension", controlando tambi�n subdirectorios con "/".
  \param nombreFichero El array de caracteres con el nombre del fichero.
  \return El Fichero que ha sido le�do.
 */
Fichero FicheroLeer (char *nombreFichero);

/**
  \brief Comprueba si existe en el fichero p el nombre dado y si existe, actualiza su puntuaci�n.
  \param p El Fichero en el que queremos buscar el nombre.
  \param nombre El nombre a buscar.
  \param puntuacion Si existe, entonces actualizo la puntuaci�n del fichero correspondiente con �ste entero.
  \return 1 si existe.
  \return 0 si no existe.
 */
int FicheroNombreExistente (Fichero p, char *nombre,int puntuacion);

/**
  \brief Inserta en el Fichero p un elemento[*nombre,puntuacion] y guarda todos los elementos en el archivo *nombreFichero.
  \param p El Fichero en el que vamos a insertar el Nodo[*nombre,puntuacion].
  \param nombreFichero Nombre del fichero para guardar el array de Nodos.
  \param nombre El char a insertar en el Nodo.
  \param puntuacion El entero a insertar en el Nodo.
 */
void FicheroInserta (Fichero p, char *nombreFichero, char *nombre, int puntuacion);

/**
  \brief Recorre el Fichero p en busca de la mejor puntuaci�n absoluta y lo guarda en *mejor en formato [Nombre Puntuacion]
  \param p El Fichero en el que vamos a buscar la mejor puntuaci�n.
  \param *mejor Nombre del mejor de los elementos del array de Nodos.

 */
void FicheroMejorPuntuacion (Fichero p, char *mejor);

/**
  \brief Imprime todos los elementos (tanto como su nombre como su puntuaci�n) del array de Nodos del Fichero p y tambi�n el RECORD.
  \param p El Fichero a imprimir.

 */
void FicheroImprimir (Fichero p);

#endif
