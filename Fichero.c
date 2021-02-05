#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fichero.h"

#define MAX 100

struct Nodo
{
    char nombre[100];
    int puntuacion;
};

typedef struct Nodo Nodo;
struct FicheroRep
{
    Nodo nodos[MAX];
    int n;
};

Fichero FicheroCrea ()
{
    Fichero aux=malloc(sizeof(struct FicheroRep));
    aux->n = 0;
    return aux;
}

void FicheroLibera(Fichero p)
{
    free(p);
}


Fichero FicheroLeer (char *nombreFichero)
{
    Fichero p = FicheroCrea();
    FILE * f = fopen(nombreFichero,"r");
    while(!feof(f))
    {
        int auxPuntuacion;
        char auxNombre[100];
        if (fscanf(f,"%s %d",auxNombre,&auxPuntuacion)==2)
        {
            strcpy(p->nodos[p->n].nombre,auxNombre);
            p->nodos[p->n].puntuacion=auxPuntuacion;
            p->n=p->n+1;
        }
    }
    fclose(f);
    return p;
}

int FicheroNombreExistente (Fichero p, char *nombre, int puntuacion)
{
    int indice=0;
    for (; (indice< p->n) && (strcmp(nombre, p->nodos[indice].nombre)) ; indice++);
    if (indice < p->n) p->nodos[indice].puntuacion=puntuacion;
    return (indice < p->n);
}

void FicheroInserta (Fichero p, char *nombreFichero, char *nombre, int puntuacion)
{
    if (!FicheroNombreExistente(p,nombre,puntuacion))
    {
        strcpy(p->nodos[p->n].nombre,nombre);
        p->nodos[p->n].puntuacion=puntuacion;
        p->n=p->n+1;
    }
    FILE * f = fopen(nombreFichero,"w");
    for(int indice=0; indice< p->n ; indice++) fprintf(f,"%s %d\n",p->nodos[indice].nombre, p->nodos[indice].puntuacion);
    fclose(f);
}

void FicheroMejorPuntuacion (Fichero p, char *mejor)
{
    strcpy(mejor,"");
    int mayor=0;
    int indice=0;
    while (indice < p->n )
    {
        if (mayor < p->nodos[indice].puntuacion)
        {
            strcpy(mejor,p->nodos[indice].nombre);
            mayor=p->nodos[indice].puntuacion;
        }
        indice++;
    }
    sprintf(mejor,"%s : %d",mejor,mayor);
}

void FicheroImprimir (Fichero p)
{
    printf("La puntuacion de todos los jugadores son:\n");
    for(int indice=0; indice< p->n ; indice++)
        printf("%s: %d\n",p->nodos[indice].nombre,p->nodos[indice].puntuacion);
    char aux[100];
    FicheroMejorPuntuacion(p,aux);
    printf("\n\nRECORD -> %s\n",aux);

}


