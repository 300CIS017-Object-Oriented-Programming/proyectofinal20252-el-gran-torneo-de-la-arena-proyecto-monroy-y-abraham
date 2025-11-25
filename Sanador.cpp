//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Sanador.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;
using std::vector;

Sanador::Sanador(string nombre, int nivel)
    : Personaje(nombre, nivel,
                90 + nivel * 9,
                12 + nivel,
                15 + nivel,
                "Sanador") {

    curacionBase = 25 + nivel * 3;
    efectividadMin = 70;
    efectividadMax = 120;

    manaMaximo = 100;
    mana = manaMaximo;
}

Sanador::~Sanador() {}

int Sanador::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;

    cout << "   [ATK] " << nombre << " roba esencia.\n";

    int danio = calcularDanioBase(objetivo) / 2;
    if (danio < 5) danio = 5;

    cout << "   [DANO] " << danio << " puntos.\n";
    objetivo->recibirDanio(danio);

    mana += 20;
    if (mana > manaMaximo) mana = manaMaximo;

    cout << "   [MANA] Recuperas 20.\n";

    return danio;
}

int Sanador::curarAliado(Personaje* aliado) {
    if (!aliado || !aliado->estaVivo()) return 0;

    int porc = efectividadMin + (rand() % (efectividadMax - efectividadMin + 1));
    int cantidad = curacionBase * porc / 100;

    cout << "   [CURACION] " << nombre << " cura a " << aliado->getNombre()
         << " por " << cantidad << ".\n";

    aliado->curar(cantidad);
    return cantidad;
}

void Sanador::realizarAccion(vector<Personaje*>& aliados,
                             vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Sanador) --\n";
    cout << "Vida: " << vida << "\n";
    cout << "Mana: " << mana << "/" << manaMaximo << "\n\n";

    cout << "1. Ataque drenante (+20 mana)\n";
    cout << "2. Curar aliado (30 mana)\n";
    cout << "3. Usar objeto\n";
    cout << "Elige opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opcion) {

        // -------------------------
        // ATAQUE
        // -------------------------
        case 1: {
            cout << "\n--- Selecciona enemigo ---\n";

            for (int i = 0; i < (int)enemigos.size(); i++) {
                cout << i + 1 << ". " << enemigos[i]->getNombre()
                     << " (Vida: " << enemigos[i]->getVida() << ")\n";
            }

            int idx;
            cout << "Num: ";
            cin >> idx;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (idx < 1 || idx > (int)enemigos.size()) idx = 1;

            atacar(enemigos[idx - 1]);
            break;
        }

        // -------------------------
        // CURA
        // -------------------------
        case 2: {
            if (mana < 30) {
                cout << "   [INFO] No tienes mana.\n";
                break;
            }

            cout << "\n--- Selecciona aliado ---\n";

            for (int i = 0; i < (int)aliados.size(); i++) {
                cout << i + 1 << ". " << aliados[i]->getNombre()
                     << " (HP: " << aliados[i]->getVida()
                     << "/" << aliados[i]->getVidaMaxima() << ")\n";
            }

            int idx;
            cout << "Num: ";
            cin >> idx;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            mana -= 30;

            if (idx < 1 || idx > (int)aliados.size())
                curarAliado(this);
            else
                curarAliado(aliados[idx - 1]);

            break;
        }

        // -------------------------
        // OBJETOS
        // -------------------------
        case 3:
            if (!objetosEquipados.empty()) usarObjeto(0);
            else cout << "   [INFO] No tienes objetos.\n";
            break;

        default:
            cout << "   [INFO] Opcion no valida.\n";
            break;
    }
}
