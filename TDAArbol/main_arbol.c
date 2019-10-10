#include <stdio.h>
#include <stdlib.h>

#include "arbol.h"

void fEliminar(tElemento e){
    free(e);
    e= NULL;
}

void preOrder(tArbol tree, tNodo nActual){

}

int main() {
    tArbol miArbol= NULL;

    printf("Creando arbol...");
    crear_arbol(&miArbol);
    printf("Arbol creado.");

    printf("Agregando raiz...");
    int *elem;
    elem= malloc(sizeof(int));
    printf("Ingrese el elemento a raiz: \n");
    scanf("%i",elem);
    crear_raiz(miArbol, elem);

    //-------CODIGO JULI--------
    tArbol arbol;
    crear_arbol(&arbol);
    int * e;
    e=malloc(sizeof(int));
    printf("Ingrese el elemento a ingresar: \n");
    scanf("%i",e);

    crear_raiz(arbol,e);
    int *a=a_recuperar(arbol,a_raiz(arbol));
    printf("%d\n",*a);
    int * e2;
    e2=malloc(sizeof(int));
    printf("Ingrese el elemento a ingresar: \n");
    scanf("%i",e2);
    a_insertar(arbol,a_raiz(arbol),NULL,e2);
    tLista hijos=a_hijos(arbol,a_raiz(arbol));
    int *a2=a_recuperar(arbol,l_recuperar(hijos,l_primera(hijos)));
    printf("%d\n",*a2);



    int * e3;
    e3=malloc(sizeof(int));
    printf("Ingrese el elemento a ingresar: \n");
    scanf("%i",e3);
    tLista hijos2=a_hijos(arbol,l_recuperar(hijos,l_primera(hijos)));
    tNodo ultimo=a_insertar(arbol,l_recuperar(hijos,l_primera(hijos)),NULL,e3);

    int *a5=a_recuperar(arbol,l_recuperar(hijos2,l_primera(hijos2)));
    printf("%d\n",*a5);


    a_eliminar(arbol, l_recuperar(hijos,l_primera(hijos)), (void (*)(tElemento)) eliminar);
    int *a4=a_recuperar(arbol,l_recuperar(hijos,l_primera(hijos)));
    printf("el ultimo elemento es %d\n",*a4);


  /*  a_eliminar(arbol, a_raiz(arbol), (void (*)(tElemento)) eliminar);
    printf("elimino\n");
    int *a2=a_recuperar(arbol,a_raiz(arbol));
    printf("%d",a2);/
    //-----FIN CODIGO JULI------

}
