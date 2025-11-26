//
// Created by Usuario on 21/11/2025.
//

#include "CristalMagico.h"
#include <iostream>

CristalMagico::CristalMagico(int stock)
    : ObjetoMagico("CristalMagico", "Restaura energía mágica", stock, "especial") {
    this->restauracionEnergia = 30;
}

void CristalMagico::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return;
    cout << "  [INFO] El cristal brilla con energía arcana!" << endl;
    cout << "  [INFO] Restaura " << restauracionEnergia << " de energía" << endl;
    objetivo->curar(15); // Curación menor
    marcarUsado();
}
