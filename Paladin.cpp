//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Paladin.h"
#include <iostream>
#include <limits>

using std::cout;
using std::endl;
using std::cin;
using std::vector;

Paladin::Paladin(string nombre, int nivel)
    : Personaje(nombre, nivel,
                130 + nivel * 12,     // vida
                22 + nivel * 2,       // ataque
                25 + nivel * 2,       // defensa
                "Paladin") {

    defensaExtra = 5 + nivel;
    danioSagrado = 3 + nivel;

    energiaMaxima = 100;
    energiaSacra = 50; // inicia a la mitad
}

Paladin::~Paladin() {}

void Paladin::plegaria() {
    int rec = 30;
    energiaSacra += rec;
    if (energiaSacra > energiaMaxima) energiaSacra = energiaMaxima;

    cout << "   [FE] " << nombre
         << " reza y recupera " << rec << " de energia sacra.\n";
}

int Paladin::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;
    return ataqueDefensivo(objetivo);
}

int Paladin::ataqueDefensivo(Personaje* objetivo) {
    cout << "   [ATK] " << nombre
         << " golpea con justicia a " << objetivo->getNombre() << ".\n";

    int danio = calcularDanioBase(objetivo) + danioSagrado;
    if (danio < 0) danio = 0;

    cout << "   [DANIO] " << danio << " puntos.\n";
    objetivo->recibirDanio(danio);

    // Recupera energia sacra al combatir
    energiaSacra += 10;
    if (energiaSacra > energiaMaxima) energiaSacra = energiaMaxima;

    cout << "   [FE] +10 Energía Sacra por combatir.\n";

    return danio;
}

void Paladin::bendicionDivina() {
    cout << "   [LUZ] " << nombre
         << " invoca una Bendicion Divina.\n";

    int curacion = 25 + nivel * 5;
    curar(curacion);

    aplicarEfecto("defensa", 10, 2);

    energiaSacra -= 40;
    if (energiaSacra < 0) energiaSacra = 0;
}

void Paladin::realizarAccion(vector<Personaje*>& aliados,
                             vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Paladín) --\n";
    cout << "Vida: " << vida << "\n";
    cout << "Energía Sacra: " << energiaSacra
         << "/" << energiaMaxima << "\n\n";

    cout << "1. Martillo Sagrado (+10 Energia)\n";
    cout << "2. Bendición Divina (40 Energia)\n";
    cout << "3. Plegaria (+30 Energia)\n";
    cout << "4. Usar Objeto\n";
    cout << "Elige opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opcion) {

        // --- ATAQUE ---
        case 1: {
            cout << "\n--- Selecciona enemigo ---\n";
            for (int i = 0; i < (int)enemigos.size(); i++) {
                cout << i + 1 << ". " << enemigos[i]->getNombre()
                     << " (Vida: " << enemigos[i]->getVida() << ")\n";
            }
            int idx;
            cout << "Número: ";
            cin >> idx;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (idx < 1 || idx > (int)enemigos.size()) idx = 1;

            atacar(enemigos[idx - 1]);
            break;
        }

        // --- BENDICION DIVINA ---
        case 2:
            if (energiaSacra >= 40) bendicionDivina();
            else cout << "   [FE BAJA] No tienes suficiente energia.\n";
            break;

        // --- PLEGARIA ---
        case 3:
            plegaria();
            break;

        // --- OBJETOS ---
        case 4:
            if (!objetosEquipados.empty()) usarObjeto(0);
            else cout << "   [INFO] No tienes objetos.\n";
            break;

        // --- ERROR ---
        default:
            cout << "   [INFO] Opcion invalida.\n";
            break;
    }
}