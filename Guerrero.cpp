//
// Created by Jesus Esteban Monroy on 21/11/2025.
//
#include "Guerrero.h"
#include <iostream>
#include <limits>
#include "ObjetoMagico.h"

using std::cout;
using std::endl;


Guerrero::Guerrero(string nombre, int nivel)
    : Personaje(nombre, nivel, 120 + (nivel * 10), 25 + (nivel * 2), 18 + nivel, "Guerrero") {
    this->probabilidadCritico = 0.20f;
    this->multiplicadorCritico = 1.8f;

    // Furia empieza en 0 (Calmado)
    this->furia = 0;
    this->furiaMaxima = 100;
}

Guerrero::~Guerrero() {}

void Guerrero::generarFuria(int cantidad) {
    furia += cantidad;
    if (furia > furiaMaxima) furia = furiaMaxima;
    cout << "   [FURIA] " << nombre << " genera " << cantidad << " de Furia." << endl;
}

int Guerrero::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;

    cout << "   [ATK] " << nombre << " lanza un tajo con su espada." << endl;

    int danio = calcularDanioBase(objetivo);

    if (intentarGolpeCritico()) {
        danio = static_cast<int>(danio * multiplicadorCritico);
        cout << "   [CRITICO] ¡Impacto brutal!" << endl;
        // Critico genera mas furia
        generarFuria(10);
    }

    cout << "   [DANIO] " << danio << " puntos." << endl;
    objetivo->recibirDanio(danio);

    // Ataque normal genera furia
    generarFuria(20);

    return danio;
}

bool Guerrero::intentarGolpeCritico() {
    float chance = static_cast<float>(rand() % 100) / 100.0f;
    return chance < probabilidadCritico;
}

// interaccion
void Guerrero::realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Guerrero) --" << endl;
    // Barra de Furia
    cout << "Furia: " << furia << "/" << furiaMaxima << " [";
    for(int i=0; i<10; i++) cout << (i < furia/10 ? "X" : " ");
    cout << "]" << endl;

    cout << "1. Ataque Basico (Genera +20 Furia)" << endl;

    if (furia >= 50) {
        cout << "2. EJECUCION (Gasta 50 Furia - Daño Masivo)" << endl;
    } else {
        cout << "2. [Falta Furia] Ejecucion (Necesitas 50)" << endl;
    }

    cout << "3. Usar Objeto" << endl;
    cout << "Elige: ";

    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Personaje* objetivo = nullptr;

    if (opcion == 1 || (opcion == 2 && furia >= 50)) {
        cout << "\n--- SELECCIONA ENEMIGO ---" << endl;
        for (int i = 0; i < enemigos.size(); i++) {
            cout << " " << i + 1 << ". " << enemigos[i]->getNombre()
                 << " [Vida: " << enemigos[i]->getVida() << "]" << endl;
        }
        cout << "Numero: ";
        int idx; cin >> idx; cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (idx > 0 && idx <= enemigos.size()) objetivo = enemigos[idx - 1];
        else objetivo = enemigos[0];
    }

    if (opcion == 1) {
        atacar(objetivo);
    } else if (opcion == 2) {
        if (furia >= 50) {
            furia -= 50;
            cout << " ¡" << nombre << " libera su ira en un golpe final!" << endl;
            int danio = (ataque * 2) + 20; // Daño muy alto
            cout << "   [EJECUCION] " << danio << " puntos de daño!!" << endl;
            objetivo->recibirDanio(danio);
        } else {
            cout << "No tienes suficiente furia. Atacas normal." << endl;
            atacar(objetivo);
        }
    } else if (opcion == 3) {
        if (!objetosEquipados.empty()) usarObjeto(0);
        else cout << "Sin objetos." << endl;
    }
}