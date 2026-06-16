#include "Juego.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

std::ostream& operator<<(std::ostream& os, const Partida& p) {
    os << "Fecha: " << p.fecha << " | Jugador: " << p.nombreJugador
       << " | Oleadas: " << p.oleadasCompletadas << "/3"
       << " | Derrotados: " << p.zombisEliminados
       << " | Soles Totales: " << p.solesRecolectados
       << " | Dmg Casa: " << p.danioRecibidoCasa
       << " | Score: " << p.puntosFinales;
    return os;
}

Juego::Juego() : soles(150), hpCasa(100), oleadaActual(1), totalOleadas(3),
                 zombisEliminadosPartida(0), solesTotalesRecolectados(150),
                 juegoActivo(true), nombreJugador("Invitado"), tablero(5, 9) {}

bool Juego::estaActivo() const { return juegoActivo; }

void Juego::operator+=(int solesBonus) {
    this->soles += solesBonus;
    this->solesTotalesRecolectados += solesBonus;
}

void Juego::mostrarMenuPrincipal() {
    int opcion = 0;
    std::cout << "\n==============================================\n";
    std::cout << "    MENU DE CONTROL: DEFENSA DEL JARDIN\n";
    std::cout << "==============================================\n";
    if (!nombreJugador.empty() && nombreJugador != "Invitado") {
        std::cout << "    Usuario: " << nombreJugador << "\n";
        std::cout << "==============================================\n";
    }
    std::cout << "1. Jugar (Iniciar nueva partida)\n";
    std::cout << "2. Ver estadisticas (Historial en disco)\n";
    std::cout << "3. Salir del Sistema\n";
    std::cout << "Seleccione una opcion: ";

    if (!(std::cin >> opcion)) { // Validacion de entrada segura
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Formato invalido. Reintente.\n";
        return;
    }

    switch (opcion) {
        case 1: {
            std::string alias;
            bool aliasValido = false;
            while (!aliasValido) {
                std::cout << "\nIngrese su alias (sin espacios, maximo 20 caracteres): ";
                std::cin >> alias;

                if (alias.empty() || alias.length() > 20) {
                    std::cout << "Error: El alias debe tener entre 1 y 20 caracteres.\n";
                    continue;
                }

                bool tieneEspacios = false;
                for (char c : alias) {
                    if (c == ' ') {
                        tieneEspacios = true;
                        break;
                    }
                }

                if (tieneEspacios) {
                    std::cout << "Error: El alias no puede contener espacios. Intente nuevamente.\n";
                    continue;
                }

                aliasValido = true;
                nombreJugador = alias;
            }

            soles = 150;
            hpCasa = 100;
            oleadaActual = 1;
            zombisEliminadosPartida = 0;
            solesTotalesRecolectados = 150;
            tablero = Tablero(5, 9);
            lanzarNuevaOleada();
            break;
        }
        case 2: {
            std::ifstream archivo("historial_partidas.txt");
            std::cout << "\n--- REGISTRO HISTORICO DE PARTIDAS ---\n";
            if (!archivo.is_open()) {
                std::cout << "Aviso: No existen partidas registradas en el archivo local.\n";
            } else {
                std::string linea;
                int contador = 1;
                while (std::getline(archivo, linea)) {
                    std::cout << contador++ << ". " << linea << "\n";
                }
                archivo.close();
            }
            break;
        }
        case 3:
            std::cout << "Cerrando programa de defensa. Exito en la exposicion.\n";
            juegoActivo = false;
            break;
        default:
            std::cout << "Codigo numerico incorrecto.\n";
            break;
    }
}

