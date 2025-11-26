//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Arquero.h"
#include <iostream>
#include <limits>
#include <cstdlib>     // rand

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;

Arquero::Arquero(string nombre, int nivel)
    : Personaje(nombre, nivel,
                80 + (nivel * 8),     // vida
                28 + (nivel * 3),     // ataque
                10 + nivel,           // defensa
                "Arquero") {

    precision = 0.85f;
    flechasEspeciales = 5;

    estaminaMaxima = 100;
    estamina = estaminaMaxima;
}

Arquero::~Arquero() {}

// Recupera estamina
void Arquero::descansar() {
    int recuperacion = 50;
    estamina += recuperacion;
    if (estamina > estaminaMaxima) {
        estamina = estaminaMaxima;
    }
    cout << "   [REPOSO] " << nombre
         << " descansa y recupera " << recuperacion << " de estamina.\n";
}

// Ataque básico
int Arquero::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;
    return dispararFlecha(objetivo);
}

// Disparo normal
int Arquero::dispararFlecha(Personaje* objetivo) {
    cout << "   [ATK] " << nombre << " dispara una flecha.\n";

    if (!verificarPrecision()) {
        cout << "   [FALLO] La flecha fallo.\n";
        estamina -= 5;
        return 0;
    }

    int danioBase = calcularDanioBase(objetivo);
    // Aumentamos 10% el daño de forma sencilla:
    int danio = danioBase * 11 / 10;  // 10% extra sin usar static_cast

    cout << "   [DANIO] " << danio << " puntos.\n";
    objetivo->recibirDanio(danio);

    estamina -= 10;
    return danio;
}

// Flecha especial
void Arquero::flechaExplosiva(Personaje* objetivo) {
    if (flechasEspeciales <= 0) {
        cout << "   [INFO] No te quedan flechas explosivas.\n";
        return;
    }
    if (!objetivo || !objetivo->estaVivo()) return;

    cout << "   [BOOM] ¡Flecha Explosiva!\n";

    int danioBase = calcularDanioBase(objetivo);
    int danio = danioBase * 3 / 2;  // 1.5x daño, versión simple entera

    cout << "   [DANIO] " << danio
         << " puntos de daño explosivo.\n";
    objetivo->recibirDanio(danio);

    flechasEspeciales--;
    estamina -= 40;
}

// ¿La flecha acierta?
bool Arquero::verificarPrecision() {
    float chance = static_cast<float>(rand() % 100) / 100.0f;
    return chance < precision;
}

// Menú de acciones, versión simplificada
void Arquero::realizarAccion(vector<Personaje*>& aliados,
                             vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Arquero) --\n";
    cout << "Vida: " << vida << "\n";
    cout << "Estamina: " << estamina << "/" << estaminaMaxima << "\n";
    cout << "Flechas especiales: " << flechasEspeciales << "\n\n";

    cout << "1. Disparar flecha (10 estamina)\n";
    cout << "2. Flecha explosiva (40 estamina, usa flecha especial)\n";
    cout << "3. Descansar (+50 estamina)\n";
    cout << "4. Usar objeto\n";
    cout << "Elige opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Personaje* objetivo = nullptr;

    // Solo pedimos objetivo si es una acción ofensiva
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
            objetivo = enemigos[0]; // por defecto el primero
        }
    }

    switch (opcion) {
        case 1:
            if (estamina >= 10) {
                dispararFlecha(objetivo);
            } else {
                cout << "   [INFO] No tienes suficiente estamina para atacar.\n";
            }
            break;

        case 2:
            if (estamina < 40) {
                cout << "   [INFO] No tienes suficiente estamina para la flecha explosiva.\n";
            } else if (flechasEspeciales <= 0) {
                cout << "   [INFO] No te quedan flechas explosivas.\n";
            } else {
                flechaExplosiva(objetivo);
            }
            break;

        case 3:
            descansar();
            break;

        case 4:
            if (!objetosEquipados.empty()) {
                usarObjeto(0); // por ahora usamos siempre el primero
            } else {
                cout << "   [INFO] No tienes objetos equipados.\n";
            }
            break;

        default:
            cout << "   [INFO] Opcion no valida, el arquero pierde el turno.\n";
            break;
    }
}
