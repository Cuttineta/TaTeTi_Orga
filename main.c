#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include "partida.h"
#include "ia.h"

/**
 * Se encarga de inicializar la matriz que se mostrara visulmente por pantalla la cual sera de la siguiente forma:
 *   - - -
 *   - - -
 *   - - -
 *   @param t matriz la cual contendra la parte visual del juego, y la cual sera mostrada por pantalla.
 */
void inicializar_tablero(char t [][3]){
    int cont= 45;//Codigo ascii para '-'

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            t[i][j]= cont;
        }
    }
}

/**
 * Actualiza el estado actual del tableroVisual en torno a lo indicado por la partida pasada por parametro,
 *  y luego muestra la misma por pantalla.
 * @param p la partida la cual se esta jugando.
 * @param tableroVisual matriz que contiene la parte visual de la partida.
 */
void mostrar_tablero(tPartida p, char  tableroVisual [][3]){
    //Actualizando estado actual del tablero
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if( (p->tablero)->grilla[i][j]== 1){
                tableroVisual[i][j]='X';
            }
            else if( (p->tablero)->grilla[i][j]== 2){
                tableroVisual[i][j]='O';
            }
        }
    }

    //Mostrar tablero por pantalla
    printf("Guia:   Tablero:\n");
    int cont= 49;//Codigo ascii para el numero 1
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%c ", cont++);
        }
        printf("   ");
        for(int t=0; t<3; t++){
            printf("%c ", tableroVisual[i][t]);
        }
        printf("\n");
    }

}

int main() {
    int modo_de_juego;
    tPartida partida;
    char tableroVisual[3][3];
    char nombreJugador1[25];
    char nombreJugador2[25];
    int movimiento, mov_x, mov_y;
    int orden, comienza;

    //Seleccion de modo de juego
    printf("Bienvenido al juego TATETI.\nModos de juego:\n[1]: Jugador vs Jugador\n[2]: Jugador vs IA\n[3]: IA vs IA\n");
    printf("Seleccione un modo de juego: ");
    scanf("%d", &modo_de_juego);
    switch (modo_de_juego){
        case 1: modo_de_juego= PART_MODO_USUARIO_VS_USUARIO;
            break;
        case 2: modo_de_juego= PART_MODO_USUARIO_VS_AGENTE_IA;
            break;
        case 3: modo_de_juego= PART_MODO_AGENTE_IA_VS_AGENTE_IA;
            break;
        default: printf("Opcion incorrecta. Seleccione una de las opciones validas.");
    }

    //Seleccion de nombres
    if(modo_de_juego==PART_MODO_USUARIO_VS_AGENTE_IA || modo_de_juego==PART_MODO_USUARIO_VS_USUARIO) {
        printf("Ingrese el nombre del jugador 1: ");
        scanf("%s", nombreJugador1);
        if(modo_de_juego==PART_MODO_USUARIO_VS_USUARIO) {
            printf("Ingrese el nombre del jugador 2: ");
            scanf("%s", nombreJugador2);
        }
        else{//Ply vs IA
            strcpy(nombreJugador2, "IA");
        }
    }
    else{//IA vs IA
        strcpy(nombreJugador1, "IA1");
        strcpy(nombreJugador2, "IA2");
    }

    //Seleccion de orden para ver quien comienza jugando
    srand(time(NULL));
    printf("\n¿Quien empieza?\n[1]: %s\n[2]: %s\n[3]: Random\nSeleccione: ",nombreJugador1, nombreJugador2);
    scanf("%d", &orden);

    while (orden < 1 || orden > 3) {//Mientras que no seleccionen uno de los ordenes correspondientes repetir
        fflush(stdin);
        printf("Inserte un numero valido.\n[1]: %s\n[2]: %s\n[3]: Random\nSeleccione: ",nombreJugador1, nombreJugador2);
        scanf("%d", &orden);
    }

    if (orden == 1){
        comienza = PART_JUGADOR_1;
    } else if (orden == 2) {
        comienza = PART_JUGADOR_2;
    } else if (orden == 3){
        comienza = (rand() % 2) == 0?PART_JUGADOR_1:PART_JUGADOR_2;

        if (comienza == PART_JUGADOR_1){
            printf("Empieza %s.\n", nombreJugador1);
        } else{
            printf("Empieza %s.\n", nombreJugador2);
        }
    }

    //Inicializacion de la partida con los parametros recolectados previamente
    nueva_partida(&partida, modo_de_juego, comienza, nombreJugador1, nombreJugador2);
    inicializar_tablero(tableroVisual);

    while(partida->estado==PART_EN_JUEGO) {
        if (partida->turno_de == PART_JUGADOR_1) {
            printf("Turno de %s => Simbolo 'X':\n", partida->nombre_jugador_1);
        } else {
            printf("Turno %s => Simbolo 'O':\n", partida->nombre_jugador_2);
        }

        mostrar_tablero(partida, tableroVisual);

        movimiento= PART_MOVIMIENTO_ERROR;//Flag que se utilizara para que se realice un movimiento valido
        while (movimiento==PART_MOVIMIENTO_ERROR){

            if(modo_de_juego==PART_MODO_USUARIO_VS_USUARIO || (modo_de_juego==PART_MODO_USUARIO_VS_AGENTE_IA && partida->turno_de==PART_JUGADOR_1)) {
                printf("Seleccione una posicion: ");
                scanf("%d", &movimiento);
                switch (movimiento) {
                    case 1:
                        mov_x = 0;
                        mov_y = 0;
                        break;
                    case 2:
                        mov_x = 0;
                        mov_y = 1;
                        break;
                    case 3:
                        mov_x = 0;
                        mov_y = 2;
                        break;
                    case 4:
                        mov_x = 1;
                        mov_y = 0;
                        break;
                    case 5:
                        mov_x = 1;
                        mov_y = 1;
                        break;
                    case 6:
                        mov_x = 1;
                        mov_y = 2;
                        break;
                    case 7:
                        mov_x = 2;
                        mov_y = 0;
                        break;
                    case 8:
                        mov_x = 2;
                        mov_y = 1;
                        break;
                    case 9:
                        mov_x = 2;
                        mov_y = 2;
                        break;
                    default:
                        printf("Opcion incorrecta. Seleccione una de las opciones validas.\n");
                        movimiento = PART_MOVIMIENTO_ERROR;
                }
            }
            else{//Si es el turno de la IA
                tBusquedaAdversaria busqueda;

                crear_busqueda_adversaria(&busqueda, partida);
                proximo_movimiento(busqueda, &mov_x, &mov_y);
                destruir_busqueda_adversaria(&busqueda);
            }

            movimiento= nuevo_movimiento(partida, mov_x, mov_y);
            if(movimiento==PART_MOVIMIENTO_ERROR) {
                printf("Opcion incorrecta. Seleccione una de las opciones validas.\n");
            }

        }//Fin bucle movimiento

    }//Fin bucle juego

    if(partida->estado == PART_GANA_JUGADOR_1){
        printf("%s WINS\n", partida->nombre_jugador_1);
    }
    else if(partida->estado == PART_GANA_JUGADOR_2){
        printf("%s WINS\n", partida->nombre_jugador_2);
    }
    else if(partida->estado == PART_EMPATE){
        printf("EMPATE\n");
    }
    mostrar_tablero(partida, tableroVisual);
    printf("END GAME\n");
    finalizar_partida(&partida);

}
