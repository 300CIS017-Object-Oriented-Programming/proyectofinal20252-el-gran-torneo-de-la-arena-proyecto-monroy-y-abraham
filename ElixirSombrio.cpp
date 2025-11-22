//
// Created by Usuario on 21/11/2025.
//

#include "ElixirSombrio.h"
#include <iostream>


ElixirSombrio::ElixirSombrio(int stock)
    : ObjetoMagico("ElixirSombrio", "Daña a TODOS (¡PELIGROSO!)", stock, "especial") {
    this->danioMin = 15;
    this->danioMax = 25;
}

void ElixirSombrio::usar(Personaje* objetivo) {
    if (!objetivo) return;

    int danio = danioMin + (rand() % (danioMax - danioMin + 1));

    cout << "   [!] ADVERTENCIA! El elixir libera energia oscura!" << endl;
    cout << "   [INFO] Dana a todos en el campo: " << danio << " puntos" << endl;
    cout << "   [INFO] (En combate real, afectaria a todos los personajes)" << endl;

    // Por simplicidad, solo daña al objetivo
    objetivo->recibirDanio(danio / 2);
    marcarUsado();
}