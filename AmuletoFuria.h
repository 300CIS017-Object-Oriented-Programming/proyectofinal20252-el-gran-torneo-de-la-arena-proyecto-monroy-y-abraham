//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_AMULETOFURIA_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_AMULETOFURIA_H

#include "ObjetoMagico.h"
#include "Personaje.h"

class AmuletoFuria : public ObjetoMagico {
private:
    int aumentoMin;
    int aumentoMax;
    int duracion;

public:
    AmuletoFuria(int stock);
    ~AmuletoFuria();

    void usar(Personaje* objetivo) override;
};



#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_AMULETOFURIA_H