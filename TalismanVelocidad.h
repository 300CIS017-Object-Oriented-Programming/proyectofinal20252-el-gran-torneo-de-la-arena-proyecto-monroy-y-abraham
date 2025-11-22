//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_TALISMANVELOCIDAD_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_TALISMANVELOCIDAD_H


#include "Objeto magico.h"
#include <iostream>

class RunaProtectora : public ObjetoMagico {

private:
     int BonusTurnos;

public:
     talismanVelocidad(int stock);
     void usar(Personaje* objeto) override;

};



#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_TALISMANVELOCIDAD_H