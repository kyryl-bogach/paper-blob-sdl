#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Punto.h"

struct PuntoRep
{
    double x,y;
};



Punto PuntoCrea(double x, double y)
{
    Punto aux=malloc(sizeof(struct PuntoRep));
    aux->x = x;
    aux->y = y;
    return aux;
}

void PuntoLibera(Punto p)
{
    free(p);
}

double PuntoX(Punto p)
{
    return p->x;
}

double PuntoY(Punto p)
{
    return p->y;
}

void PuntoAsignaX (Punto p,double x)
{
    p->x=x;
}
void PuntoAsignaY (Punto p,double y)
{
    p->y=y;
}


void PuntoDibujarImagen(Imagen i,Punto p, double w, double h)
{
    Pantalla_DibujaImagen(i,p->x,p->y,w,h);
}

void PuntoMueve(Punto p,double x, double y, double v)
{
    p->y+=y*v;
    p->x+=x*v;
}

