#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Nave.h"


struct NaveRep
{
    Punto pos;
    double Altura;double Anchura;
};

Nave NaveCrear (double AlturaPrincipal, double AnchuraPrincipal)
{
    Nave aux=malloc(sizeof(struct NaveRep));
    Punto cuadrado=PuntoCrea(Pantalla_Anchura()/2,Pantalla_Altura()/2);
    aux->pos=cuadrado;
    aux->Altura=AlturaPrincipal;
    aux->Anchura=AnchuraPrincipal;
    return aux;
}

Punto NavePos(Nave p)
{
    return p->pos;
}

double NaveAlto (Nave p)
{
    return p->Altura;
}

double NaveLargo (Nave p)
{
    return p->Anchura;
}

void NaveLibera(Nave cuadrado)
{
    PuntoLibera(cuadrado->pos);
    free(cuadrado);
}

void NaveDibujar(Imagen i, Nave cuadrado)
{
    PuntoDibujarImagen(i,NavePos(cuadrado),NaveLargo(cuadrado),NaveAlto(cuadrado));
}

void NaveMovimiento(Nave p,double velocidadCuadrado)
{
    Punto cuadrado=NavePos(p);

    if (Pantalla_TeclaPulsada(SDL_SCANCODE_D)) PuntoMueve(cuadrado,1.0,0.0,velocidadCuadrado);
    if (Pantalla_TeclaPulsada(SDL_SCANCODE_A)) PuntoMueve(cuadrado,-1.0,0.0,velocidadCuadrado);
    if (Pantalla_TeclaPulsada(SDL_SCANCODE_S)) PuntoMueve(cuadrado,0.0,1.0,velocidadCuadrado);
    if (Pantalla_TeclaPulsada(SDL_SCANCODE_W)) PuntoMueve(cuadrado,0.0,-1.0,velocidadCuadrado);
    if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) Pantalla_Libera();
    if (PuntoX(cuadrado)<=0) PuntoAsignaX(cuadrado,0.0);
    if (PuntoX(cuadrado)>=(Pantalla_Anchura()-NaveLargo(p))) PuntoAsignaX(cuadrado,Pantalla_Anchura()-NaveLargo(p));
    if (PuntoY(cuadrado)<=0) PuntoAsignaY(cuadrado,0);
    if (PuntoY(cuadrado)>=Pantalla_Altura()-NaveAlto(p)) PuntoAsignaY(cuadrado,Pantalla_Altura()-NaveAlto(p));
}

void NaveDisparar (Nave q, Lista p,double LargoDisparo,double AltoDisparo, int *mousePulsado)
{
    double LargoCuadrado=NaveLargo(q);
    double AltoCuadrado=NaveAlto(q);
    Punto cuadrado=NavePos(q);
    double ratonX;
    double ratonY;
    Pantalla_RatonCoordenadas(&ratonX,&ratonY);
    if (Pantalla_RatonBotonPulsado(1))
    {
        if (*mousePulsado==0)
        {
            double vectorX=0.0;
            double vectorY=0.0;
            double XCentrado=PuntoX(cuadrado)+LargoCuadrado/2-LargoDisparo/2;
            double YCentrado=PuntoY(cuadrado)+AltoCuadrado/2-AltoDisparo/2;
            vectorX=ratonX-XCentrado;
            vectorY=ratonY-YCentrado;
            double div= sqrt(vectorX*vectorX+vectorY*vectorY);
            vectorX=vectorX/div;
            vectorY=vectorY/div;
            ListaInsertarInicio(p,XCentrado,YCentrado,vectorX,vectorY);
        }
        *mousePulsado=1;
    }
    else
    {
        *mousePulsado=0;
    }

}
void NaveDispararExplosivo (Nave q, Lista p,double LargoDisparo,double AltoDisparo, int *mousePulsado,double *municion)
{
    double LargoCuadrado=NaveLargo(q);
    double AltoCuadrado=NaveAlto(q);
    Punto cuadrado=NavePos(q);
    if (Pantalla_RatonBotonPulsado(3))
    {
        if (*mousePulsado==0 && *municion>=1.2)
        {
            double XCentrado=PuntoX(cuadrado)+LargoCuadrado/2-LargoDisparo/2;
            double YCentrado=PuntoY(cuadrado)+AltoCuadrado/2-AltoDisparo/2;

            ListaInsertarInicio(p,XCentrado,YCentrado,1.0,0.0);
            ListaInsertarInicio(p,XCentrado,YCentrado,-1.0,0);

            ListaInsertarInicio(p,XCentrado,YCentrado,0.0,1.0);
            ListaInsertarInicio(p,XCentrado,YCentrado,0.0,-1.0);

            ListaInsertarInicio(p,XCentrado,YCentrado,-1.0,1.0);
            ListaInsertarInicio(p,XCentrado,YCentrado,1.0,-1.0);

            ListaInsertarInicio(p,XCentrado,YCentrado,1.0,-1.0);
            ListaInsertarInicio(p,XCentrado,YCentrado,-1.0,1.0);

            ListaInsertarInicio(p,XCentrado,YCentrado,1.0,1.0);
            ListaInsertarInicio(p,XCentrado,YCentrado,-1.0,-1.0);

            if (*municion>=1.0)*municion=*municion-1;

        }
        *mousePulsado=1;
    }
    else
    {
        *mousePulsado=0;
    }
}

float MAX(float r, float g, float b)
{
    float max=r;
    if (g>max) max=g;
    if (b>max) max=b;
    return max;
}

float MIN(float r, float g, float b)
{
    float min=r;
    if (g<min) min=g;
    if (b<min) min=b;
    return min;
}

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
	float min, max, delta;
	min = MIN( r, g, b );
	max = MAX( r, g, b );
	*v = max;				// v
	delta = max - min;
	if( max != 0 )
		*s = delta / max;		// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		*s = 0;
		*h = -1;
		return;
	}
	if( r == max )
		*h = ( g - b ) / delta;		// between yellow & magenta
	else if( g == max )
		*h = 2 + ( b - r ) / delta;	// between cyan & yellow
	else
		*h = 4 + ( r - g ) / delta;	// between magenta & cyan
	*h *= 60;				// degrees
	if( *h < 0 )
		*h += 360;
}

void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}
