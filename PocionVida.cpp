//
// Created by Usuario on 21/11/2025.
//

#include "PocionVida.h"
#include <iostream>
#include <cstdlib>

using namespace std;

PocionVida::PocionVida(int stock)
    : ObjetoMagico("PocionVida", "Restaura entre 20-40 puntos de vida", stock, "curacion") {

    this->curacionMin = 20;
    this->curacionMax = 40;
}

PocionVida::~PocionVida() {
    // Destructor
}

void PocionVida::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) {
        cout << " No se puede usar en este objetivo" << endl;
        return;
    }

    // Calcular curación aleatoria
    int curacion = curacionMin + (rand() % (curacionMax - curacionMin + 1));

    cout << "   [INFO] Efecto: Restaura " << curacion << " puntos de vida" << endl;
    objetivo->curar(curacion);

    marcarUsado();
}