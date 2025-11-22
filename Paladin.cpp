//
// Created by Jesus Esteban Monroy on 21/11/2025.
//
#include "Paladin.h"
#include <iostream>
#include <limits>
#include "ObjetoMagico.h"

using namespace std;

Paladin::Paladin(string nombre, int nivel)
    : Personaje(nombre, nivel, 130 + (nivel * 12), 22 + (nivel * 2), 25 + (nivel * 2), "Paladin") {
    this->defensaExtra = 5 + nivel;
    this->danioSagrado = 3 + nivel;

    // Sistema de Energia Sacra
    this->energiaMaxima = 100;
    this->energiaSacra = 50; // Empieza a la mitad
}

Paladin::~Paladin() {}

void Paladin::plegaria() {
    int rec = 30;
    energiaSacra += rec;
    if (energiaSacra > energiaMaxima) energiaSacra = energiaMaxima;
    cout << "   [FE] " << nombre << " reza y recupera " << rec << " de energia sacra." << endl;
}

int Paladin::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;
    return ataqueDefensivo(objetivo);
}

int Paladin::ataqueDefensivo(Personaje* objetivo) {
    cout << "   [ATK] " << nombre << " golpea con justicia a " << objetivo->getNombre() << endl;

    int danio = calcularDanioBase(objetivo) + danioSagrado;
    if (danio < 0) danio = 0;

    cout << "   [DANIO] " << danio << " puntos." << endl;
    objetivo->recibirDanio(danio);

    // Recupera un poco de energia al combatir
    energiaSacra += 10;
    if (energiaSacra > energiaMaxima) energiaSacra = energiaMaxima;
    cout << "   [FE] +10 Energia Sacra por combatir." << endl;

    return danio;
}

void Paladin::bendicionDivina() {
    cout << "   [LUZ] ¡" << nombre << " invoca una Bendicion Divina!" << endl;
    int curacion = 25 + (nivel * 5);
    curar(curacion);

    aplicarEfecto("defensa", 10, 2);

    // Gasto de energia
    energiaSacra -= 40;
}

// --- LOGICA INTERACTIVA CON ENERGIA ---
void Paladin::realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Paladin) --" << endl;
    // Barra de Energia Sacra
    cout << "Energia Sacra: " << energiaSacra << "/" << energiaMaxima << " [";
    for(int i=0; i<10; i++) cout << (i < energiaSacra/10 ? "+" : " ");
    cout << "]" << endl;

    cout << "1. Martillo Sagrado (+10 Energia)" << endl;

    if (energiaSacra >= 40) {
        cout << "2. Bendicion Divina (Gasta 40 Energia)" << endl;
    } else {
        cout << "2. [Poca Fe] Bendicion Divina (Necesitas 40)" << endl;
    }

    cout << "3. Plegaria (Recuperar 30 Energia)" << endl;
    cout << "4. Usar Objeto" << endl;
    cout << "Elige: ";

    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opcion == 1) {
        cout << "\n--- OBJETIVO ---" << endl;
        for (int i = 0; i < enemigos.size(); i++) {
            cout << " " << i + 1 << ". " << enemigos[i]->getNombre()
                 << " [Vida: " << enemigos[i]->getVida() << "]" << endl;
        }
        cout << "Numero: ";
        int idx; cin >> idx; cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Personaje* objetivo = nullptr;
        if (idx > 0 && idx <= enemigos.size()) objetivo = enemigos[idx - 1];
        else objetivo = enemigos[0];

        atacar(objetivo);

    } else if (opcion == 2) {
        if (energiaSacra >= 40) {
            bendicionDivina();
        } else {
            cout << "No tienes suficiente energia sacra. Debes rezar o pelear." << endl;
        }
    } else if (opcion == 3) {
        plegaria();
    } else if (opcion == 4) {
        if (!objetosEquipados.empty()) usarObjeto(0);
        else cout << "Sin objetos." << endl;
    }
}