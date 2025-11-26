//
// Created by Usuario on 26/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PERSISTENCIAJSON_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PERSISTENCIAJSON_H


#include "Guild.h"
#include "Inventario.h"
#include <string>

using namespace std;

class GestorArchivos {
public:
    // Guarda todo el progreso en "partida.json"
    static void guardarPartida(Guild* guild, Inventario* inventario);

    // Lee "partida.json" y reconstruye el gremio y el inventario
    static bool cargarPartida(Guild* guild, Inventario* inventario);
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PERSISTENCIAJSON_H