//
// Created by Usuario on 21/11/2025.
//
//
// Created by Usuario on 15/11/2025.
//

#include "TalismanVelocidad.h"
#include <iostream>

TalismanVelocidad::TalismanVelocidad(int stock)
    : ObjetoMagico("TalismanVelocidad", "Da un turno extra", stock, "especial") {
    this->bonusTurnos = 1;
}

void TalismanVelocidad::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return;
    cout << "   [INFO] " << objetivo->getNombre() << " gana velocidad extra!" << endl;
    cout << "   [INFO] (En esta implementación básica, aumenta temporalmente el ataque)" << endl;
    objetivo->aplicarEfecto("ataque", 5, 2);
    marcarUsado();
}