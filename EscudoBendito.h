//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ESCUDOBENDITO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ESCUDOBENDITO_H

#include "ObjetoMagico.h"
#include "Personaje.h"

class EscudoBendito : public ObjetoMagico {
private:
    int defensaMin;
    int defensaMax;
    int duracion;

public:
    EscudoBendito(int stock);
    ~EscudoBendito();

    void usar(Personaje* objetivo) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ESCUDOBENDITO_H