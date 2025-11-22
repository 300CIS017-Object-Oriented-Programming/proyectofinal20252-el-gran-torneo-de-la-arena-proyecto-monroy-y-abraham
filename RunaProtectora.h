//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_RUNAPROTECTORA_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_RUNAPROTECTORA_H


#include <iostream>
#include "ElixirSombrio.h"
#include "ObjetoMagico.h"
#include "Personaje.h"

class RunaProtectora : public ObjetoMagico {
private:
    int absorcionMin;
    int absorcionMax;
    int duracion;

public:
    RunaProtectora(int stock);
    void usar(Personaje* objetivo) override;
};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_RUNAPROTECTORA_H