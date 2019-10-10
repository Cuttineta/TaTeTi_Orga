#include <stdio.h>
#include <stdlib.h>

#include "arbol.h"

/**
Inicializa un arbol vacio.
Una referencia al arbol creado es referenciado en *A.
**/
void crear_arbol(tArbol * a) {
    *a= (tArbol) malloc(sizeof(struct arbol));
    if((*a)==NULL){
        exit(ARB_ERROR_MEMORIA);
    }

    (*a)->raiz= NULL;
}

/**
Crea la raiz de A.
Si A no es vacio, finaliza indicando ARB_OPERACION_INVALIDA.
**/
void crear_raiz(tArbol a, tElemento e){
    if(a->raiz!=NULL){//Si el arbol ya posee una raiz
        exit(ARB_OPERACION_INVALIDA);
    }

    tNodo rootA=(tNodo) malloc(sizeof(struct nodo));
    if(rootA==NULL){
        exit(ARB_ERROR_MEMORIA);
    }

    rootA->padre= NULL;
    rootA->elemento= e;
    crear_lista(&rootA->hijos);
    a->raiz= rootA;
}

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo rotulo es E.
 Si NH es NULL, el nuevo nodo se agrega como ultimo hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e);

/**
 Elimina el nodo N de A.
 El elemento almacenado en el arbol es eliminado mediante la funcion fEliminar parametrizada.
 Si N es la raiz de A, y tiene un solo hijo, este pasa a ser la nueva raiz del arbol.
 Si N es la raiz de A, y a su vez tiene mas de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la raiz de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posicion que ocupa N en la lista de hijos de su padre.
**/
void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){

    tPosicion primera;//primer hijo de N
    tPosicion ultima;//ultimo hijo de N
    tPosicion posN;//posicion de N en la lista de hijos de su padre
    tPosicion act;//posicion auxiliar para recorrer los hijos de N y luego insertar en la lista de hijos de su padre
    tLista hijosPadre;

    if(a==NULL||n==NULL){
        exit(ARB_OPERACION_INVALIDA);
    }

    primera= l_primera(n->hijos);
    ultima= l_ultima(n->hijos);

    if(a->raiz==n){
            if(a->raiz->hijos==NULL){
                    fEliminar(a->raiz->elemento);
                    free(a->raiz);
            }else{
                if(primera==ultima){
                    hijosPadre= a->raiz->hijos;
                    a->raiz->hijos= n->hijos;
                    a->raiz->elemento= n->elemento;
                    fEliminar(a->raiz->padre->elemento);
                    l_destruir(&hijosPadre,fEliminar);
                    a->raiz->padre=NULL;
                    free(a->raiz->padre);

            } else
            exit(ARB_OPERACION_INVALIDA);

        }

    }
    else{
        hijosPadre= n->padre->hijos;
        posN=l_primera(hijosPadre);
        while(posN!=NULL&&posN->elemento!=n){
            posN= posN->siguiente;
        }
        act=primera;
        while(act!=NULL){
            l_insertar(hijosPadre,posN,l_recuperar(n->hijos,act));
            act=act->siguiente;
        }
        l_eliminar(hijosPadre,posN,fEliminar);
    }
}

/**
 Destruye el arbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el arbol son eliminados mediante la funcion fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento));

/**
Recupera y retorna el elemento del nodo N.
*/
tElemento a_recuperar(tArbol a, tNodo n){
    if(n==NULL)
        exit(ARB_POSICION_INVALIDA);

    return n->elemento;
}

/**
Recupera y retorna el nodo correspondiente a la raiz de A.
**/
tNodo a_raiz(tArbol a){
    if(a->raiz==NULL){
        exit(ARB_OPERACION_INVALIDA);
    }
    return a->raiz;
}

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
tLista a_hijos(tArbol a, tNodo n){
    if(n==NULL){
        exit(ARB_POSICION_INVALIDA);
    }
    return n->hijos;
}

/**
 Inicializa un nuevo arbol en *SA.
 El nuevo arbol en *SA se compone de los nodos del subarbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol a, tNodo n, tArbol * sa);
