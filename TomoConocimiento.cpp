//
// Created by Usuario on 21/11/2025.
//

#include "TomoConocimiento.h"
#include <iostream>

TomoConocimiento::TomoConocimiento(int stock)
    : ObjetoMagico("TomoConocimiento", "Aumenta estadísticas", stock, "especial") {
    this->experienciaGanada = 100;
}

void TomoConocimiento::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return;
    cout << "   [INFO] " << objetivo->getNombre() << " lee el tomo y gana sabiduría!" << endl;
    cout << "   [INFO] Todas las estadísticas aumentan ligeramente" << endl;
    objetivo->setAtaque(objetivo->getAtaque() + 3);
    objetivo->setDefensa(objetivo->getDefensa() + 3);
    objetivo->curar(20);

    marcarUsado();
}