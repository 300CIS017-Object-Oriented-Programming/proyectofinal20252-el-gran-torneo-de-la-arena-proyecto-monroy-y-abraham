//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Arena.h"

#include "Arena.h"
#include "ObjetoGenerico.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// Lectura segura de enteros
int leerIntArena() {
    string linea;
    while (true) {
        std::getline(cin, linea);
        if (linea.empty()) continue;
        try {
            return std::stoi(linea);
        } catch (...) {
            return -1;
        }
    }
}

// Constructor
Arena::Arena(Guild* guild, Inventario* inv) {
    this->guild = guild;
    this->inventario = inv;
    turnoActual = 0;
    objetosUsadosTotal = 0;
    combateActivo = false;
    equipoGanador = "";
}

// Destructor
Arena::~Arena() {
    for (size_t i = 0; i < enemigos.size(); i++) {
        delete enemigos[i];
    }
    enemigos.clear();
}

// Configuración de enemigos
void Arena::inicializarEnemigos() {
    cout << "\n=== GENERACION DE OPONENTES ===\n";

    cout << "¿Cuantos enemigos desea enfrentar? (1-6): ";
    int numEnemigos = leerIntArena();
    if (numEnemigos < 1) numEnemigos = 1;
    if (numEnemigos > 6) numEnemigos = 6;

    cout << "\nSeleccione la dificultad:\n";
    cout << " 1. Facil\n";
    cout << " 2. Normal\n";
    cout << " 3. Dificil\n";
    cout << "Opcion: ";

    int dificultad = leerIntArena();

    int nivelMin = 1;
    float multiplicadorStats = 1.0f;

    switch (dificultad) {
        case 1:
            nivelMin = 1;
            multiplicadorStats = 0.8f;
            break;
        case 2:
            nivelMin = 3;
            multiplicadorStats = 1.0f;
            break;
        case 3:
            nivelMin = 5;
            multiplicadorStats = 1.3f;
            break;
        default:
            nivelMin = 3;
            multiplicadorStats = 1.0f;
            break;
    }

    cout << "\n[INFO] Generando " << numEnemigos << " oponentes...\n\n";

    string roles[]   = {"Guerrero", "Mago", "Sanador"};
    string nombres[] = {"Goblin", "Orco", "Esqueleto", "Bandido", "Lobo"};

    for (int i = 0; i < numEnemigos; i++) {
        string nombre = nombres[std::rand() % 5] + " " + std::to_string(i + 1);
        string rol    = roles[std::rand() % 3];

        int nivel   = nivelMin + (std::rand() % 3);
        int vida    = static_cast<int>((60 + nivel * 12) * multiplicadorStats);
        int ataque  = static_cast<int>((18 + nivel * 3)  * multiplicadorStats);
        int defensa = static_cast<int>((12 + nivel * 2)  * multiplicadorStats);

        Oponente* enemigo = new Oponente(nombre, nivel, vida, ataque, defensa, rol);

        if (std::rand() % 100 < 50) {
            asignarObjetoAleatorioAEnemigo(enemigo);
        }

        enemigos.push_back(enemigo);
        cout << " [ENEMIGO] " << nombre << " (" << rol << ") - Nivel " << nivel << endl;
    }

    cout << "\n[OK] Enemigos listos para el combate.\n";
}

void Arena::asignarObjetoAleatorioAEnemigo(Oponente* enemigo) {
    ObjetoMagico* pocion = new ObjetoGenerico(
        "Pocion Oscura", "Restaura salud", 1, "curacion", 30, 50, 0
    );
    enemigo->agregarObjeto(pocion);
}

bool Arena::deberiaUsarObjeto(Personaje* p, ObjetoMagico* o) {
    if (!o || o->fueUsado()) return false;
    if (o->getTipo() == "curacion" && p->getVida() < p->getVidaMaxima() / 2) return true;
    return false;
}

// Preparar combate: mostrar héroes y equipar objetos
void Arena::prepararCombate() {
    cout << "\n=== PREPARACION DEL COMBATE ===\n\n";

    cout << "[INFO] TUS HEROES:\n";
    auto todosHeroes = guild->getHeroes();
    int contador = 1;
    for (auto& par : todosHeroes) {
        Personaje* h = par.second;
        if (h->estaVivo()) {
            cout << " " << contador++ << ". " << h->getNombre()
                 << " (" << h->getRol() << ") - NV " << h->getNivel() << endl;
        }
    }

    cout << "\n¿Equipar objetos de forma aleatoria? (s/n): ";
    string r;
    std::getline(cin, r);

    if (r == "s" || r == "S") {
        asignarObjetosAleatoriosAHeroes();
    } else {
        cout << "\nEquipamiento manual...\n";
        distribuirObjetos();
    }

    cout << "\n[OK] Todo listo. Presiona ENTER para empezar la batalla...";
    cin.get();

}

