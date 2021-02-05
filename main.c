#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Pantalla.h"
#include "Punto.h"
#include "Lista.h"
#include "Fichero.h"
#include "Nave.h"

#define AltoCuadrado 40.0
#define LargoCuadrado 40.0
#define velocidadCuadrado 12.0

#define AltoDisparo 18.0
#define LargoDisparo 18.0
#define velocidadDisparo 14.0

#define AltoEnemigo 24.0
#define LargoEnemigo 24.0
#define velocidadEnemigo 7.0

#define AltoEnemigoSeguidor 19.0
#define LargoEnemigoSeguidor 19.0
#define velocidadEnemigoSeguidor 10.0

#define AltoAmigo 20.0
#define LargoAmigo 20.0
#define velocidadAmigo 8.0

#define randomCrearEnemigo 60
#define randomCrearEnemigoSeguidor 700


void VaciarTodos (Lista p, Lista q, Lista r,Lista s)
{
    ListaVaciar(p);
    ListaVaciar(q);
    ListaVaciar(r);
    ListaVaciar(s);

}

void MostrarStats(char *user, int *puntuacion, int *vidas,int *porcion,double *municion,Lista balas, Lista enemigos, Lista amigos,Lista enemigos_seguidores, Punto cuadrado )
{
    Pantalla_ColorTrazo(255,255,255, 255);
    char vida[10];
    sprintf(vida,"%d",*vidas);
    Pantalla_DibujaTexto(vida,29,25);

    Pantalla_ColorTrazo(0,0,0, 255);
    char puntua[10];
    sprintf(puntua,"%d",*puntuacion);
    if (*puntuacion>=100) Pantalla_DibujaTexto(puntua,62,26);
    else  if (*puntuacion>=10) Pantalla_DibujaTexto(puntua,68,26);
    else Pantalla_DibujaTexto(puntua,72,26);

    if (*vidas==0)
    {
        Pantalla_ColorTrazo(255,0,0, 255);
        Pantalla_ColorTrazo(0,0,0, 255);
        char GameOver_Score[]="Si quiere guardar su puntuacion pulse 'Y'. Sino, pulse 'R'.";
        Pantalla_DibujaTexto(GameOver_Score,100/2,450);
    }

    if (Pantalla_TeclaPulsada(SDL_SCANCODE_R))
    {
        *vidas=5;
        *puntuacion=0;
        *porcion=0;
        *municion=5.0;
        PuntoAsignaX(cuadrado,Pantalla_Anchura()/2);
        PuntoAsignaY(cuadrado,Pantalla_Altura()/2);
        VaciarTodos(balas,enemigos,amigos,enemigos_seguidores);
    }

}

void DibujarMosaico (int *n)
{
    Pantalla_ColorRelleno(rand()%255,30,30,25);
    Pantalla_ColorTrazo(200,0,0, 30);
    int lado=Pantalla_Anchura()/(2*(*n));
    for (int i=0; i<2*(*n); i++)
        for (int j=0; j<2*(*n); j++)
        {
            Pantalla_DibujaRectangulo(i*lado,j*lado,lado,lado);
            Pantalla_ColorRelleno(rand()%255,30,30,25);
            Pantalla_DibujaLinea(i*lado,j*lado,rand()%600,rand()%600);
        }
    (*n)++;
    if ((*n)>50) (*n)=2;
}


void DibujarPorcionCorazon(int *n,int *v,Imagen cero,Imagen uno, Imagen dos)
{
    if (*n==3)
    {
        Pantalla_DibujaImagen(cero,18,45,30,30);
        *n=0;
        *v+=1;
    }
    else if (*n==2) Pantalla_DibujaImagen(dos,18,45,30,30);
    else if (*n==1) Pantalla_DibujaImagen(uno,18,45,30,30);
}

