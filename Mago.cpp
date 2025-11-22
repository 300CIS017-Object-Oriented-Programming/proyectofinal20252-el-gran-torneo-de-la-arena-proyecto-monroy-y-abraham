//
// Created by Jesus Esteban Monroy on 21/11/2025.
//
#include "Mago.h"
#include <iostream>
#include <limits>
#include "ObjetoMagico.h"

using std::cout;

Mago::Mago(string nombre, int nivel)
    : Personaje(nombre, nivel, 70 + (nivel * 8), 30 + (nivel * 3), 8 + nivel, "Mago") {
    this->danioMagicoExtra = 5 + nivel;
    this->ignorarDefensaPorcentaje = 0.30f;

    // Energia empieza llena
    this->energiaMaxima = 100;
    this->energia = 100;
}

Mago::~Mago() {}

void Mago::meditar() {
    int rec = 40;
    energia += rec;
    if (energia > energiaMaxima) energia = energiaMaxima;
    cout << "   [MEDITACION] " << nombre << " concentra su mente y recupera " << rec << " de energia." << endl;
}

bool Mago::consumirEnergia(int cantidad) {
    if (energia >= cantidad) {
        energia -= cantidad;
        return true;
    }
    return false;
}

int Mago::atacar(Personaje* objetivo) {
    // El ataque basico tambien gasta un poco de energia (es magia basica)
    if (!consumirEnergia(10)) {
        cout << "   [!] Sin energia. Debes meditar." << endl;
        return 0;
    }
    return lanzarHechizo(objetivo);
}

int Mago::lanzarHechizo(Personaje* objetivo) {
    cout << "   [MAGIA] " << nombre << " lanza una Bola de Fuego." << endl;

    int defensaReducida = static_cast<int>(objetivo->getDefensa() * (1.0f - ignorarDefensaPorcentaje));
    int danio = ataque + danioMagicoExtra - defensaReducida;

    danio = aplicarVariacionAleatoria(danio, 15);
    if (danio < 0) danio = 0;

    cout << "   [DANIO] " << danio << " puntos (ignora defensa)." << endl;
    objetivo->recibirDanio(danio);
    return danio;
}

// --- INTERACCION ---
void Mago::realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    // Recuperacion pasiva pequeña
    if (energia < energiaMaxima) energia += 5;

    cout << "\n-- Turno de " << nombre << " (Mago) --" << endl;
    // Barra de Energia
    cout << "Energia: " << energia << "/" << energiaMaxima << " [";
    for(int i=0; i<10; i++) cout << (i < energia/10 ? "*" : " ");
    cout << "]" << endl;

    if (energia >= 10) cout << "1. Bola de Fuego (Gasta 10)" << endl;
    else cout << "1. [Sin Energia] Bola de Fuego" << endl;

    if (energia >= 40) cout << "2. Explosion Arcana (Gasta 40 - Daño a TODOS)" << endl;
    else cout << "2. [Sin Energia] Explosion Arcana (Necesitas 40)" << endl;

    cout << "3. Meditar (Recuperar 40 Energia)" << endl;
    cout << "4. Usar Objeto" << endl;
    cout << "Elige: ";

    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opcion == 1 && energia >= 10) {
        cout << "\n--- OBJETIVO ---" << endl;
        for (int i = 0; i < enemigos.size(); i++) {
            cout << " " << i + 1 << ". " << enemigos[i]->getNombre()
                 << " [Vida: " << enemigos[i]->getVida() << "]" << endl;
        }
        int idx; cout << "Num: "; cin >> idx; cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Personaje* obj = (idx > 0 && idx <= enemigos.size()) ? enemigos[idx-1] : enemigos[0];
        atacar(obj);

    } else if (opcion == 2 && energia >= 40) {
        consumirEnergia(40);
        cout << " ¡" << nombre << " desata una TORMENTA MAGICA!" << endl;
        for(auto e : enemigos) {
            if(e->estaVivo()) {
                int danio = (ataque + danioMagicoExtra) / 2;
                cout << " - " << e->getNombre() << " recibe " << danio << endl;
                e->recibirDanio(danio);
            }
        }

    } else if (opcion == 3) {
        meditar();

    } else if (opcion == 4) {
        if (!objetosEquipados.empty()) usarObjeto(0);
        else cout << "Sin objetos." << endl;
    } else {
        cout << "Opcion no valida o sin energia." << endl;
    }
}