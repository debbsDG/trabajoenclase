#ifndef FUTBOL_H
#define FUTBOL_H

// Posición discreta en una cancha tipo matriz
typedef struct { int fila, col; } PosI;

// Jugador básico
typedef struct {
    int id;            // dorsal o índice
    int es_portero;    // 1 si es portero
    int tiene_balon;   // 1 si posee el balón
    PosI pos;          // dónde está parado
} Jugador;

// Equipo con hasta 11 jugadores
#define MAX_JUG 11
typedef struct {
    char nombre[32];
    Jugador jug[MAX_JUG];
    int n;             // cuántos realmente usamos
} Equipo;

// Balón: o libre en la cancha o “pegado” a un jugador
typedef struct {
    int en_poder;   // -1 = libre; si no, índice del jugador que lo tiene (demo)
    PosI pos;       // si está libre, su ubicación
} Balon;

// Cancha/partido mínimo: dimensiones, dos equipos y arco como rectángulos
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

    // 2. Inicializar Arcos (Porterías)
    // Asumimos que los arcos tienen 5 unidades de ancho
    int ancho_arco = 5;
    int centro_vertical = alto / 2;
    int inicio_arco_y = centro_vertical - ancho_arco / 2;
    int fin_arco_y = centro_vertical + ancho_arco / 2;

    // Arco A (Equipo A, a la izquierda: columna 0)
    p->arco_A_min.fila = inicio_arco_y;
    p->arco_A_min.col = 0;
    p->arco_A_max.fila = fin_arco_y;
    p->arco_A_max.col = 0; // O 1, dependiendo de cómo definas la línea de gol

    // Arco B (Equipo B, a la derecha: columna 'ancho-1')
    p->arco_B_min.fila = inicio_arco_y;
    p->arco_B_min.col = ancho - 1;
    p->arco_B_max.fila = fin_arco_y;
    p->arco_B_max.col = ancho - 1;

    // 3. Inicializar Balón
    p->balon.en_poder = -1; // Balón libre
    p->balon.pos.fila = centro_vertical;
    p->balon.pos.col = ancho / 2; // Posición de saque (centro del campo)

    // 4. Inicializar Equipos y Jugadores
    
    // --- Equipo A (Juega de izquierda a derecha) ---
    snprintf(p->A.nombre, 32, "Equipo Casa");
    p->A.n = MAX_JUG;
    
    // Posiciones iniciales del Equipo A (Ejemplo simple de formación 4-4-2)
    int fila_centro = alto / 2;
    int zona_defensa = ancho / 4;
    int zona_media = ancho / 2 - ancho / 8;
    int zona_ataque = ancho / 2 - ancho / 16;
    
    // Posición inicial del Jugador (id, es_portero, fila, col)
    
    // 1. Portero (GK)
    inicializar_jugador(&p->A.jug[0], 1, 1, fila_centro, 1); 

    // 2-5. Defensores (DF)
    inicializar_jugador(&p->A.jug[1], 2, 0, alto / 5 * 1, zona_defensa);
    inicializar_jugador(&p->A.jug[2], 3, 0, alto / 5 * 2, zona_defensa);
    inicializar_jugador(&p->A.jug[3], 4, 0, alto / 5 * 3, zona_defensa);
    inicializar_jugador(&p->A.jug[4], 5, 0, alto / 5 * 4, zona_defensa);

    // 6-9. Mediocampistas (MC)
    inicializar_jugador(&p->A.jug[5], 6, 0, alto / 5 * 1, zona_media);
    inicializar_jugador(&p->A.jug[6], 7, 0, alto / 5 * 2, zona_media);
    inicializar_jugador(&p->A.jug[7], 8, 0, alto / 5 * 3, zona_media);
    inicializar_jugador(&p->A.jug[8], 9, 0, alto / 5 * 4, zona_media);
    
    // 10-11. Atacantes (AT)
    inicializar_jugador(&p->A.jug[9], 10, 0, alto / 3 * 1, zona_ataque);
    inicializar_jugador(&p->A.jug[10], 11, 0, alto / 3 * 2, zona_ataque);


    // --- Equipo B (Juega de derecha a izquierda) ---
    snprintf(p->B.nombre, 32, "Equipo Visitante");
    p->B.n = MAX_JUG;
    
    // Las posiciones del Equipo B son simétricas a las del Equipo A
    zona_defensa = ancho - 1 - zona_defensa;
    zona_media = ancho - 1 - zona_media + ancho/16; // ajuste para simetría
    zona_ataque = ancho - 1 - zona_ataque + ancho/8; // ajuste para simetría

    // 1. Portero (GK)
    inicializar_jugador(&p->B.jug[0], 1, 1, fila_centro, ancho - 2); 

    // 2-5. Defensores (DF)
    inicializar_jugador(&p->B.jug[1], 2, 0, alto / 5 * 1, zona_defensa);
    inicializar_jugador(&p->B.jug[2], 3, 0, alto / 5 * 2, zona_defensa);
    inicializar_jugador(&p->B.jug[3], 4, 0, alto / 5 * 3, zona_defensa);
    inicializar_jugador(&p->B.jug[4], 5, 0, alto / 5 * 4, zona_defensa);

    // 6-9. Mediocampistas (MC)
    inicializar_jugador(&p->B.jug[5], 6, 0, alto / 5 * 1, zona_media);
    inicializar_jugador(&p->B.jug[6], 7, 0, alto / 5 * 2, zona_media);
    inicializar_jugador(&p->B.jug[7], 8, 0, alto / 5 * 3, zona_media);
    inicializar_jugador(&p->B.jug[8], 9, 0, alto / 5 * 4, zona_media);
    
    // 10-11. Atacantes (AT)
    inicializar_jugador(&p->B.jug[9], 10, 0, alto / 3 * 1, zona_ataque);
    inicializar_jugador(&p->B.jug[10], 11, 0, alto / 3 * 2, zona_ataque);

    printf("⚽️ Partido inicializado: %s vs %s en campo %d x %d.\n", p->A.nombre, p->B.nombre, p->alto, p->ancho);
}

#endif