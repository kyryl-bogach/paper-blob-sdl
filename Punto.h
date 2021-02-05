#ifndef __Punto_H__
#define __Punto_H__
#include "Pantalla.h"

/**
   \file Punto.h
   \brief Permite al usuario tener las facilidades de manejar las coordenadas de un punto de dos dimensiones (x,y).
   Este TDA se usa con las coordenadas como "double".
   */

/**
    \brief TDA Punto
 */

typedef struct PuntoRep * Punto;


/**
  \brief Crea un punto a partir de los parámetros y que el usuario debe asegurarse de hacer un PuntoLibera().
  \param x Anchura de la ventana en puntos.
  \param y Altura de la vantana en puntos.
  \return El Punto creado.
 */
Punto PuntoCrea(double x, double y);


/**
  \brief Libera un punto dado.
  \param p Punto a liberar.
 */
void PuntoLibera(Punto p);

/**
  \brief Devuelve en forma de double la coordenada X del punto p.
  \param p Punto del cual queremos la coordenada X.
  \return La coordenada X del punto p.
 */
double PuntoX(Punto p);

/**
  \brief Devuelve en forma de double la coordenada Y del punto p.
  \param p Punto del cual queremos la coordenada Y.
  \return La coordenada Y del punto p.
 */
double PuntoY(Punto p);

/**
  \brief Asigna el double x que pasamos como parámetro a la coordenada X del punto p.
  \param p Punto al que queremos asignar la coordenada X.
  \param x El double que queremos asignar a la coordenada X del punto p.
 */
void PuntoAsignaX (Punto p,double x);

/**
  \brief Asigna el double y que pasamos como parámetro a la coordenada Y del punto p.
  \param p Punto al que queremos asignar la coordenada Y.
  \param y El double que queremos asignar a la coordenada Y del punto p.
 */
void PuntoAsignaY (Punto p,double y);

/**
  \brief Dibuja una Imagen en la posición del punto dado con la anchura y altura dada.
  \param i Imagen a dibujar.
  \param p Coordenadas (x,y) del punto p donde se va a dibujar la Imagen.
  \param w Anchura de la Imagen.
  \param h Altura de la Imagen.
 */
void PuntoDibujarImagen(Imagen i,Punto p, double w, double h);

/**
  \brief Mueve un Punto con dirección [x,y] con una velocidad v
  \param p Punto que queremos mover.
  \param x Coordenada X de la dirección.
  \param y Coordenada Y de la dirección.
  \param v Velocidad.
 */
void PuntoMueve(Punto p,double x, double y, double v);


#endif
