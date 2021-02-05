#ifndef __Principal_H__
#define __Principal_H__

#include "Punto.h"
#include "Lista.h"
#include "Pantalla.h"

/**
   \file Nave.h
   \brief Permite al usuario tener las facilidades de manejar un personaje.
   Este TDA se usa con un punto posición y la altura y anchura de la nave.
   */

/**
    \brief TDA Nave
 */

typedef struct NaveRep * Nave;

/**
  \brief Crea una Nave a partir de su Altura y Anchura. Su posición inicial será [Pantalla_Anchura()/2,Pantalla_Altura()/2].
  \param AlturaPrincipal de la Nave.
  \param AnchuraPrincipal de la Nave.
  \return La Nave creada.
 */
Nave NaveCrear (double AlturaPrincipal, double AnchuraPrincipal);

/**
  \brief Libera una Nave.
  \param cuadrado La Nave a liberar.
 */
void NaveLibera(Nave cuadrado);

/**
  \brief Devuelve el punto posición de la Nave p.
  \param p La Nave de la cual queremos el punto.
  \return El punto de la Nave p.
 */
Punto NavePos(Nave p);

/**
  \brief Devuelve el Alto de la Nave p.
  \param p La Nave de la cual queremos el Alto.
  \return El Alto de la Nave p.
 */
double NaveAlto (Nave p);

/**
  \brief Devuelve el Largo de la Nave p.
  \param p La Nave de la cual queremos el Largo.
  \return El Largo de la Nave p.
 */
double NaveLargo (Nave p);

/**
  \brief Dibuja la Nave pasada por parámetro según la Imagen, también, pasada por parámetro. Se dibujará en la posición de la Nave.
  \param i La Imagen con la que queremos dibuajar la Nave.
  \param cuadrado La Nave a dibujar.
 */
void NaveDibujar(Imagen i, Nave cuadrado);

/**
  \brief Mueve la Nave pasada por parámetro según una velocidad, también, pasada por parámetro.
  \param p La Nave a mover.
  \param velocidadCuadrado Velocidad de movimiento de la Nave.
 */
void NaveMovimiento(Nave p,double velocidadCuadrado);

/**
  \brief Inserta elementos en la Lista p con dirección vectorial [Ratón,Posicion(Nave)]. Se construirá el vector unitario para así controlarlo posteriormente con la velocidad.
  Se toma como parámetros el Largo y Alto del disparo para cuadrar el disparo. Además, únicamente se disparará si el puntero *mousePulsado está a cero, es decir, si el ratón no está pulsado.
  Funciona como limitador para que solo puedas disparar con un click.
  \param q La Nave con la que disparamos.
  \param p La Lista a insertar las balas.
  \param LargoDisparo Largo del Disparo.
  \param AltoDisparo Alto del Disparo.
  \param *mousePulsado Puntero al "trigger" del disparo.
 */
void NaveDisparar (Nave q, Lista p,double LargoDisparo,double AltoDisparo, int *mousePulsado);

/**
  \brief Inserta elementos en la Lista p con dirreción vectorial [Ratón,Posicion(Nave)].En este caso, se insertan varios disparos en forma de cruz. Se construirá el vector unitario para así controlarlo posteriormente con la velocidad.
  Se toma como parámetros el Largo y Alto del disparo para cuadrar el disparo. Además, únicamente se disparará si el puntero *mousePulsado está a cero, es decir, si el ratón no está pulsado.
  Funciona como limitador para que solo puedas disparar con un click.
  \param q La Nave con la que disparamos.
  \param p La Lista a insertar las balas.
  \param LargoDisparo Largo del Disparo.
  \param AltoDisparo Alto del Disparo.
  \param *mousePulsado Puntero al "trigger" del disparo.
  \param *municion Decrementa el numero de munición en 1 si municion>=1.
 */
void NaveDispararExplosivo (Nave q, Lista p,double LargoDisparo,double AltoDisparo, int *mousePulsado,double *municion);

/**
  \brief Convierte del código RGB al HSV.
  \param r Coordenada r del código RGB.
  \param g Coordenada g del código RGB.
  \param b Coordenada b del código RGB.
  \param h Vector h del código HSV.
  \param s Vector s del código HSV.
  \param v Vector v del código HSV.
 */
void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );

/**
  \brief Convierte del código HSV al RGB.
  \param r Coordenada r del código RGB.
  \param g Coordenada g del código RGB.
  \param b Coordenada b del código RGB.
  \param h Vector h del código HSV.
  \param s Vector s del código HSV.
  \param v Vector v del código HSV.
 */
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );

#endif
