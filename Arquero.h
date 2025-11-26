//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ARQUERO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ARQUERO_H


#include "Personaje.h"

class Arquero : public Personaje {
private:
    float precision;
    int flechasEspeciales;
    int estamina;
    int estaminaMaxima;

public:
    Arquero(string nombre, int nivel);
    ~Arquero();

    int atacar(Personaje* objetivo) override;
    void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) override;

private:
    int dispararFlecha(Personaje* objetivo);
    void flechaExplosiva(Personaje* objetivo);
    bool verificarPrecision();

    // Accion para recuperar aura
    void descansar();
};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ARQUERO_H