//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Arquero.h"
#include "Arquero.h"
#include <iostream>
#include <limits>
#include "ObjetoMagico.h"

using std::cout;
using std::endl;


Arquero::Arquero(string nombre, int nivel)
    : Personaje(nombre, nivel, 80 + (nivel * 8), 28 + (nivel * 3), 10 + nivel, "Arquero") {
    this->precision = 0.85f;
    this->flechasEspeciales = 5;

    // Sistema de Cansancio
    this->estaminaMaxima = 100;
    this->estamina = 100; // Empieza fresco
}

Arquero::~Arquero() {}

void Arquero::descansar() {
    int recuperacion = 50;
    estamina += recuperacion;
    if (estamina > estaminaMaxima) estamina = estaminaMaxima;
    cout << "   [REPOSO] " << nombre << " toma un respiro y recupera " << recuperacion << " de estamina." << endl;
}

int Arquero::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;
    return dispararFlecha(objetivo);
}

int Arquero::dispararFlecha(Personaje* objetivo) {
    cout << "   [ATK] " << nombre << " tensa el arco y dispara." << endl;

    if (!verificarPrecision()) {
        cout << "   [FALLO] La flecha paso de largo." << endl;
        // Aun fallando se cansa un poco
        estamina -= 5;
        return 0;
    }

    int danio = calcularDanioBase(objetivo);
    danio = static_cast<int>(danio * 1.1f);

    cout << "   [DANIO] " << danio << " puntos." << endl;
    objetivo->recibirDanio(danio);

    // Gasto de estamina normal
    estamina -= 10;

    return danio;
}

void Arquero::flechaExplosiva(Personaje* objetivo) {
    if (flechasEspeciales <= 0) return;

    cout << "   [BOOM] ¡Flecha Explosiva lanzada!" << endl;
    int danio = calcularDanioBase(objetivo) * 1.5;
    cout << "   [DANIO] " << danio << " puntos de daño explosivo." << endl;
    objetivo->recibirDanio(danio);

    flechasEspeciales--;
    // Gasto fuerte de estamina
    estamina -= 40;
}

bool Arquero::verificarPrecision() {
    float chance = static_cast<float>(rand() % 100) / 100.0f;
    return chance < precision;
}

// Logica interactiva incluyendo la estamina del personaje
void Arquero::realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Arquero) --" << endl;
    // Barra de Estamina
    cout << "Estamina: " << estamina << "/" << estaminaMaxima << " [";
    for(int i=0; i<10; i++) cout << (i < estamina/10 ? "=" : " ");
    cout << "]" << endl;
    cout << "Flechas Especiales: " << flechasEspeciales << endl;

    // Opciones condicionadas por la estamina
    if (estamina >= 10) cout << "1. Disparar Flecha (Gasta 10 Estamina)" << endl;
    else cout << "1. [Cansado] Disparar Flecha (Necesitas 10)" << endl;

    if (estamina >= 40 && flechasEspeciales > 0) cout << "2. Flecha Explosiva (Gasta 40 Estamina)" << endl;
    else if (flechasEspeciales == 0) cout << "2. [Sin municion] Flecha Explosiva" << endl;
    else cout << "2. [Cansado] Flecha Explosiva (Necesitas 40)" << endl;

    cout << "3. Descansar (Recuperar 50 Estamina)" << endl;
    cout << "4. Usar Objeto" << endl;
    cout << "Elige: ";

    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Personaje* objetivo = nullptr;

    // Seleccion de objetivo si va a atacar
    if ((opcion == 1 && estamina >= 10) || (opcion == 2 && estamina >= 40 && flechasEspeciales > 0)) {
        cout << "\n--- BLANCO ---" << endl;
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
        if (estamina >= 10) dispararFlecha(objetivo);
        else cout << "Estas muy cansado para tensar el arco. Debes descansar." << endl;
    }
    else if (opcion == 2) {
        if (estamina >= 40 && flechasEspeciales > 0) flechaExplosiva(objetivo);
        else if (flechasEspeciales <= 0) cout << "No te quedan flechas explosivas." << endl;
        else cout << "Estas muy cansado para la tecnica especial." << endl;
    }
    else if (opcion == 3) {
        descansar();
    }
    else if (opcion == 4) {
        if (!objetosEquipados.empty()) usarObjeto(0);
        else cout << "Sin objetos." << endl;
    }
}