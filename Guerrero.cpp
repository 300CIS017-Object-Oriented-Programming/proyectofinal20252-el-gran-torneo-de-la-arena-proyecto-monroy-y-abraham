//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Guerrero.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

Guerrero::Guerrero(string nombre, int nivel)
    : Personaje(nombre, nivel,
                120 + (nivel * 10),   // vida
                25 + (nivel * 2),     // ataque
                18 + nivel,           // defensa
                "Guerrero") {

    probabilidadCritico = 0.20f;
    multiplicadorCritico = 1.8f;

    furiaMaxima = 100;
    furia = 0;
}

Guerrero::~Guerrero() {}

void Guerrero::generarFuria(int cantidad) {
    furia += cantidad;
    if (furia > furiaMaxima) {
        furia = furiaMaxima;
    }
    cout << "   [FURIA] " << nombre
         << " gana " << cantidad << " de furia.\n";
}

int Guerrero::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;

    cout << "   [ATK] " << nombre << " ataca con su espada.\n";

    int danio = calcularDanioBase(objetivo);

    if (intentarGolpeCritico()) {
        // 1.8x el daño usando solo enteros (aprox)
        danio = danio * 18 / 10;
        cout << "   [CRITICO] ¡Golpe crítico!\n";
        generarFuria(10);   // extra furia por crítico
    }

    cout << "   [DANIO] " << danio << " puntos.\n";
    objetivo->recibirDanio(danio);

    // Ataque normal genera furia base
    generarFuria(20);

    return danio;
}

bool Guerrero::intentarGolpeCritico() {
    float chance = static_cast<float>(rand() % 100) / 100.0f;
    return chance < probabilidadCritico;
}

void Guerrero::realizarAccion(vector<Personaje*>& aliados,
                              vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Guerrero) --\n";
    cout << "Vida: " << vida << "\n";
    cout << "Furia: " << furia << "/" << furiaMaxima << "\n\n";

    cout << "1. Ataque básico (+20 furia)\n";
    cout << "2. Ejecución (requiere 50 de furia)\n";
    cout << "3. Usar objeto\n";
    cout << "Elige opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Personaje* objetivo = nullptr;

    // Si va a atacar, pedimos enemigo
    if ((opcion == 1 || opcion == 2) && !enemigos.empty()) {
        cout << "\n--- Selecciona enemigo ---\n";
        for (int i = 0; i < (int)enemigos.size(); ++i) {
            cout << " " << i + 1 << ". " << enemigos[i]->getNombre()
                 << " (Vida: " << enemigos[i]->getVida() << ")\n";
        }
        cout << "Numero: ";
        int idx;
        cin >> idx;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (idx >= 1 && idx <= (int)enemigos.size()) {
            objetivo = enemigos[idx - 1];
        } else {
            objetivo = enemigos[0];
        }
    }

    switch (opcion) {
        case 1:
            atacar(objetivo);
            break;

        case 2:
            if (furia < 50) {
                cout << "   [INFO] No tienes suficiente furia, haces un ataque básico.\n";
                atacar(objetivo);
            } else {
                furia -= 50;
                cout << "   [EJECUCION] " << nombre
                     << " desata un golpe devastador.\n";
                int danio = ataque * 2 + 20;
                cout << "   [DANIO] " << danio << " puntos.\n";
                objetivo->recibirDanio(danio);
            }
            break;

        case 3:
            if (!objetosEquipados.empty()) {
                usarObjeto(0);   // de momento siempre el primero
            } else {
                cout << "   [INFO] No tienes objetos equipados.\n";
            }
            break;

        default:
            cout << "   [INFO] Opcion no valida, el guerrero pierde el turno.\n";
            break;
    }
}