void Juego::menuEstrategia() {
    int opcion = 0;
    while (true) {
        tablero.mostrar();
        std::cout << "\n--- FASE DE PREPARACION DE DEFENSA (Oleada " << oleadaActual << ") ---\n";
        std::cout << "Usuario: " << nombreJugador << " | Soles: " << soles << " | Integridad de la Casa: " << hpCasa << " HP\n";
        std::cout << "-------------------------------------------------------------\n";
        std::cout << "1. Colocar Girasol (50 Soles)\n";
        std::cout << "2. Colocar Lanzaguisantes (100 Soles)\n";
        std::cout << "3. Colocar Cactus (125 Soles)\n";
        std::cout << "4. Eliminar una planta sembrada\n";
        std::cout << "5. Confirmar y comenzar el asalto zombie\n";
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada erronea.\n";
            continue;
        }

        if (opcion == 5) break;

        int f, c;
        if (opcion >= 1 && opcion <= 3) {
            std::cout << "Coordenadas destino (Fila 0-4 y Columna 0-7): ";
            if (!(std::cin >> f >> c)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            std::shared_ptr<Planta> p = nullptr;
            if (opcion == 1) p = std::make_shared<Girasol>();
            else if (opcion == 2) p = std::make_shared<Lanzaguisantes>();
            else if (opcion == 3) p = std::make_shared<Cactus>();

            if (p) {
                if (soles >= p->getCostoSoles()) {
                    if (tablero.colocarPlanta(f, c, p)) {
                        soles -= p->getCostoSoles();
                        std::cout << "Planta sembrada!\n";
                    } else {
                        std::cout << "Celda no disponible o fuera del rango del patio.\n";
                    }
                } else {
                    std::cout << "Cantidad de soles insuficiente.\n";
                }
            }
        } else if (opcion == 4) {
            std::cout << "Coordenadas a remover (Fila 0-4 y Columna 0-7): ";
            if (!(std::cin >> f >> c)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            if (tablero.eliminarPlanta(f, c)) {
                std::cout << "Casilla desocupada con exito.\n";
            } else {
                std::cout << "No hay ninguna planta en esa posicion.\n";
            }
        }
    }
}

void Juego::lanzarNuevaOleada() {
    menuEstrategia();

    int cantidadZombies = oleadaActual * 2;
    std::cout << "\n[ALERTA!] " << nombreJugador << ", la oleada ha comenzado. Spawneando " << cantidadZombies << " zombies...\n";
    std::cout << "Presiona cualquier tecla para comenzar...\n";
    std::cin.ignore();
    std::cin.get();

    for (int i = 0; i < cantidadZombies; ++i) {
        int filaAleatoria = rand() % tablero.getFilas();
        int tipoZombie = rand() % 3;

        std::shared_ptr<Zombie> z = nullptr;
        // Inician el avance desde el extremo derecho del mapa (Columna 8)
        if (tipoZombie == 0) z = std::make_shared<ZombieBasico>(tablero.getColumnas() - 1);
        else if (tipoZombie == 1) z = std::make_shared<ZombieCasco>(tablero.getColumnas() - 1);
        else z = std::make_shared<ZombieRapido>(tablero.getColumnas() - 1);

        tablero.agregarZombie(filaAleatoria, z);
    }

    cicloTurnosOleada();
}

void Juego::cicloTurnosOleada() {
    int turno = 1;
    while (tablero.hayZombiesActivos() && hpCasa > 0) {
        std::cout << "\n>>>>>>>>>>>> SIMULACION DE TURNO NUMERO: " << turno << " <<<<<<<<<<<<\n";
        std::cout << "Usuario: " << nombreJugador << "\n";

        tablero.actualizarEntidadesYTurno(soles, hpCasa, zombisEliminadosPartida);
        tablero.mostrar();

        std::cout << "Usuario: " << nombreJugador << " | Soles: " << soles << " | Vida de la Casa: " << hpCasa << " HP\n";
        std::cout << "Presione [ENTER] para avanzar el turno...";
        std::cin.ignore();
        std::cin.get();
        turno++;
    }

    if (hpCasa <= 0) {
        std::cout << "\n[DERROTA] " << nombreJugador << ", los zombies traspasaron tus defensas. Fin de la partida.\n";
        guardarEstadisticas();
    } else {
        std::cout << "\n[OLEADA COMPLETADA] " << nombreJugador << ", superaste la oleada " << oleadaActual << "!\n";
        if (oleadaActual < totalOleadas) {
            oleadaActual++;
            *this += 75; // Bonificacion de recursos usando operador += sobrecargado
            lanzarNuevaOleada();
        } else {
            std::cout << "\n[VICTORIA ABSOLUTA] " << nombreJugador << ", has defendido la Academia perfectamente!\n";
            guardarEstadisticas();
        }
    }
}

void Juego::guardarEstadisticas() {
    std::time_t t = std::time(nullptr);
    char bufferFecha[100];
    std::strftime(bufferFecha, sizeof(bufferFecha), "%Y-%m-%d %H:%M", std::localtime(&t));

    Partida p;
    p.fecha = std::string(bufferFecha);
    p.nombreJugador = nombreJugador;
    p.oleadasCompletadas = (hpCasa <= 0) ? (oleadaActual - 1) : oleadaActual;
    p.zombisEliminados = zombisEliminadosPartida;
    p.solesRecolectados = solesTotalesRecolectados;
    p.danioRecibidoCasa = 100 - hpCasa;
    p.puntosFinales = (p.oleadasCompletadas * 500) + (p.zombisEliminados * 150);

    std::ofstream archivo("historial_partidas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << p << "\n"; // Llama a la sobrecarga << estructurada
        archivo.close();
        std::cout << "\n--- PARTIDA FINALIZADA ---\n";
        std::cout << "Jugador: " << nombreJugador << "\n";
        std::cout << "Oleadas completadas: " << p.oleadasCompletadas << "/3\n";
        std::cout << "Zombis eliminados: " << p.zombisEliminados << "\n";
        std::cout << "Puntos finales: " << p.puntosFinales << "\n";
        std::cout << "Historial sincronizado en disco duro ('historial_partidas.txt').\n";
    } else {
        std::cout << "Error Critico: No se pudo escribir el archivo de guardado.\n";
    }
}




