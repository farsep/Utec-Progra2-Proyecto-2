#include "Zombie.h"

Zombie::Zombie(std::string nom, int vida, int dmg, int vel, int colInicial)
    : nombre(nom), hp(vida), danio(dmg), velocidad(vel), contadorPasos(0), posicionColumna(colInicial) {}

std::string Zombie::getNombre() const { return nombre; }
int Zombie::getHp() const { return hp; }
int Zombie::getDanio() const { return danio; }
int Zombie::getPosicionColumna() const { return posicionColumna; }
void Zombie::setPosicionColumna(int col) { posicionColumna = col; }

void Zombie::mover() {
    contadorPasos++;
    if (contadorPasos >= velocidad && posicionColumna > 0) {
        posicionColumna--;
        std::cout << "[MOVIMIENTO] " << nombre << " avanza a la columna " << posicionColumna << ".\n";
        contadorPasos = 0;
    }
}

void Zombie::atacarCasa(int& hpCasa) {
    std::cout << "[DANIO CASA] " << nombre << " ha alcanzado el final y muerde la estructura (" << danio << " dmg)!\n";
    hpCasa -= danio;
    if (hpCasa < 0) hpCasa = 0;
}

void Zombie::recibirDanio(int cantidad) {
    hp -= cantidad;
    if (hp < 0) hp = 0;
}

void Zombie::operator-=(int cantidad) {
    recibirDanio(cantidad);
}

std::ostream& operator<<(std::ostream& os, const Zombie& z) {
    os << z.nombre[0] << "(" << z.hp << ")";
    return os;
}

// Zombie Basico: Estadisticas estandar de un zombie comun, nada especial
ZombieBasico::ZombieBasico(int colInicial) : Zombie("Zombie Basico", 100, 15, 1, colInicial) {}

// Zombie Casco: Mitiga el 50% de danio en los 3 primeros ataques del jardin, tiene armadura decente
ZombieCasco::ZombieCasco(int colInicial) : Zombie("Zombie Casco", 120, 15, 1, colInicial), ataquesProtegidos(3) {}
void ZombieCasco::recibirDanio(int cantidad) {
    if (ataquesProtegidos > 0) {
        cantidad = cantidad / 2;
        ataquesProtegidos--;
        std::cout << "[PASIVA] La armadura redujo el danio al 50%! Quedan " << ataquesProtegidos << " bloqueos.\n";
    }
    Zombie::recibirDanio(cantidad);
}

// Zombie Rapido: Cada 3 turnos se desplaza una casilla extra mediante su pasiva de agilidad, muy veloz
ZombieRapido::ZombieRapido(int colInicial) : Zombie("Zombie Rapido", 80, 10, 1, colInicial), turnosContados(0) {}
void ZombieRapido::mover() {
    turnosContados++;
    if (posicionColumna > 0) {
        posicionColumna--;
        std::cout << "[MOVIMIENTO] " << nombre << " corre a la columna " << posicionColumna << ".\n";
        if (turnosContados % 3 == 0 && posicionColumna > 0) {
            posicionColumna--;
            std::cout << "[PASIVA AGILIDAD] " << nombre << " obtiene velocidad extra y avanza otra casilla a la col " << posicionColumna << "!\n";
        }
    }
}


