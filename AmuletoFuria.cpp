//
// Created by Usuario on 21/11/2025.
//

#include "AmuletoFuria.h"
#include <iostream>

using namespace std;

AmuletoFuria::AmuletoFuria(int stock)
    : ObjetoMagico("AmuletoFuria", "Aumenta ataque +5 a +10 por 2 turnos", stock, "buff_ataque") {

    this->aumentoMin = 5;
    this->aumentoMax = 10;
    this->duracion = 2;
}

AmuletoFuria::~AmuletoFuria() {
}

void AmuletoFuria::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) {
        cout << " No se puede usar en este objetivo" << endl;
        return;
    }

    int aumento = aumentoMin + (rand() % (aumentoMax - aumentoMin + 1));

    cout << "   [INFO] Efecto: Aumenta ataque +" << aumento << " por " << duracion << " turnos" << endl;
    objetivo->aplicarEfecto("ataque", aumento, duracion);

    marcarUsado();
}
