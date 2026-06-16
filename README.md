# 🌿 Defensa del Jardin - Juego de Estrategia en Consola

## Descripcion General

**Defensa del Jardin** es un juego de estrategia por turnos desarrollado en C++ que combina mecanicas de defensa de torres con elementos de jardineria. El jugador debe colocar plantas estrategicamente para detener oleadas de zombies que avanzan hacia su casa.

El juego implementa conceptos avanzados de Programacion Orientada a Objetos (POO) incluyendo herencia, polimorfismo, sobrecargas de operadores y patrones de composicion y agregacion.

---

## 🎮 Caracteristicas Principales

### Mecanica de Juego
- **Sistema de turnos**: Orden estricto de ejecucion (Plantas → Zombies → Colisiones)
- **Mapa ASCII interactivo**: Cuadicula 5x9 visualizable en consola
- **3 Oleadas progresivas** con dificultad creciente
- **Sistema de recursos**: Soles que se generan automaticamente y se usan para plantar
- **Guardado de estadisticas**: Historial persistente de partidas

### Plantas Disponibles
1. **🌻 Girasol** (50 soles)
   - Habilidad pasiva: Genera 25 soles cada 2 turnos
   - HP: 60 | Danio: 0

2. **🌿 Lanzaguisantes** (100 soles)
   - Habilidad activa: Dispara 20 de danio al primer zombie
   - HP: 100 | Danio: 20

3. **🌵 Cactus** (125 soles)
   - Habilidad activa: Lanza espinas infligiendo 15 de danio
   - HP: 150 | Danio: 15

### Enemigos (Zombies)
1. **🧟 Zombie Basico**
   - Estadisticas: HP 100, Danio 15, Velocidad 1
   - Comportamiento estandar

2. **🧱 Zombie Casco**
   - Estadisticas: HP 120, Danio 15, Velocidad 1
   - Habilidad pasiva: Reduce 50% de danio en los 3 primeros ataques

3. **⚡ Zombie Rapido**
   - Estadisticas: HP 80, Danio 10, Velocidad 1
   - Habilidad pasiva: Cada 3 turnos obtiene un turno adicional de movimiento

---

## 📋 Requisitos

### Software
- **C++17 o superior**
- **CMake 3.10+** (para compilacion)
- **Compilador**: GCC, Clang o MSVC compatible con C++17

### Sistema Operativo
- Windows (PowerShell o CMD)
- Linux (Bash)
- macOS (Bash)

---

## 📁 Estructura del Proyecto

```
Proyecto 2/
├── README.md                    # Este archivo
├── CMakeLists.txt              # Configuracion de compilacion
├── main.cpp                    # Punto de entrada (limpio de logica)
├── Planta.h / Planta.cpp       # Clase base + 3 subclases (Girasol, Lanzaguisantes, Cactus)
├── Zombie.h / Zombie.cpp       # Clase base + 3 subclases (Basico, Casco, Rapido)
├── Tablero.h / Tablero.cpp     # Gestión del mapa y ciclos de turno
├── Juego.h / Juego.cpp         # Controlador principal y logica de juego
├── historial_partidas.txt      # Archivo de estadisticas (auto-generado)
└── cmake-build-debug/          # Directorio de compilacion
```

---

## 🚀 Instrucciones de Compilacion y Ejecucion

### En Windows (PowerShell)

```powershell
# Navegar al directorio del proyecto
cd "C:\Users\farid\Coding\UTEC\PROGRAMACION 2\Proyecto 2"

# Crear directorio de compilacion (si no existe)
mkdir cmake-build-debug
cd cmake-build-debug

# Configurar y compilar
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug

# Ejecutar
.\Debug\Proyecto_2.exe
```

### En Linux/macOS (Bash)

```bash
# Navegar al directorio del proyecto
cd "Proyecto 2"

# Crear directorio de compilacion
mkdir -p cmake-build-debug
cd cmake-build-debug

# Configurar y compilar
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Ejecutar
./Proyecto_2
```

---

## 🎯 Como Jugar

### Menu Principal
1. **Jugar** - Inicia una nueva partida
   - Se solicita un alias (sin espacios, maximo 20 caracteres)
   
2. **Ver estadisticas** - Muestra el historial de todas las partidas guardadas
   
3. **Salir** - Cierra el programa

### Fase de Preparacion (Antes de cada oleada)
Antes de que los zombies ataquen, tienes tiempo para colocar o eliminar plantas:
- **Opcion 1-3**: Coloca plantas (si tienes soles suficientes)
- **Opcion 4**: Elimina una planta ya colocada
- **Opcion 5**: Confirma y comienza la oleada

### Durante la Oleada
- Las plantas actuan primero (disparan, generan soles)
- Los zombies se mueven hacia la casa o atacan plantas
- Si un zombie llega a la columna 0, dania la casa
- El juego termina cuando:
  - **Victoria**: Completas todas las oleadas sin que la casa sea destruida (HP > 0)
  - **Derrota**: La casa llega a 0 HP

