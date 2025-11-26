//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Mago.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;
using std::vector;

Mago::Mago(string nombre, int nivel)
    : Personaje(nombre, nivel,
                70 + (nivel * 8),     // vida
                30 + (nivel * 3),     // ataque
                8 + nivel,            // defensa
                "Mago") {

    danioMagicoExtra = 5 + nivel;
    ignorarDefensaPorcentaje = 0.30f;  // ignora 30% de defensa

    energiaMaxima = 100;
    energia = energiaMaxima;
}

Mago::~Mago() {}

void Mago::meditar() {
    int recuperacion = 40;
    energia += recuperacion;
    if (energia > energiaMaxima) energia = energiaMaxima;

    cout << "   [MEDITACION] " << nombre
         << " recupera " << recuperacion << " de energia.\n";
}

bool Mago::consumirEnergia(int cantidad) {
    if (energia >= cantidad) {
        energia -= cantidad;
        return true;
    }
    return false;
}

int Mago::atacar(Personaje* objetivo) {
    if (!consumirEnergia(10)) {
        cout << "   [!] No tienes energia suficiente.\n";
        return 0;
    }
    return lanzarHechizo(objetivo);
}

int Mago::lanzarHechizo(Personaje* objetivo) {
    cout << "   [MAGIA] " << nombre << " lanza una Bola de Fuego.\n";

    // Defensa reducida sin usar static_cast
    int defensaOriginal = objetivo->getDefensa();
    int defensaReducida = defensaOriginal - (defensaOriginal * 3 / 10); // 30%

    int danio = ataque + danioMagicoExtra - defensaReducida;

    danio = aplicarVariacionAleatoria(danio, 15);
    if (danio < 0) danio = 0;

    cout << "   [DANIO] " << danio << " puntos.\n";
    objetivo->recibirDanio(danio);
    return danio;
}

void Mago::realizarAccion(vector<Personaje*>& aliados,
                          vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    if (energia < energiaMaxima) energia += 5; // recuperación pasiva

    cout << "\n-- Turno de " << nombre << " (Mago) --\n";
    cout << "Vida: " << vida << "\n";
    cout << "Energia: " << energia << "/" << energiaMaxima << "\n\n";

    cout << "1. Bola de Fuego (10 energia)\n";
    cout << "2. Explosion Arcana (40 energia, daño a todos)\n";
    cout << "3. Meditar (+40 energia)\n";
    cout << "4. Usar objeto\n";
    cout << "Elige opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opcion) {
        case 1: {
            if (energia < 10) {
                cout << "   [INFO] No tienes energia.\n";
                break;
            }

            cout << "\n--- Seleccionar objetivo ---\n";
            for (int i = 0; i < (int)enemigos.size(); i++) {
                cout << i + 1 << ". " << enemigos[i]->getNombre()
                     << " (Vida: " << enemigos[i]->getVida() << ")\n";
            }
            cout << "Num: ";
            int idx;
            cin >> idx;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (idx < 1 || idx > (int)enemigos.size()) idx = 1;

            lanzarHechizo(enemigos[idx - 1]);
            break;
        }

        case 2: {
            if (energia < 40) {
                cout << "   [INFO] No tienes energia para Explosion Arcana.\n";
                break;
            }

            consumirEnergia(40);
            cout << "   [TORMENTA] " << nombre << " libera magia a todos los enemigos.\n";

            for (auto e : enemigos) {
                if (e->estaVivo()) {
                    int danio = (ataque + danioMagicoExtra) / 2;
                    cout << " - " << e->getNombre() << " recibe " << danio << "\n";
                    e->recibirDanio(danio);
                }
            }
            break;
        }

        case 3:
            meditar();
            break;

        case 4:
            if (!objetosEquipados.empty()) usarObjeto(0);
            else cout << "   [INFO] No tienes objetos.\n";
            break;

        default:
            cout << "   [INFO] Opcion no valida.\n";
            break;
    }
}
