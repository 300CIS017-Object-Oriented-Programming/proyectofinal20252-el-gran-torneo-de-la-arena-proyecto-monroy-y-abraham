//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_CRISTALMAGICO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_CRISTALMAGICO_H

#include "ObjetoMagico.h"
#include "Personaje.h"

class CristalMagico : public ObjetoMagico {
private:
    int restauracionEnergia;

public:
    CristalMagico(int stock);
    void usar(Personaje* objetivo) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_CRISTALMAGICO_H