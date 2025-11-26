//
// Created by Usuario on 21/11/2025.
//

#include "EscudoBendito.h"
#include <iostream>

using namespace std;

EscudoBendito::EscudoBendito(int stock)
    : ObjetoMagico("EscudoBendito", "Aumenta defensa +10 a +20 por 1 turno", stock, "buff_defensa") {

    this->defensaMin = 10;
    this->defensaMax = 20;
    this->duracion = 1;
}

EscudoBendito::~EscudoBendito() {
}

void EscudoBendito::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) {
        cout << " No se puede usar en este objetivo" << endl;
        return;
    }

    int aumento = defensaMin + (rand() % (defensaMax - defensaMin + 1));

    cout << "   [INFO] Efecto: Aumenta defensa +" << aumento << " por " << duracion << " turno" << endl;
    objetivo->aplicarEfecto("defensa", aumento, duracion);

    marcarUsado();
}