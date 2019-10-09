#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

#define FIN_TESTER 6
#define LISTA_CREADA 7
#define LISTA_NO_CREADA 8


void mostrar(tLista l){
    int *elem;
    tPosicion pos= l_primera(l);
    printf("[");
    while(pos!=l_fin(l)){
        if(pos!=l_ultima(l)){
            elem =l_recuperar(l,pos);
            printf("%d - ",*elem);}
        else{
            elem= l_recuperar(l,pos);
            printf("%d",*elem);

        }
        pos= l_siguiente(l,pos);

    }
    printf("] \n");

}
void fEliminar(tElemento e){
    free(e);
    e= NULL;
}

int main() {
    printf("Bienvenido al tester de lista.\n");
    int *elem;//Utilizado para crear el espacio en memoria al insertar un nuevo elemento
    int decision= 0;//Flag de decisiones.
    int estadoLista= LISTA_NO_CREADA;//Flag para indicar cuando la lista fue creada.
    tLista lista= NULL;

    do {
        printf("Elija una opcion para continuar:\n");
        printf("1- Crear lista de enteros.\n2- Agregar un entero.\n3- Imprimir lista por pantalla.\n4- Salir.\n\n");
        scanf("%d", &decision);

        switch(decision) {
            case 1:
            {
                if(estadoLista==LISTA_NO_CREADA){
                    crear_lista(&lista);//Se crea la lista
                    estadoLista= LISTA_CREADA;
                    printf("Se ha creado la lista satisfactoriamente.\n\n");
                }else {
                    printf("La lista ya se encuentra creada.\n\n");
                }

            }break;

            case 2:
            {
                if(estadoLista==LISTA_NO_CREADA){
                    printf("Debe crear la lista para poder agregar elementos.\n\n");
                }else {
                    elem =(int *)malloc(sizeof(int));
                    printf("Ingrese el elemento a insertar en la lista: \n");
                    scanf("%d", elem);

                    l_insertar(lista, l_fin(lista), elem);

                    printf("El elemento se ha insertado satisfactoriamente.\n\n");
                }
            }break;

            case 3:
            {
               if(estadoLista==LISTA_NO_CREADA)
                    printf("No se ha creado la lista. \n\n");
                else
                    mostrar(lista);
            }break;

            case 4:
            {
                if(estadoLista==LISTA_CREADA)
                    l_destruir(&lista,&fEliminar);

                decision= FIN_TESTER;

            }break;

            default:
            {
                decision= 0;
                printf("Opcion invalida.\n\n");
            }
        }

    } while(decision != FIN_TESTER);

    printf("\n");
    printf("Fin del tester.\n");

    return 0;
}
