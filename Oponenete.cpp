//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Oponente.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "ObjetoMagico.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

Oponente::Oponente(string nombre, int nivel, int vida, int ataque, int defensa, string rol)
    : Personaje(nombre, nivel, vida, ataque, defensa, rol) {

    int estrategiaRandom = rand() % 3;

    if (estrategiaRandom == 0) {
        estrategia = "agresivo";
        agresividad = 80;
    } else if (estrategiaRandom == 1) {
        estrategia = "defensivo";
        agresividad = 30;
    } else {
        estrategia = "equilibrado";
        agresividad = 50;
    }

    contadorTurnos = 0;
}

Oponente::~Oponente() {}

int Oponente::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) {
        return 0;
    }

    cout << "   [ATK] " << nombre << " ataca a " << objetivo->getNombre() << endl;

    int danio = calcularDanioBase(objetivo);
    if (danio < 0) danio = 0;

    cout << "   [DANIO] " << danio << " puntos" << endl;
    objetivo->recibirDanio(danio);

    cout << "   [HP] " << objetivo->getNombre() << " - Vida: "
         << objetivo->getVida() << "/" << objetivo->getVidaMaxima() << endl;

    return danio;
}

void Oponente::realizarAccion(vector<Personaje*>& aliados,
                              vector<Personaje*>& enemigos) {
    if (!estaVivo() || enemigos.empty()) return;

    cout << "\n>> Turno de " << nombre
         << " (" << rol << " enemigo - " << estrategia << ")" << endl;

    contadorTurnos++;
    decidirAccion(aliados, enemigos);
}

void Oponente::decidirAccion(vector<Personaje*>& aliados,
                             vector<Personaje*>& enemigos) {

    int vidaPorcentaje = (vida * 100) / vidaMaxima;
    int enemigosVivos = contarVivos(enemigos);

    Personaje* objetivo = nullptr;

    if (estrategia == "agresivo") {
        if (vidaPorcentaje < 30 && enemigosVivos > 2) {
            objetivo = seleccionarMasDebil(enemigos);
            cout << "   [OBJETIVO] Eliminar al mas debil" << endl;
        } else {
            objetivo = seleccionarMasFuerte(enemigos);
            cout << "   [OBJETIVO] Enfrentar al mas fuerte" << endl;
        }

    } else if (estrategia == "defensivo") {

        if (vidaPorcentaje < 50) {
            if (!objetosEquipados.empty()) {
                for (size_t i = 0; i < objetosEquipados.size(); i++) {
                    if (!objetosEquipados[i]->fueUsado()) {
                        cout << "   [ITEM] Usar objeto defensivo" << endl;
                        usarObjeto(i);
                        return;
                    }
                }
            }

            objetivo = seleccionarMasFuerte(enemigos);
            cout << "   [OBJETIVO] Neutralizar amenaza principal" << endl;

        } else {
            objetivo = seleccionarObjetivo(enemigos);
        }

    } else { // equilibrado

        if (vidaPorcentaje < 40) {
            if (!objetosEquipados.empty()) {
                for (size_t i = 0; i < objetosEquipados.size(); i++) {
                    if (!objetosEquipados[i]->fueUsado()) {
                        cout << "   [ITEM] Usar objeto para sobrevivir" << endl;
                        usarObjeto(i);
                        return;
                    }
                }
            }
        }

        if (enemigosVivos == 1) {
            objetivo = enemigos[0];
            cout << "   [OBJETIVO] Eliminar ultimo enemigo" << endl;
        } else {
            objetivo = seleccionarObjetivo(enemigos);
            cout << "   [OBJETIVO] Distribuir danio" << endl;
        }
    }

    if (objetivo) {
        atacar(objetivo);
    }
}

Personaje* Oponente::seleccionarObjetivo(vector<Personaje*>& enemigos) {
    vector<Personaje*> vivos;

    for (Personaje* p : enemigos) {
        if (p && p->estaVivo()) {
            vivos.push_back(p);
        }
    }

    if (vivos.empty()) return nullptr;

    int idx = rand() % vivos.size();
    return vivos[idx];
}

Personaje* Oponente::seleccionarMasDebil(vector<Personaje*>& enemigos) {
    Personaje* masDebil = nullptr;
    int minVida = 999999;

    for (Personaje* enemigo : enemigos) {
        if (enemigo->estaVivo() && enemigo->getVida() < minVida) {
            minVida = enemigo->getVida();
            masDebil = enemigo;
        }
    }

    if (masDebil) return masDebil;
    return seleccionarObjetivo(enemigos);
}

Personaje* Oponente::seleccionarMasFuerte(vector<Personaje*>& enemigos) {
    Personaje* masFuerte = nullptr;
    int maxAtaque = 0;

    for (Personaje* enemigo : enemigos) {
        if (enemigo->estaVivo() && enemigo->getAtaque() > maxAtaque) {
            maxAtaque = enemigo->getAtaque();
            masFuerte = enemigo;
        }
    }

    if (masFuerte) return masFuerte;
    return seleccionarObjetivo(enemigos);
}

int Oponente::contarVivos(vector<Personaje*>& personajes) {
    int count = 0;
    for (Personaje* p : personajes) {
        if (p && p->estaVivo()) {
            count++;
        }
    }
    return count;
}
