#include <stdio.h>
#include <stdlib.h>

#include "lista.h"


/**
 Inicializa una lista vacia.
 Una referencia a la lista creada es referenciada en *L.
**/
void crear_lista(tLista * l) {
    *l= (tLista)malloc(sizeof(struct celda));
    (*l)->siguiente= NULL;
    (*l)->elemento= NULL;
}

/**
 Inserta el elemento E, en la posicion P, en L.
 Con L = A,B,C,D y la posicion P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e) {
    tPosicion *nuevo;
    *nuevo=(tPosicion)malloc(sizeof(struct celda));

    (*nuevo)->siguiente= p->siguiente;
    (*nuevo)->elemento= e;
    p->siguiente= *nuevo;
}

