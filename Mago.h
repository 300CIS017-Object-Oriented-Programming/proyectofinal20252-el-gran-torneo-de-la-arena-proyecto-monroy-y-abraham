//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_MAGO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_MAGO_H

#include "Personaje.h"

class Mago : public Personaje {
private:
    int danioMagicoExtra;
    float ignorarDefensaPorcentaje;

    // energia arcana
    int energia;
    int energiaMaxima;

public:
    Mago(string nombre, int nivel);
    ~Mago();

    int atacar(Personaje* objetivo) override;
    void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) override;

private:
    int lanzarHechizo(Personaje* objetivo);
    bool consumirEnergia(int cantidad);
    void meditar(); // Recuperar energia
};
#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_MAGO_H