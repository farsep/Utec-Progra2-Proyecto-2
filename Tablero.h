#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <memory>
#include "Planta.h"
#include "Zombie.h"

class Tablero {
private:
    int filas;
    int columnas;
    // Composicion: El tablero posee y destruye las plantas contenidas
    std::vector<std::vector<std::shared_ptr<Planta>>> cuadriculaPlantas;
    // Agregacion: Los zombies se desplazan temporalmente a traves de las filas
    std::vector<std::vector<std::shared_ptr<Zombie>>> zombiesPorFila;

public:
    Tablero(int f = 5, int c = 9);

    int getFilas() const;
    int getColumnas() const;

    bool colocarPlanta(int f, int c, std::shared_ptr<Planta> nuevaPlanta);
    bool eliminarPlanta(int f, int c);
    void agregarZombie(int f, std::shared_ptr<Zombie> nuevoZombie);

    bool hayZombiesActivos() const;

    // Procesa el ciclo secuencial del juego exigido por la rubrica
    void actualizarEntidadesYTurno(int& solesJugador, int& hpCasa, int& eliminados);
    void mostrar() const;
};

#endif


