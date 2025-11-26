//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ELIXIRSOMBRIO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ELIXIRSOMBRIO_H

#include "ObjetoMagico.h"
#include "Personaje.h"
#include <vector>

class ElixirSombrio : public ObjetoMagico {
private:
    int danioMin;
    int danioMax;

public:
    ElixirSombrio(int stock);
    void usar(Personaje* objetivo) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ELIXIRSOMBRIO_H