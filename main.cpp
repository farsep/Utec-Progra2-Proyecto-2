#include "Juego.h"
#include <ctime>
#include <cstdlib>

int main() {
    // Inicializacion del motor de aleatoriedad para las coordenadas de los enemigos, lo basico
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Instanciacion unica del objeto de control principal (Requisito de main limpio)
    Juego controlDefensaJardin;

    // Ejecucion ciclica condicionada al estado de terminacion del menu
    while (controlDefensaJardin.estaActivo()) {
        controlDefensaJardin.mostrarMenuPrincipal();
    }

    return 0;
}
