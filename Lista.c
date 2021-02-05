#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "Lista.h"

struct Nodo
{
    Punto pos,dir;
    struct Nodo * sig;
};

Lista ListaCrea ()
{
    Lista aux=malloc(sizeof(struct Nodo));
    aux->sig=NULL;
    return aux;
}

void ListaNodoLibera (Lista p)
{
    Lista Borrar=p->sig;
    Punto Borrar1=p->sig->pos;
    Punto Borrar2=p->sig->dir;
    p->sig=p->sig->sig;
    free(Borrar);
    PuntoLibera(Borrar1);
    PuntoLibera(Borrar2);
}


void ListaVaciar(Lista p)
{
    while (p->sig!=NULL) ListaNodoLibera(p);
}


void ListaLibera (Lista p)
{
    ListaVaciar(p);
    free(p);
}

void ListaInsertarInicio (Lista p, double x,double y,double xdir, double ydir)
{
    Lista aux=malloc(sizeof(struct Nodo));
    aux->pos=PuntoCrea(x,y);
    aux->dir=PuntoCrea(xdir,ydir);
    aux->sig=p->sig;
    p->sig=aux;
}


void ListaMover (Lista p, double velocidad)
{
    while (p->sig!=NULL)
    {
        double x=PuntoX(p->sig->pos)+(PuntoX(p->sig->dir)*velocidad);
        double y=PuntoY(p->sig->pos)+(PuntoY(p->sig->dir)*velocidad);
        PuntoAsignaX(p->sig->pos,x);
        PuntoAsignaY(p->sig->pos,y);
        p=p->sig;
    }
}


void ListaImprimirImagen (Imagen i,Lista p, double largo, double alto)
{
    while (p->sig!=NULL)
    {
        if (PuntoY(p->sig->pos) <= 0 || PuntoY(p->sig->pos) >= Pantalla_Altura() || PuntoX(p->sig->pos) >= Pantalla_Anchura() || PuntoX(p->sig->pos) <= 0 )
        {
            ListaNodoLibera(p);

        }
        else
        {
            Pantalla_DibujaImagen(i,PuntoX(p->sig->pos),PuntoY(p->sig->pos),largo,alto);
            p=p->sig;
        }
    }
}

int ListaColisiones (Lista p, Lista r, double plargo, double palto, double qlargo, double qalto) ///balas - enemigo
{
    int contador=0;
    while (p->sig!=NULL)
    {
        Lista q=r;
        while (q->sig!=NULL)
        {
            double rect1_x=PuntoX(p->sig->pos);
            double rect2_x=PuntoX(q->sig->pos);
            double rect1_y=PuntoY(p->sig->pos);
            double rect2_y=PuntoY(q->sig->pos);
            if ( rect1_x < rect2_x + qlargo
                    && rect1_x + plargo > rect2_x
                    && rect1_y < rect2_y + qalto
                    && rect1_y + palto > rect2_y )
            {
                ListaNodoLibera(q);
                contador++;
            }

         else q=q->sig;

        }
        p=p->sig;
    }
    return contador;
}

void ListaActualizarMovimiento (Lista p, Punto cuadrado)
{
    while (p->sig!=NULL)
    {
        double vectorX=PuntoX(cuadrado)-PuntoX(p->sig->pos);
        double vectorY=PuntoY(cuadrado)-PuntoY(p->sig->pos);
        double div= sqrt(vectorX*vectorX+vectorY*vectorY);
        vectorX=vectorX/div;
        vectorY=vectorY/div;
        Punto s=PuntoCrea(vectorX,vectorY);
        p->sig->dir=s;

        p=p->sig;
    }
}

void ListaColisionConPrincipal (Lista p, Punto cuadrado,double plargo, double palto, double qlargo, double qalto, int i,int *valor,Imagen img) ///balas - cuadrado
{
    while (p->sig!=NULL)
    {
        double rect1_x=PuntoX(p->sig->pos);
        double rect2_x=PuntoX(cuadrado);
        double rect1_y=PuntoY(p->sig->pos);
        double rect2_y=PuntoY(cuadrado);
        if ( rect1_x < rect2_x + qlargo
                && rect1_x + plargo > rect2_x
                && rect1_y < rect2_y + qalto
                && rect1_y + palto > rect2_y )
        {
            Lista aux=p->sig;
            p->sig=p->sig->sig;
            free(aux);
            if (i==0)
            {
                *valor=*valor+1;
                Pantalla_DibujaImagen(img,PuntoX(cuadrado),PuntoY(cuadrado),qlargo,qalto);
            }
            else
            {
                Pantalla_ColorRelleno(255,255,255, 200);
                Pantalla_DibujaImagen(img,PuntoX(cuadrado),PuntoY(cuadrado),qlargo,qalto);
                if (*valor>0) *valor=*valor-1;
            }

        }

        else p=p->sig;

    }
}

