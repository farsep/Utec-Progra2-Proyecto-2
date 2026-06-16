#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include <iostream>

class Zombie {
protected:
    std::string nombre;
    int hp;
    int danio;
    int velocidad;
    int contadorPasos;
    int posicionColumna;
public:
    Zombie(std::string nom, int vida, int dmg, int vel, int colInicial);
    virtual ~Zombie() = default;

    std::string getNombre() const;
    int getHp() const;
    int getDanio() const;
    int getPosicionColumna() const;
    void setPosicionColumna(int col);

    virtual void mover();
    virtual void atacarCasa(int& hpCasa);
    virtual void recibirDanio(int cantidad);

    // Sobrecarga del operador -= para danios (Requisito Tecnico)
    void operator-=(int cantidad);

    // Sobrecarga del operador << para impresion en consola (Requisito Tecnico)
    friend std::ostream& operator<<(std::ostream& os, const Zombie& z);
};

// --- Subclase 1: Zombie Basico ---
class ZombieBasico : public Zombie {
public:
    ZombieBasico(int colInicial);
};

// --- Subclase 2: Zombie con Casco (Habilidad pasiva de Armadura) ---
class ZombieCasco : public Zombie {
private:
    int ataquesProtegidos;
public:
    ZombieCasco(int colInicial);
    void recibirDanio(int cantidad) override; // Comportamiento polimorfrico
};

// --- Subclase 3: Zombie Rapido (Habilidad de Agilidad) ---
class ZombieRapido : public Zombie {
private:
    int turnosContados;
public:
    ZombieRapido(int colInicial);
    void mover() override; // Comportamiento polimorfrico
};

#endif