void CrearCuadrados (Lista p, Punto cuadrado, int suerte)
{
    int azar=rand()%suerte;
    double posX;
    double posY;
    if (azar==0) ///arriba
    {
        posX=rand()%Pantalla_Anchura();
        posY=1;
    }
    else if(azar==1) ///izquierda
    {
        posX=1;
        posY=rand()%Pantalla_Altura();
    }
    else if (azar==2) ///abajo
    {
        posX=rand()%Pantalla_Anchura();
        posY=Pantalla_Altura()-1;
    }
    else if (azar==3) ///derecha
    {
        posX=Pantalla_Anchura()-1;
        posY=rand()%Pantalla_Altura();
    }
    if (azar==0||azar==1||azar==2||azar==3)
    {
        double vectorX=PuntoX(cuadrado)-posX;
        double vectorY=PuntoY(cuadrado)-posY;
        double div= sqrt(vectorX*vectorX+vectorY*vectorY);
        vectorX=vectorX/div;
        vectorY=vectorY/div;
        ListaInsertarInicio(p,posX,posY,vectorX,vectorY);
    }

}

void BarraMunicion(Nave p, double *x)
{
    float *r=malloc(sizeof(float));
    float *g=malloc(sizeof(float));
    float *b=malloc(sizeof(float));
    float *h=malloc(sizeof(float));
    float *s=malloc(sizeof(float));
    float *v=malloc(sizeof(float));

    *h=36*(*x);
    *s=1;
    *v=255;
    HSVtoRGB(r,g,b,*h,*s,*v);

    Pantalla_ColorRelleno(*r,*g,*b,255);
    Punto q=NavePos(p);
    Pantalla_DibujaRectangulo(PuntoX(q),PuntoY(q)+35,NaveLargo(p)/5*(*x),5);
    if (*x<5.0) *x=*x+0.02;

    free(r);free(g);free(b);free(h);free(s);free(v);

}

int Menu ()
{
    Imagen tutorial=Pantalla_ImagenLee("imagenes/tutorial.bmp",255);
    Imagen nombre=Pantalla_ImagenLee("imagenes/nombre.bmp",255);
    Pantalla_Crea("menu", 640,480);
    Pantalla_DibujaRellenoFondo(200,20,20, 200);
    int salir=0;
    int arriba=1;
    int fin=0;
    int k=1;
    double x_raton,y_raton;

    Fichero score=FicheroLeer("score");
    FicheroImprimir(score);
    char mejor[100];
    FicheroMejorPuntuacion(score,mejor);

    while (Pantalla_Activa()&&(!fin))
    {
        Pantalla_RatonCoordenadas(&x_raton,&y_raton);
        DibujarMosaico(&k);
        Pantalla_DibujaImagen(tutorial,30,100,480,360);

        Pantalla_ColorTrazo(255,255,255, 255);
        Pantalla_DibujaTexto("RECORD",10,10);
        Pantalla_DibujaTexto(mejor,10,30);

        Pantalla_ColorTrazo(0,0,255, 255);
        Pantalla_DibujaImagen(nombre,Pantalla_Anchura()-90,Pantalla_Altura()-33,90,35);

        if (Pantalla_TeclaPulsada(SDL_SCANCODE_UP)||Pantalla_TeclaPulsada(SDL_SCANCODE_W)) arriba=1;
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN)||Pantalla_TeclaPulsada(SDL_SCANCODE_S)) arriba=-1;

        if (Pantalla_RatonBotonPulsado(1))
        {
            if (x_raton>=300 && x_raton<=350 && y_raton>=13 && y_raton<=23)
            {
                arriba=1;
                fin=1;
                salir=0;
            }
            else if(x_raton>=300 && x_raton<=350 && y_raton>=50 && y_raton<=63)
            {
                arriba=0;
                fin=1;
                salir=1;
            }
        }

        if (arriba==1)
        {
            Pantalla_ColorTrazo(255,0,0, 255);
            char Jugar[]="Jugar:";
            Pantalla_DibujaTexto(Jugar,Pantalla_Anchura()/2-20,12);

            Pantalla_ColorTrazo(0,0,0, 255);
            char Salir[]="Salir:";
            Pantalla_DibujaTexto(Salir,Pantalla_Anchura()/2-20,50);
        }
        else if(arriba==-1)
        {
            Pantalla_ColorTrazo(255,0,0, 255);
            char Salir[]="Salir:";
            Pantalla_DibujaTexto(Salir,Pantalla_Anchura()/2-20,50);

            Pantalla_ColorTrazo(0,0,0, 255);
            char Jugar[]="Jugar:";
            Pantalla_DibujaTexto(Jugar,Pantalla_Anchura()/2-20,12);
        }
        else if (arriba==0)
        {
            Pantalla_ColorTrazo(0,0,0, 255);
            char Jugar[]="Jugar:";
            Pantalla_DibujaTexto(Jugar,Pantalla_Anchura()/2-20,12);
            char Salir[]="Salir:";
            Pantalla_DibujaTexto(Salir,Pantalla_Anchura()/2-20,50);
        }

        Pantalla_Actualiza();
        Pantalla_Espera(40);

        if ( Pantalla_TeclaPulsada(SDL_SCANCODE_KP_ENTER)|| Pantalla_TeclaPulsada(SDL_SCANCODE_RETURN) )
        {
            if (arriba==1)
            {
                fin=1;
                salir=0;
            }
            else
            {
                fin=1;
                salir=1;
            }
        }

    }

    if ( !Pantalla_Activa() && (fin==0) ) salir=1;
    Pantalla_Libera();
    FicheroLibera(score);
    Pantalla_ImagenLibera(tutorial);Pantalla_ImagenLibera(nombre);
    return salir;
}

