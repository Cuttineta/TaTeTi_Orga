#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"


void crear_arbol(tArbol * a){
    *a=(tArbol)malloc(sizeof(struct arbol));
    if(*a==NULL){
        exit(ARB_ERROR_MEMORIA);
    }
    (*a)->raiz=NULL;
}


void crear_raiz(tArbol a, tElemento e){
    if(a->raiz->elemento!=NULL){
        exit(ARB_OPERACION_INVALIDA);
    }
    a->raiz->elemento=e;
}


tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e);


void a_eliminar(tArbol a, tNodo pa, void (*fEliminar)(tElemento));

void a_destruir(tArbol * a, void (*fEliminar)(tElemento));

tElemento a_recuperar(tArbol a, tNodo n);

tNodo a_raiz(tArbol a);


tLista a_hijos(tArbol a, tNodo n);


void a_sub_arbol(tArbol a, tNodo n, tArbol * sa);

