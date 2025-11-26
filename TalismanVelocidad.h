//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_TALISMANVELOCIDAD_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_TALISMANVELOCIDAD_H


#include "ObjetoMagico.h"
#include "Personaje.h"

class TalismanVelocidad : public ObjetoMagico {
private:
    int bonusTurnos;

public:
    TalismanVelocidad(int stock);
    void usar(Personaje* objetivo) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_TALISMANVELOCIDAD_H