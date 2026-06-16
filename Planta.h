#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

// Declaracion adelantada para evitar dependencias circulares
class Zombie;

class Planta {
protected:
    std::string nombre;
    int hp;
    int costoSoles;
    int danio;
public:
    Planta(std::string nom, int vida, int costo, int dmg);
    virtual ~Planta() = default;

    std::string getNombre() const;
    int getCostoSoles() const;
    int getHp() const;

    // Metodo polimorfrico puro para la accion del turno, lo basico nomas
    virtual void actuar(std::vector<std::shared_ptr<Zombie>>& enemigosEnFila, int& solesJugador) = 0;

    // Sobrecarga del operador -= para recibir danio (Requisito Tecnico)
    void operator-=(int cantidad);

    // Sobrecarga del operador << para imprimir informacion de la planta en formato ASCII (Requisito Tecnico)
    friend std::ostream& operator<<(std::ostream& os, const Planta& p);
};

// --- Subclase 1: Girasol ---
class Girasol : public Planta {
private:
    int turnosParaSoles;
    int contadorTurnos;
public:
    Girasol();
    void actuar(std::vector<std::shared_ptr<Zombie>>& enemigosEnFila, int& solesJugador) override;
};

// --- Subclase 2: Lanzaguisantes ---
class Lanzaguisantes : public Planta {
public:
    Lanzaguisantes();
    void actuar(std::vector<std::shared_ptr<Zombie>>& enemigosEnFila, int& solesJugador) override;
};

// --- Subclase 3: Cactus ---
class Cactus : public Planta {
public:
    Cactus();
    void actuar(std::vector<std::shared_ptr<Zombie>>& enemigosEnFila, int& solesJugador) override;
};

#endif


