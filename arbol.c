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
    tPosicion it;
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
         it= l_primera(hermanos);

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
 Se simula la eliminacion del nodo, en este se anula la asignacion al nodo padre del mismo,
 de esta forma causando el desreferenciamiento del mismo sobre el arbol.
**/
void fEliminarNodoSuperficial(tElemento e){
    tNodo nElim;
    nElim=(tNodo) e;
    nElim->padre= NULL;//De esta manera simulo que es el nodo raiz.
}

/**
 * Se encarga de eliminar el nodo parametrizado haciendo uso de la funcion globlal EliminarElemento.
 * @param nodo Nodo a eliminar.
 */
void fEliminarNodo(tNodo nodo){
    eliminarElem(nodo->elemento);
    free(nodo->elemento);
    free(nodo->hijos);
    free(nodo);
}

/**
 * Se encarga de buscar la posicion en la lista parametrizada de el nodo parametrizado.
 * @param l Lista en la cual se buscara la posicion.
 * @param nodo Nodo al cual se le buscara la posicion.
 * @return Posicion de nodo en la lista l.
 */
tPosicion buscarPos(tLista l,tNodo nodo){
    tPosicion posicion=l_primera(l);
    int encontre=0;
    while(posicion!=NULL && encontre!=1){
        if(l_recuperar(l,posicion)==nodo){
            encontre=1;
        }
        else{
            posicion=l_siguiente(l,posicion)!=NULL?l_siguiente(l,posicion):NULL;
        }
    }
    return posicion;
}

/**
 * Funcion que se utilizara cuando se conoce que no se elimina los nodos realmente.
 * @param nodo nodo el cual se "eliminara".
 */
void fEliminarNodoVacio(tNodo nodo){ }

/**
 Elimina el nodo N de A.
 El elemento almacenado en el arbol es eliminado mediante la funcion fEliminar parametrizada.
 Si N es la raiz de A, y tiene un solo hijo, este pasa a ser la nueva raiz del arbol.
 Si N es la raiz de A, y a su vez tiene mas de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la raiz de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posicion que ocupa N en la lista de hijos de su padre.
**/
void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    tLista hijos= n->hijos;
    tNodo padre= n->padre;
    tLista hermanos;
    tNodo hijoraiz;
    tLista listaaux;
    tPosicion posEnHermanos;
    tPosicion posHijos;
    eliminarElem= fEliminar;

    if(n==a->raiz){//Si el nodo a eliminar es la raiz
        if(l_primera(hijos)==l_fin(hijos)){//Si no posee hijos
            fEliminarNodo(n);
            a->raiz=NULL;
        }
        else{
            if(l_siguiente(hijos,l_primera(hijos))==l_fin(hijos)){//Si tiene un solo hijo
                hijoraiz= l_recuperar(hijos, l_primera(hijos));
                listaaux= hijos;
                eliminarElem(n->elemento);
                n->hijos= hijoraiz->hijos;
                n->elemento= hijoraiz->elemento;
                l_destruir(&listaaux, (void (*)(tElemento)) fEliminarNodo);
            }
            else{//Si tiene mas de un hijo
                exit(ARB_OPERACION_INVALIDA);
            }
        }
    }
    else{//Si el nodo a eliminar no es la raiz
        hermanos= padre->hijos;
        posEnHermanos= buscarPos(hermanos,n);
        if(l_primera(hijos)==l_fin(hijos)){//Si el nodo a eliminar no posee hijos
            l_destruir(&hijos, (void (*)(tElemento)) &fEliminarNodo);
            l_eliminar(hermanos, posEnHermanos, (void (*)(tElemento)) &fEliminarNodo);
        }
        else{//Si el nodo a eliminar posee hijos
            posHijos= l_ultima(hijos);
            while( posHijos!=l_primera(hijos) ){
                l_insertar(hermanos, l_siguiente(hermanos,posEnHermanos), l_recuperar(hijos, posHijos));
                posHijos= l_anterior(hijos,posHijos);
            }
            l_insertar(hermanos, l_siguiente(hermanos,posEnHermanos), l_recuperar(hijos, posHijos));
            l_destruir(&hijos, (void (*)(tElemento)) &fEliminarNodoVacio);
            posEnHermanos= buscarPos(hermanos,n);
            l_eliminar(hermanos, posEnHermanos, (void (*)(tElemento)) &fEliminarNodo);
        }
    }

}

/**
 * Se encarga de recorrer el arbol parametrizado en posOrder a medida que elimina los nodos del mismo.
 * @param arbol Arbol a recorrer.
 * @param nodo Nodo en el cual te encuentras posicionado actualmente.
 */
void posOrden(tArbol arbol, tNodo nodo){
    tNodo hijo= NULL;
    tPosicion posHijo= NULL;

    if(l_primera(nodo->hijos)!=l_fin(nodo->hijos)){//Si el nodo posee hijos
        hijo= l_recuperar(nodo->hijos, l_primera(nodo->hijos));
        posHijo= l_primera(nodo->hijos);
    }

    while(hijo!=NULL && posHijo!=NULL){
        posOrden(arbol, hijo);
        posHijo= ( posHijo!=l_ultima(nodo->hijos) ) ? l_siguiente(nodo->hijos, posHijo) : NULL;
        hijo= ( posHijo!=NULL ) ? l_recuperar(nodo->hijos,posHijo) : NULL;
    }

    l_destruir(&(nodo->hijos), eliminarElem);
    fEliminarNodo(nodo);
}

/**
 Destruye el arbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el arbol son eliminados mediante la funcion fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)) {
    eliminarElem= fEliminar;
    posOrden(*a, (*a)->raiz);
    free(*a);
    (*a)= NULL;
}

/**
Recupera y retorna el elemento del nodo N.
*/
tElemento a_recuperar(tArbol a, tNodo n){
    if(n==NULL) {
        exit(ARB_POSICION_INVALIDA);
    }

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
        l_eliminar(padre->hijos,actual,fEliminarNodoSuperficial);

    }else{
        (*sa)->raiz= n;
        a->raiz= NULL;
    }



}