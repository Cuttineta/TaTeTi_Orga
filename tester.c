#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

#define FIN_TESTER 6
#define LISTA_CREADA 7
#define LISTA_NO_CREADA 8

void mostrarPorPantalla(tLista l){
    tPosicion pos= l_primera(l);
    printf("Lista: ");
    while(pos != l_fin(l)) {
        int *elem= l_recuperar(l, pos);
        printf("%d ", *elem);
        pos= l_siguiente(l, pos);
    }
    int *elem= l_recuperar(l, pos);
    printf("%d .\n\n", *elem);

}

int main() {
    printf("Bienvenido al tester de lista.\n");
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
                    int elem= 0;
                    printf("Ingrese el elemento a insertar en la lista: \n");
                    scanf("%d", &elem);

                    l_insertar(lista, l_primera(lista), &elem);

                    int *valor= l_recuperar(lista, l_primera(lista));
                    printf("Primera: %d\n", *valor);

                    printf("El elemento se ha insertado satisfactoriamente.\n\n");
                }
            }break;

            case 3:
            {
                mostrarPorPantalla(lista);
            }break;

            case 4:
            {
                //AGREGAR DESTRUIR LISTA
                decision= FIN_TESTER;
            }break;

            default:
            {
                decision= 0;
                printf("Opcion invalida.\n\n");
            }
        }

    } while(decision != FIN_TESTER);

    printf("Fin del tester.\n");

    return 0;
}