---

## 💻 Requisitos Tecnicos Implementados

### Programacion Orientada a Objetos (POO)
✅ **Herencia**: Clases base (`Planta`, `Zombie`) con subclases especializadas
✅ **Polimorfismo**: Metodos virtuales (`actuar()`, `mover()`, `recibirDanio()`)
✅ **Encapsulacion**: Atributos `private`, `protected`, `public` bien definidos
✅ **Constructores/Destructores**: Inicialiacion y limpieza adecuadas

### Estructuras de Datos
✅ **Vectores dinamicos**: `std::vector<>` para filas y columnas
✅ **Matrices**: `std::vector<std::vector<>>` para el tablero
✅ **Punteros inteligentes**: `std::shared_ptr<>` para evitar fugas de memoria

### Relaciones entre Clases
✅ **Composicion**: Tablero posee las plantas (ciclo de vida ligado)
✅ **Agregacion**: Tablero contiene los zombies (ciclo de vida independiente)
✅ **Asociacion**: Juego usa Tablero para gestionar el mapa

### Sobrecargas de Operadores
✅ `operator<<` - Imprime informacion legible de Planta, Zombie y Partida
✅ `operator-=` - Aplica danio a plantas y zombies
✅ `operator+=` - Aniade bonificaciones de soles

### Persistencia de Datos
✅ **Lectura/Escritura**: Archivos de texto con `std::ifstream` y `std::ofstream`
✅ **Formato estructurado**: Historial con fecha, jugador, oleadas, danio, puntos

---

## 📊 Mecanica de Turnos

Cada turno sigue este orden estricto:

1. **Fase de Plantas**
   - Cada planta ejecuta su metodo `actuar()`
   - Pueden disparar, generar soles, activar habilidades pasivas

2. **Limpieza de Zombies**
   - Se eliminan zombies con HP <= 0
   - Se incrementa el contador de zombies derrotados

3. **Fase de Zombies**
   - Cada zombie intenta moverse o atacar
   - Si hay planta en el frente, la muerde
   - Si no hay obstaculo, avanza

4. **Comprobacion de Condiciones**
   - Si hay zombies activos y HP casa > 0, continua siguiente turno
   - Si no hay zombies y no es ultima oleada, pasa a siguiente oleada
   - Si es ultima oleada sin zombies, VICTORIA
   - Si HP casa <= 0, DERROTA

---

## 📈 Sistema de Puntuacion

**Puntos finales = (Oleadas completadas × 500) + (Zombies eliminados × 150)**

### Recursos
- **Soles iniciales**: 150 por partida
- **Generacion**: Girasoles producen 25 soles cada 2 turnos
- **Bonificacion oleada**: +75 soles al completar una oleada

---

## 🔧 Validaciones de Entrada

- Alias sin espacios (1-20 caracteres)
- Coordenadas dentro del rango del tablero
- Suficientes soles para colocar plantas
- Opciones de menu solo numeros validos

---

## 📝 Formato del Historial

Cada linea del archivo `historial_partidas.txt` contiene:

```
Fecha: YYYY-MM-DD HH:MM | Jugador: alias | Oleadas: X/3 | Derrotados: N | Soles Totales: M | Dmg Casa: D | Score: S
```

Ejemplo:
```
Fecha: 2026-06-16 14:23 | Jugador: FaridGamer | Oleadas: 3/3 | Derrotados: 18 | Soles Totales: 550 | Dmg Casa: 0 | Score: 4200
```

---

## 🎓 Conceptos Educativos

Este proyecto demuestra:
- **Patrones de diseño**: Composicion, agregacion, asociacion
- **Control de flujo de juego**: Ciclos por turnos sincronizados
- **Manejo de memoria**: Punteros inteligentes y RAII
- **Validacion de entrada**: Manejo de errores de usuario
- **Persistencia**: Guardado y lectura de datos

---

## 🐛 Notas Tecnicas

- El tablero es de 5 filas × 9 columnas (configurable en `Juego.cpp`)
- Los zombies aparecen en la columna 8 (extremo derecho)
- La casa esta en la columna 0 (extremo izquierdo)
- Las plantas no se pueden colocar en la columna 8 (columna de spawn)
- El orden de ejecucion de turnos es critico para la balanza del juego

---

## 📝 Autores

Proyecto: **Defensa del Jardin**
Curso: **Programacion II - Laboratorio**
Institucion: **Universidad de Tecnologia y Comercio (UTEC)**
Semestre: **2026-1**

---

## 📄 Licencia

Este proyecto es de propositos educativos.

---

## 💡 Consejos de Estrategia

1. **Comienza con Girasoles** para generar soles adicionales rapidamente
2. **Coloca Cactus** en puntos estrategicos para defenderte temprano
3. **Usa Lanzaguisantes** para atacar zombies de larga distancia
4. **Planifica la oleada siguiente** mientras luchas contra la actual
5. **Prioriza la defensa** sobre generar soles en oleadas avanzadas


