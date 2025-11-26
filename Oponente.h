//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OPONENETE_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OPONENETE_H

#include "Personaje.h"

class Oponente : public Personaje {
private:
    string estrategia; // "agresivo", "defensivo", "equilibrado"
    int agresividad;
    int contadorTurnos;

public:
    Oponente(string nombre, int nivel, int vida, int ataque, int defensa, string rol);
    ~Oponente();

    int atacar(Personaje* objetivo) override;
    void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) override;

private:
    void decidirAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos);
    Personaje* seleccionarObjetivo(vector<Personaje*>& enemigos);
    Personaje* seleccionarMasDebil(vector<Personaje*>& enemigos);
    Personaje* seleccionarMasFuerte(vector<Personaje*>& enemigos);
    int contarVivos(vector<Personaje*>& personajes);
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OPONENETE_H