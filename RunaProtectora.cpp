//
// Created by Usuario on 21/11/2025.
//
#include "RunaProtectora.h"
#include <iostream>
#include <cstdlib>

RunaProtectora::RunaProtectora(int stock)
    : ObjetoMagico("RunaProtectora", "Crea escudo mágico", stock, "buff_defensa") {
    this->absorcionMin = 30;
    this->absorcionMax = 50;
    this->duracion = 3;
}

void RunaProtectora::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return;

    int absorcion = absorcionMin + (rand() % (absorcionMax - absorcionMin + 1));

    cout << "   [INFO] Una runa protectora rodea a " << objetivo->getNombre() << "!" << endl;
    cout << "   [INFO] Escudo mágico: absorbe " << absorcion << " de daño por " << duracion << " turnos" << endl;

    // Implementado como buff de defensa
    objetivo->aplicarEfecto("defensa", absorcion / 3, duracion);
    marcarUsado();
}