#ifndef __Lista_H__
#define __Lista_H__
#include "Pantalla.h"
#include "Punto.h"

/**
   \file Lista.h
   \brief Permite al usuario manejar estructura enlazadas de simple enlace como Listas.
   Este TDA presenta dos Puntos: La posici�n y la direcci�n.
   */

/**
    \brief TDA Lista
 */

typedef struct Nodo * Lista;

/**
  \brief Crea una Lista vac�a. El usuario debe asegurarse de hacer un ListaLibera()
  \return La Lista creada.
 */
Lista ListaCrea ();

/**
  \brief Vac�a la Lista que le pasemos como par�metro.
  \param p La Lista a vaciar.
 */
void ListaVaciar(Lista p);

/**
  \brief Libera la Lista que le pasemos como par�metro.
  \param p La Lista a liberar.
 */
void ListaLibera (Lista p);

/**
  \brief Inserta en el inicio de la Lista un elemento con posicion(x,y) y dir(xdir,ydir)
  \param p La Lista a insertar los valores.
  \param x La coordenada X de la posici�n.
  \param y La coordenada Y de la posici�n.
  \param xdir La coordenada X de la direcci�n.
  \param ydir La coordenada Y de la direcci�n.
 */
void ListaInsertarInicio (Lista p, double x,double y,double xdir, double ydir);

/**
  \brief Mueve los elementos de la Lista dada con una velocidad dada.
  Hay que tener en cuenta que se va a mover en funci�n de la posici�n que tenga cada elemento en cada momento y con la direcci�n multiplicada por la velocidad.
  \param p La Lista a mover.
  \param velocidad La velocidad a la que se mover� la Lista.
 */
void ListaMover (Lista p, double velocidad);

/**
  \brief Imprime todos los elementos de la Lista con una Imagen (con su correspondiente width y height).
  Adem�s, si alguno de los puntos posici�n de alg�n elemento se sale de los l�mites de la pantalla, entonces se liberar�.
  \param i Imagen con la cual se dibujar�n en pantalla los puntos posici�n de los elementos.
  \param p La Lista a imprimir.
  \param largo El largo de la Imagen.
  \param alto El alto de la Imagen.
 */
void ListaImprimirImagen (Imagen i,Lista p, double largo, double alto);

/**
  \brief Actualiza el Punto Direcci�n de los elementos en funci�n de un Punto dado.
  Dicha direcci�n se calcula con el vector unitario del vector entre el punto y los elementos de la Lista.
  \param p La Lista a actualizar.
  \param cuadrado Punto de referencia para actualizar el punto direcci�n de los elementos.
 */
void ListaActualizarMovimiento (Lista p, Punto cuadrado);

/**
  \brief Comprueba las colisiones entre dos Listas.
  Para ello comprueba seg�n la altura y anchura de cada elemento la colisi�n entre dos rect�ngulos.
  Si colisionan entonces se libera el elemento de la Lista q.
  \param p La Lista a comprobar colisiones.
  \param q La segunda Lista a comprobar colisiones con la primera.
  \param plargo La longitud de los elementos de la primera Lista.
  \param palto La altura de los elementos de la primera Lista.
  \param qlargo La longitud de los elementos de la segunda Lista.
  \param qalto La altura de los elementos de la segunda Lista.
  \return N�mero de colisiones entre ambas Listas.
 */
int ListaColisiones (Lista p, Lista q, double plargo, double palto, double qlargo, double qalto);

/**
  \brief Comprueba las colisiones entre una Lista y un Punto y devuelve el n�mero de �stas. Para ello comprueba seg�n la altura y anchura de cada elemento la colisi�n entre dos rect�ngulos.
  Si colisionan entonces, en funci�n del par�metro i, se incrementa o decrementa el punto *valor y se dibujar� la Imagen dada por par�metro.
  \param p La Lista a comprobar colisiones.
  \param cuadrado Punto con el que vamos a comprobar las colisiones con la Lista.
  \param plargo La longitud de los elementos de la primera Lista.
  \param palto La altura de los elementos de la primera Lista.
  \param qlargo La longitud del Punto.
  \param qalto La altura del Punto.
  \param i Valor que controla si el *valor, se incrementar� o decrementar�. SI i=0 ENTONCES *valor=*valor+1; SI_NO *valor=*valor-1;
  \param *valor El valor a modificar si existe colisi�n.
  \param img La Imagen a dibujar si existe colisi�n. (Sirve para hacer un efecto de colisi�n).
 */
void ListaColisionConPrincipal (Lista p, Punto cuadrado,double plargo, double palto, double qlargo, double qalto, int i,int *valor,Imagen img);
#endif
