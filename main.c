#include <stdio.h>
#include <stdlib.h>

#include "partida.h"
#include <time.h>


void inicializar_tablero(char t [][3]){
    int cont= 49;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            t[i][j]= cont++;
        }
    }
}

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

    //Mostrando tablero por pantalla
    for(int r=0; r<3; r++){
        for(int t=0; t<3; t++){
            printf("%c ", tableroVisual[r][t]);
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

    printf("Bienvenido al juego TATETI.\nModos de juego:\n[1]: Jugador vs Jugador\nLos otros modos de juego seran lanzados en la proxima version.\n");
    printf("Seleccione un modo de juego: ");
    scanf("%d", &modo_de_juego);
    switch (modo_de_juego){
        case 1: modo_de_juego= PART_MODO_USUARIO_VS_USUARIO;
            break;
        /*case 2: modo_de_juego= PART_MODO_USUARIO_VS_AGENTE_IA;
            break;
        case 3: modo_de_juego= PART_MODO_AGENTE_IA_VS_AGENTE_IA;
            break;*/
        default: printf("Opcion incorrecta. Seleccione una de las opciones validas.");
    }

    printf("Ingrese el nombre del jugador 1: ");
    scanf("%s", nombreJugador1);
    printf("Ingrese el nombre del jugador 2: ");
    scanf("%s", nombreJugador2);


    //AÑADIDO
    srand(time(NULL));
    printf("\n¿Quien empieza?\n[1]: %s\n[2]: %s\n[3]: Random\nSeleccione: ",nombreJugador1, nombreJugador2);
    scanf("%d", &orden);

    while (orden < 1 || orden > 3) {
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
            printf("Empieza %s\n", nombreJugador1);
        } else{
            printf("Empieza %s\n", nombreJugador2);
        }
    }
    //FIN AÑADIDO

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
                    movimiento= PART_MOVIMIENTO_ERROR;
            }

            movimiento= nuevo_movimiento(partida, mov_x, mov_y);
            if(movimiento==PART_MOVIMIENTO_ERROR) {
                printf("Opcion incorrecta. Seleccione una de las opciones validas.\n");
            }
        }

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