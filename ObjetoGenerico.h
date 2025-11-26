//
// Created by Usuario on 24/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OBJETOGENERICO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OBJETOGENERICO_H

#include "ObjetoMagico.h"
#include "Personaje.h"

class ObjetoGenerico : public ObjetoMagico {
private:
    string tipoEfecto; // "curacion", "buff_ataque", "buff_defensa", "especial"
    int valorMin;
    int valorMax;
    int duracion;

public:
    ObjetoGenerico(string nombre, string descripcion, int stock,
                   string tipoEfecto, int valorMin, int valorMax, int duracion = 0);
    ~ObjetoGenerico();

    void usar(Personaje* objetivo) override;
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OBJETOGENERICO_H