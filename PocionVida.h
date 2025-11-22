//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_POCIONVIDA_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_POCIONVIDA_H

#include "ObjetoMagico.h"
#include "Personaje.h"

class PocionVida : public ObjetoMagico {
private:
    int curacionMin;
    int curacionMax;

public:
    PocionVida(int stock);
    ~PocionVida();

    void usar(Personaje* objetivo) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_POCIONVIDA_H