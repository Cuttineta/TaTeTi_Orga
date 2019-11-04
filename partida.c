#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partida.h"

/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){
    *p= (tPartida) malloc(sizeof(struct partida));
    if((*p)==NULL){
        exit(PART_ERROR_MEMORIA);
    }

    //INICIALIZO LA MATRIZ
    tTablero nuevoTablero= (tTablero)malloc(sizeof(struct tablero));
    if(nuevoTablero==NULL){
        exit(PART_ERROR_MEMORIA);
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) {
            nuevoTablero->grilla[i][j]= 0;
        }
    }

    (*p)->modo_partida= modo_partida;
    (*p)->turno_de= comienza;
    (*p)->estado= PART_EN_JUEGO;
    (*p)->tablero= nuevoTablero;
    strcpy((*p)->nombre_jugador_1, j1_nombre);
    strcpy((*p)->nombre_jugador_2, j2_nombre);
}

/**
 * Se encarga de recorrer el tablero y verificar si alguno de los jugadores correspondientes a ganado la partida,
 * actualizando a su vez el estado de la partida.
 */
void checkearGanador(tPartida p){
    int objetivoJugador1= 1;//Este resultado se dara en el caso de que gane el jugador1
    int objetivoJugador2= 8;//Este resultado se dara en el caso de que gane el jugador2
    int espaciosDisponibles= 0;//Indica si todavia hay espacion disponibles para jugar en el tablero
    int ganador= 0;//Flag para indicar al ganador
    int estadoPartida= PART_EN_JUEGO;
    tTablero tableroActual= p->tablero;

    int aux_d1= 1; int aux_d2= 1;
    for(int i=0; i<3 && ganador==0; i++){
        int aux_i= 1; int aux_j= 1;
        aux_d1 *= tableroActual->grilla[i][i];  //Calcula la diagonal (0,0) (1,1) (2,2)
        aux_d2 *= tableroActual->grilla[i][2-i];//Calcula la diagonal (0,2) (1,1) (2,0)

        for(int j=0; j<3; j++){
            aux_i *= tableroActual->grilla[i][j];
            aux_j *= tableroActual->grilla[j][i];
        }

        if(aux_i== objetivoJugador1 || aux_j== objetivoJugador1){//Si gano el jugador 1
           ganador= 1;
        }
        else if(aux_i== objetivoJugador2 || aux_j== objetivoJugador2){//Si gano el jugador 2
            ganador= 2;
        }
        else if(aux_i==espaciosDisponibles || aux_j==espaciosDisponibles){//Si todavia hay casillas disponibles
            estadoPartida= PART_EN_JUEGO;
        }
        else{//Si las filas y columnas estan llenas y ningun jugador gano todavia
            estadoPartida= PART_EMPATE;
        }

    }
    if(aux_d1==objetivoJugador1 || aux_d2==objetivoJugador1){
        ganador= 1;
    }
    else if(aux_d1==objetivoJugador2 || aux_d2==objetivoJugador2){
        ganador= 2;
    }

    if(ganador!=0){//Si gano algun jugador
        p->estado= (ganador==1) ? PART_GANA_JUGADOR_1 : PART_GANA_JUGADOR_2;
    }
    else{//Si no gano ningun jugador
        p->estado= estadoPartida;
        p->turno_de= (p->turno_de==PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;//Cambio el turno del jugador
    }
}

/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    int estado_movimiento;
    tTablero tableroActual= p->tablero;

    if( !(mov_x<3 && mov_x>=0) || !(mov_y<3 && mov_y>=0) ){//Si el movimiento seleccionado no corresponde a una celda existente
        estado_movimiento= PART_MOVIMIENTO_ERROR;
    }
    else if(tableroActual->grilla[mov_x][mov_y]!= 0){//Si la casilla seleccionada ya posee una ficha
        estado_movimiento= PART_MOVIMIENTO_ERROR;
    }
    else{//En caso de que el movimiento seleccionado sea valido
        estado_movimiento= PART_MOVIMIENTO_OK;
        tableroActual->grilla[mov_x][mov_y]= (p->turno_de==PART_JUGADOR_1) ? 1 : 2;//1 en caso de que sea el jugador1, 2 en caso contrario
        checkearGanador(p);
    }

    return estado_movimiento;
}

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
void finalizar_partida(tPartida * p){
    free( (*p)->tablero);
    (*p)->tablero= NULL;
    free(*p);
    (p)= NULL;
}
