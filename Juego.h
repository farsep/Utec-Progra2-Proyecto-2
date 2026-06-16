#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include <string>
#include <iostream>

// Estructura auxiliar para guardar la informacion del Historial
struct Partida {
    std::string fecha;
    std::string nombreJugador;
    int oleadasCompletadas;
    int zombisEliminados;
    int solesRecolectados;
    int danioRecibidoCasa;
    int puntosFinales;

    // REQUISITO DE SOBRECARGA: operator<< para exportar datos del Historial
    friend std::ostream& operator<<(std::ostream& os, const Partida& p);
};

class Juego {
private:
    int soles;
    int hpCasa;
    int oleadaActual;
    int totalOleadas;
    int zombisEliminadosPartida;
    int solesTotalesRecolectados;
    bool juegoActivo;
    std::string nombreJugador;
    Tablero tablero;

    void lanzarNuevaOleada();
    void menuEstrategia();
    void cicloTurnosOleada();
    void guardarEstadisticas();

public:
    Juego();
    void mostrarMenuPrincipal();
    bool estaActivo() const;

    // REQUISITO DE SOBRECARGA EXTRA: aniade bonos directamente al contador de soles
    void operator+=(int solesBonus);
};

#endif



