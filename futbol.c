#ifndef FUTBOL_H
#define FUTBOL_H

// Posición 
typedef struct { int fila, col; } PosI;

// Jugador 
typedef struct {
    int id;            // índice
    int es_portero;    // 1 si es portero
    int tiene_balon;   // 1 si posee el balón
    PosI pos;          // dónde está
} Jugador;

// 11 jugadores
#define MAX_JUG 11
typedef struct {
    char nombre[32];
    Jugador jug[MAX_JUG];
    int n;             
} Equipo;

// Balón
typedef struct {
    int en_poder;   // -1 = libre; si no, índice del jugador que lo tiene
    PosI pos;       // si está libre, su ubicación
} Balon;

// Cancha arco como rectángulos
typedef struct {
    int alto, ancho;  // filas x columnas
    Equipo A, B;
    Balon balon;
    PosI arco_A_min, arco_A_max;  // rectángulo del arco A (izq)
    PosI arco_B_min, arco_B_max;  // rectángulo del arco B (der)
} Partido;


void inicializar_jugador(Jugador* j, int id, int es_portero, int fila, int col) {
    j->id = id;
    j->es_portero = es_portero;
    j->tiene_balon = 0; // Nadie tiene el balón al inicio
    j->pos.fila = fila;
    j->pos.col = col;
}

void inicializar_partido_simple(Partido* p, int alto, int ancho) {
    // 1. Inicializar Dimensiones del Campo
    p->alto = alto;
    p->ancho = ancho;

#endif
