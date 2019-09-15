#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

#define FIN_TESTER 6
#define LISTA_CREADA 7
#define LISTA_NO_CREADA 8

int main()
{
    printf("Bienvenido al tester de lista.\n");
    int decision= 0;//Flag de decisiones.
    int estadoLista= LISTA_NO_CREADA;//Flag para indicar cuando la lista fue creada.
    tLista lista= NULL;

    do {
        printf("Elija una opcion para continuar:\n");
        printf("1- Crear lista de enteros.\n2- Agregar un entero.\n3- Imprimir lista por pantalla.\n4- Salir.\n");
        scanf("%d", &decision);

        switch(decision) {
            case 1:
            {
                if(estadoLista==LISTA_NO_CREADA){
                    crear_lista(&lista);//Se crea la lista
                    estadoLista= LISTA_CREADA;
                    printf("Se ha creado la lista satisfactoriamente.\n\n\n\n");
                }else {
                    printf("La lista ya se encuentra creada.\n\n\n\n");
                }

            }
            break;


        }

    } while(decision != FIN_TESTER);

    return 0;
}
