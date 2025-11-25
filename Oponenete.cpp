//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Oponente.h"
#include <iostream>
#include <cstdlib>
#include "ObjetoMagico.h"

using namespace std;

Oponente::Oponente(string nombre, int nivel, int vida, int ataque, int defensa, string rol)
    : Personaje(nombre, nivel, vida, ataque, defensa, rol) {

    int estrategiaRandom = rand() % 3;
    if (estrategiaRandom == 0) {
        this->estrategia = "agresivo";
        this->agresividad = 80;
    } else if (estrategiaRandom == 1) {
        this->estrategia = "defensivo";
        this->agresividad = 30;
    } else {
        this->estrategia = "equilibrado";
        this->agresividad = 50;
    }

    this->contadorTurnos = 0;
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

void Oponente::realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) {
    if (!estaVivo() || enemigos.empty()) return;

    cout << "\n>> Turno de " << nombre << " (" << rol << " enemigo - " << estrategia << ")" << endl;

    contadorTurnos++;
    decidirAccion(aliados, enemigos);
}

void Oponente::decidirAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) {
    int vidaPorcentaje = (vida * 100) / vidaMaxima;
    int enemigosVivos = contarVivos(enemigos);

    Personaje* objetivo = nullptr;

    if (estrategia == "agresivo") {
        if (vidaPorcentaje < 30 && enemigosVivos > 2) {
            objetivo = seleccionarMasDebil(enemigos);
            cout << "   [OBJETIVO] Estrategia: Eliminar al mas debil" << endl;
        } else {
            objetivo = seleccionarMasFuerte(enemigos);
            cout << "   [OBJETIVO] Estrategia: Enfrentar al mas fuerte" << endl;
        }
    } else if (estrategia == "defensivo") {
        if (vidaPorcentaje < 50) {
            if (!objetosEquipados.empty()) {
                for (size_t i = 0; i < objetosEquipados.size(); i++) {
                    if (!objetosEquipados[i]->fueUsado()) {
                        cout << "   [ITEM] Estrategia: Usar objeto defensivo" << endl;
                        usarObjeto(i);
                        return;
                    }
                }
            }

            objetivo = seleccionarMasFuerte(enemigos);
            cout << "   [OBJETIVO] Estrategia: Neutralizar amenaza principal" << endl;
        } else {
            objetivo = seleccionarObjetivo(enemigos);
        }
    } else {
        if (vidaPorcentaje < 40) {
            if (!objetosEquipados.empty()) {
                for (size_t i = 0; i < objetosEquipados.size(); i++) {
                    if (!objetosEquipados[i]->fueUsado()) {
                        usarObjeto(i);
                        return;
                    }
                }
            }
        }

        if (enemigosVivos == 1) {
            objetivo = enemigos[0];
            cout << "   [OBJETIVO] Estrategia: Eliminar ultimo enemigo" << endl;
        } else {
            objetivo = seleccionarObjetivo(enemigos);
            cout << "   [OBJETIVO] Estrategia: Distribuir danio" << endl;
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

    return vivos[rand() % vivos.size()];
}

Personaje* Oponente::seleccionarMasDebil(vector<Personaje*>& enemigos) {
    Personaje* masDebil = nullptr;
    int minVida = 9999;

    for (Personaje* enemigo : enemigos) {
        if (enemigo->estaVivo() && enemigo->getVida() < minVida) {
            minVida = enemigo->getVida();
            masDebil = enemigo;
        }
    }

    return masDebil ? masDebil : seleccionarObjetivo(enemigos);
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

    return masFuerte ? masFuerte : seleccionarObjetivo(enemigos);
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