#include "Planta.h"
#include "Zombie.h"

Planta::Planta(std::string nom, int vida, int costo, int dmg)
    : nombre(nom), hp(vida), costoSoles(costo), danio(dmg) {}

std::string Planta::getNombre() const { return nombre; }
int Planta::getCostoSoles() const { return costoSoles; }
int Planta::getHp() const { return hp; }

void Planta::operator-=(int cantidad) {
    this->hp -= cantidad;
    if (this->hp < 0) this->hp = 0;
}

std::ostream& operator<<(std::ostream& os, const Planta& p) {
    // Retorna la inicial y su vida actual (Ejemplo: G(60))
    os << p.nombre[0] << "(" << p.hp << ")";
    return os;
}

// Implementacion Girasol (Habilidad Pasiva: Generar Soles cada 2 turnos)
Girasol::Girasol() : Planta("Girasol", 60, 50, 0), turnosParaSoles(2), contadorTurnos(0) {}
void Girasol::actuar(std::vector<std::shared_ptr<Zombie>>& enemigosEnFila, int& solesJugador) {
    contadorTurnos++;
    if (contadorTurnos >= turnosParaSoles) {
        solesJugador += 25;
        std::cout << "[PASIVA] Girasol genero 25 soles de forma automatica!\n";
        contadorTurnos = 0;
    }
}

// Implementacion Lanzaguisantes (Habilidad Activa: Atacar en fila por turno)
Lanzaguisantes::Lanzaguisantes() : Planta("Lanzaguisantes", 100, 100, 20) {}
void Lanzaguisantes::actuar(std::vector<std::shared_ptr<Zombie>>& enemigosEnFila, int& solesJugador) {
    if (!enemigosEnFila.empty()) {
        std::cout << "[ACCION] Lanzaguisantes dispara al primer zombie en la fila e inflige " << danio << " de danio.\n";
        *enemigosEnFila.front() -= danio; // Usa la sobrecarga del operador -= de Zombie
    }
}

// Implementacion Cactus (Planta Defensiva/Ataque con mas HP)
Cactus::Cactus() : Planta("Cactus", 150, 125, 15) {}
void Cactus::actuar(std::vector<std::shared_ptr<Zombie>>& enemigosEnFila, int& solesJugador) {
    if (!enemigosEnFila.empty()) {
        std::cout << "[ACCION] Cactus lanza espinas e inflige " << danio << " de danio.\n";
        *enemigosEnFila.front() -= danio;
    }
}


