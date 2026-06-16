#include "Tablero.h"
#include <iostream>
#include <iomanip>

Tablero::Tablero(int f, int c) : filas(f), columnas(c) {
    cuadriculaPlantas.resize(filas, std::vector<std::shared_ptr<Planta>>(columnas, nullptr));
    zombiesPorFila.resize(filas);
}

int Tablero::getFilas() const { return filas; }
int Tablero::getColumnas() const { return columnas; }

bool Tablero::colocarPlanta(int f, int c, std::shared_ptr<Planta> nuevaPlanta) {
    if (f >= 0 && f < filas && c >= 0 && c < columnas - 1) { // No colocar en la columna de spawn
        if (!cuadriculaPlantas[f][c]) {
            cuadriculaPlantas[f][c] = nuevaPlanta;
            return true;
        }
    }
    return false;
}

bool Tablero::eliminarPlanta(int f, int c) {
    if (f >= 0 && f < filas && c >= 0 && c < columnas) {
        if (cuadriculaPlantas[f][c]) {
            cuadriculaPlantas[f][c] = nullptr;
            return true;
        }
    }
    return false;
}

void Tablero::agregarZombie(int f, std::shared_ptr<Zombie> nuevoZombie) {
    if (f >= 0 && f < filas) {
        zombiesPorFila[f].push_back(nuevoZombie);
    }
}

bool Tablero::hayZombiesActivos() const {
    for (int i = 0; i < filas; ++i) {
        if (!zombiesPorFila[i].empty()) return true;
    }
    return false;
}

void Tablero::actualizarEntidadesYTurno(int& solesJugador, int& hpCasa, int& eliminados) {
    // REQUISITO: Orden estricto de Turno (Plantas -> Zombies -> Colisiones)

    // 1. Fase de Plantas (Ataques o Generacion pasiva)
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            if (cuadriculaPlantas[f][c]) {
                cuadriculaPlantas[f][c]->actuar(zombiesPorFila[f], solesJugador);
            }
        }
    }

    // Comprobacion y limpieza intermedia de zombies eliminados por disparos
    for (int f = 0; f < filas; ++f) {
        auto& lista = zombiesPorFila[f];
        for (auto it = lista.begin(); it != lista.end(); ) {
            if ((*it)->getHp() <= 0) {
                std::cout << "[ELIMINADO] " << (*it)->getNombre() << " fue derrotado.\n";
                eliminados++;
                it = lista.erase(it);
            } else {
                ++it;
            }
        }
    }

    // 2. Fase de Zombies (Movimiento o Ataque cuerpo a cuerpo)
    for (int f = 0; f < filas; ++f) {
        auto& lista = zombiesPorFila[f];
        for (auto& z : lista) {
            int colActual = z->getPosicionColumna();

            if (colActual == 0) {
                z->atacarCasa(hpCasa);
            } else {
                // Si hay una planta inmediatamente bloqueando la casilla del frente
                if (cuadriculaPlantas[f][colActual - 1]) {
                    std::cout << "[COMBATE] " << z->getNombre() << " muerde continuamente a la planta del frente.\n";
                    *cuadriculaPlantas[f][colActual - 1] -= z->getDanio(); // Planta recibe danio

                    if (cuadriculaPlantas[f][colActual - 1]->getHp() <= 0) {
                        std::cout << "[INFO] La planta en Fila " << f << ", Col " << (colActual - 1) << " fue comida.\n";
                        cuadriculaPlantas[f][colActual - 1] = nullptr;
                    }
                } else {
                    z->mover(); // Avanza si el paso esta completamente libre
                }
            }
        }
    }
}

void Tablero::mostrar() const {
    std::cout << "\n==================== MAPA DEL JARDIN (ASCII) ====================\n";
    for (int f = 0; f < filas; ++f) {
        std::cout << "Fila " << f << " | ";
        for (int c = 0; c < columnas; ++c) {
            bool zombieDibujado = false;
            // Buscar si existe algun zombie vivo en esta coordenada exacta
            for (const auto& z : zombiesPorFila[f]) {
                if (z->getPosicionColumna() == c) {
                    std::cout << std::setw(7) << *z << " "; // Usa sobrecarga << de Zombie
                    zombieDibujado = true;
                    break;
                }
            }
            if (!zombieDibujado) {
                if (cuadriculaPlantas[f][c]) {
                    std::cout << std::setw(7) << *cuadriculaPlantas[f][c] << " "; // Usa sobrecarga << de Planta
                } else {
                    std::cout << std::setw(7) << "[ . ]" << " ";
                }
            }
        }
        std::cout << "|\n";
    }
    std::cout << "==============================================================\n";
}


