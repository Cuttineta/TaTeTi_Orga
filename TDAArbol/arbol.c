#include <stdio.h>
#include <stdlib.h>

#include "arbol.h"

void (*eliminarElem)(tElemento);//Variable global que referenciara a la funcion que elimina los elementos contenidos por el nodo

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
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    if(np==NULL){
        exit(ARB_POSICION_INVALIDA);
    }

    tLista hermanos= np->hijos;
    tPosicion posInsertar= NULL;
    tNodo nuevo= (tNodo) malloc(sizeof(struct nodo));
    if(nuevo==NULL){
        exit(ARB_ERROR_MEMORIA);
    }

    if(nh!=NULL && l_primera(hermanos)==l_fin(hermanos)){//Si NH no es nulo y NP no posee hijos
        exit(ARB_POSICION_INVALIDA);
    }

    if(nh==NULL || l_primera(hermanos)==l_fin(hermanos)){//Si NH es nulo o si NP no posee hijos
        posInsertar= l_fin(hermanos);
    }
    else {//NP posee hijos y NH es distinto de nulo
        tPosicion it= l_primera(hermanos);

        while(l_recuperar(hermanos, it)!=nh && it!=l_fin(hermanos)){//Mientras no haya encontrado a nh y no haya visitado todos los hijos
            it= l_siguiente(hermanos, it);
        }
        if(it==l_fin(hermanos)){
            exit(ARB_POSICION_INVALIDA);//NH no corresponde a un hijo de NP
        }

        posInsertar= it;
    }

    nuevo->elemento= e;
    crear_lista( &(nuevo->hijos) );
    nuevo->padre= np;
    l_insertar(hermanos, posInsertar, nuevo);

    return nuevo;
}

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
        posN= l_primera(hijosPadre);
        while(posN!=NULL&&posN->elemento!=n){
            posN= posN->siguiente;
        }
        act= primera;
        while(act!=NULL){
            l_insertar(hijosPadre,posN,l_recuperar(n->hijos,act));
            act= act->siguiente;
        }
        l_eliminar(hijosPadre,posN,fEliminar);
    }
}

/**
 Destruye el arbol A utilizando un recorrido en postOrder invertido.
 @param tElemento elem -> hace referencia al nodo actual del recorrido el cual va a ser eliminado.
**/
void a_destruirAux(tElemento elem){
    if(elem!=NULL){
        tNodo nodoElim= elem;

        nodoElim->padre= NULL;
        eliminarElem(nodoElim->elemento);
        l_destruir(&(nodoElim->hijos), &a_destruirAux);
        nodoElim->hijos= NULL;
        free(nodoElim);
        elem=NULL;
    }

}

/**
 Destruye el arbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el arbol son eliminados mediante la funcion fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)) {
    eliminarElem= fEliminar;
    tNodo nActual= (*a)->raiz;
    if(nActual!=NULL){
        a_destruirAux(nActual);
    }
    free(*a);
    (*a)= NULL;
}

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
 Metodo a utilizarse para eliminar un nodo en el metodo a_sub_arbol.
**/
void fEliminarSubArbol(tElemento e){
    tNodo nElim=(tNodo) e;
    nElim->padre= NULL;//De esta manera simulo que es el nodo raiz.
}

/**
 Inicializa un nuevo arbol en *SA.
 El nuevo arbol en *SA se compone de los nodos del subarbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){
    tPosicion actual, ultima;
    tNodo padre;
    int es;
    if(a==NULL||n==NULL||sa==NULL){
        exit(ARB_POSICION_INVALIDA);
    }
    crear_arbol(sa);

    if(a->raiz!=n){
        (*sa)->raiz= n;
        padre= n->padre;
        if(padre->hijos==NULL){//Arbol corrupto
            exit(ARB_POSICION_INVALIDA);
        }
        actual= l_primera(padre->hijos);
        ultima= l_fin(padre->hijos);
        es= 0;//Flag para indicar si se encontro la posicion del tNodo n en la lista de hijos del padre

        while(!es && actual!=ultima){//While para encontrar la posicion de lista de n
                es= l_recuperar(padre->hijos,actual)==n;
                if(!es)
                    actual= (actual->siguiente==ultima) ? (NULL) : (actual->siguiente);
        }
        if(!es)
            exit(ARB_POSICION_INVALIDA);

        //Una vez eliminado el nodo de la lista de hijos del padre, todo descendiente del mismo se ve desprendido del arbol a
        l_eliminar(padre->hijos,actual,fEliminarSubArbol);

    }else{
        (*sa)->raiz= n;
        a->raiz= NULL;
    }

}