int main(int argc, char *argv[])
{
    char user[100];
    printf("Introduzca su nombre: ");
    scanf("%s",user);
    printf("\n\n********\n\n");

    if (Menu()==0)
    {
        srand(time(NULL));

        Imagen fondo=Pantalla_ImagenLee("imagenes/fondo.bmp",255);
        Imagen gameover=Pantalla_ImagenLee("imagenes/gameover.bmp",255);
        Imagen corazon=Pantalla_ImagenLee("imagenes/corazon.bmp",255);
        Imagen corazon1=Pantalla_ImagenLee("imagenes/corazon1.bmp",255);
        Imagen corazon2=Pantalla_ImagenLee("imagenes/corazon2.bmp",255);
        Imagen moneda=Pantalla_ImagenLee("imagenes/moneda.bmp",255);
        Imagen nave=Pantalla_ImagenLee("imagenes/nave.bmp",255);
        Imagen nave_golpe=Pantalla_ImagenLee("imagenes/nave_golpe.bmp",255);
        Imagen nave_punto=Pantalla_ImagenLee("imagenes/nave_punto.bmp",255);
        Imagen bala=Pantalla_ImagenLee("imagenes/bola.bmp",255);
        Imagen roca=Pantalla_ImagenLee("imagenes/roca.bmp",255);
        Imagen seguidor=Pantalla_ImagenLee("imagenes/roca_seguidor.bmp",255);
        Imagen gema=Pantalla_ImagenLee("imagenes/c.bmp",255);

        Pantalla_Crea("pantalla", 640 ,480);
        Nave Principal=NaveCrear(AltoCuadrado,LargoCuadrado);
        int mousePulsado=0; ///estado del clic izquierdo del ratón para disparar
        int mousePulsado2=0; ///estado del clic derecho del ratón para disparar cruzado
        int porcion=0;
        int puntuacion=0;
        int vidas=5;
        double municion=5.0; ///municion inicial

        Lista balas=ListaCrea();
        Lista enemigos=ListaCrea();
        Lista amigos=ListaCrea();
        Lista enemigos_seguidores=ListaCrea();

        while (Pantalla_Activa())
        {
            Pantalla_DibujaRellenoFondo(250,250,250, 50);
            Pantalla_DibujaImagen(fondo,0,0,640,480);
            Pantalla_DibujaImagen(corazon,15,15,35,35);
            Pantalla_DibujaImagen(moneda,60,15,30,35);
            Pantalla_ColorRelleno(255,0,0, 255);

            MostrarStats(user,&puntuacion,&vidas,&porcion,&municion,balas,enemigos,amigos,enemigos_seguidores,NavePos(Principal));
            if (vidas>0)
            {
                BarraMunicion(Principal,&municion);

                DibujarPorcionCorazon(&porcion,&vidas,corazon,corazon1,corazon2);
                NaveDibujar(nave,Principal);
                NaveMovimiento(Principal,velocidadCuadrado);
                Pantalla_ColorRelleno(0,0,255, 255);

                NaveDisparar(Principal,balas,LargoDisparo,AltoDisparo,&mousePulsado);
                NaveDispararExplosivo(Principal,balas,LargoDisparo,AltoDisparo,&mousePulsado2,&municion);
                ListaImprimirImagen(bala,balas,LargoDisparo,AltoDisparo);
                ListaMover(balas,velocidadDisparo);

                Pantalla_ColorRelleno(0,255,0, 255); ///enemigos
                CrearCuadrados(enemigos,NavePos(Principal),randomCrearEnemigo);
                ListaImprimirImagen(roca,enemigos,LargoEnemigo,AltoEnemigo);
                ListaMover(enemigos,velocidadEnemigo);

                Pantalla_ColorRelleno(238,rand()%200,217, 255); ///enemigos_seguidores
                CrearCuadrados(enemigos_seguidores,NavePos(Principal),randomCrearEnemigoSeguidor);
                ListaImprimirImagen(seguidor,enemigos_seguidores,LargoEnemigo,AltoEnemigo);

                ListaMover(enemigos_seguidores,velocidadEnemigoSeguidor);
                ListaActualizarMovimiento(enemigos_seguidores,NavePos(Principal));
                porcion+=ListaColisiones(balas,enemigos_seguidores,LargoDisparo,AltoDisparo,LargoEnemigoSeguidor,AltoEnemigoSeguidor);


                Pantalla_ColorRelleno(255,255,0, 255); ///amigos
                int NumAmigos=ListaColisiones(balas,enemigos,LargoDisparo,AltoDisparo,LargoEnemigo,AltoEnemigo);
                for (int i=0; i<NumAmigos; i++) CrearCuadrados(amigos,NavePos(Principal),4);
                ListaImprimirImagen(gema,amigos,LargoAmigo,AltoAmigo);
                ListaMover(amigos,velocidadAmigo);
                ListaActualizarMovimiento(amigos,NavePos(Principal));

                int NumPuntos=ListaColisiones(balas,amigos,LargoDisparo,AltoDisparo,LargoAmigo,AltoAmigo); ///colisiones
                if (puntuacion>=NumPuntos) puntuacion-=NumPuntos;
                ListaColisionConPrincipal(amigos,NavePos(Principal),LargoAmigo,AltoAmigo,NaveLargo(Principal),NaveAlto(Principal),0,&puntuacion,nave_punto);
                ListaColisionConPrincipal(enemigos,NavePos(Principal),LargoEnemigo,AltoEnemigo,NaveLargo(Principal),NaveAlto(Principal),1,&vidas,nave_golpe);
                ListaColisionConPrincipal(enemigos_seguidores,NavePos(Principal),LargoEnemigoSeguidor,AltoEnemigoSeguidor,NaveLargo(Principal),NaveAlto(Principal),1,&vidas,nave_golpe);


            }
            else
            {
                Pantalla_DibujaImagen(gameover,180,80,300,300);
                VaciarTodos(balas,amigos,enemigos,enemigos_seguidores);
                if (Pantalla_TeclaPulsada(SDL_SCANCODE_Y))
                {
                    Fichero score=FicheroLeer("score");
                    FicheroInserta(score,"score",user,puntuacion);
                    system("cls");
                    FicheroImprimir(score);
                    FicheroLibera(score);
                    vidas=5;
                    puntuacion=0;
                    porcion=0;
                    municion=5.0;
                    PuntoAsignaX(NavePos(Principal),Pantalla_Anchura()/2);
                    PuntoAsignaY(NavePos(Principal),Pantalla_Altura()/2);
                }

            }
            Pantalla_Actualiza();
            Pantalla_Espera(40);
        }
        NaveLibera(Principal);
        Pantalla_ImagenLibera(fondo);Pantalla_ImagenLibera(gameover);Pantalla_ImagenLibera(corazon);
        Pantalla_ImagenLibera(corazon1);Pantalla_ImagenLibera(corazon2);Pantalla_ImagenLibera(moneda);
        Pantalla_ImagenLibera(nave);Pantalla_ImagenLibera(nave_golpe);Pantalla_ImagenLibera(bala);
        Pantalla_ImagenLibera(roca);Pantalla_ImagenLibera(seguidor);Pantalla_ImagenLibera(gema);
        Pantalla_ImagenLibera(nave_punto);

        ListaLibera(balas);ListaLibera(amigos);ListaLibera(enemigos);ListaLibera(enemigos_seguidores);

    }
    Pantalla_Libera();

    return 0;
}
