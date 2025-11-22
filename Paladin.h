//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PALADIN_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PALADIN_H

#include "Personaje.h"

class Paladin : public Personaje {
private:
    int defensaExtra;
    int danioSagrado;
    int energiaSacra;
    int energiaMaxima;

public:

    Paladin(string nombre, int nivel);
    ~Paladin();

    int atacar(Personaje* objetivo) override;
    void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) override;

private:

    int ataqueDefensivo(Personaje* objetivo);
    void bendicionDivina();
    void plegaria(); // recurpar energia del personaje

};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PALADIN_H