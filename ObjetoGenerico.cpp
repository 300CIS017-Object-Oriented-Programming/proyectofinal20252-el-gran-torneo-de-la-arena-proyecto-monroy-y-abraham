//
// Created by Usuario on 24/11/2025.
//

#include "ObjetoGenerico.h"
#include <iostream>
#include <cstdlib>

using namespace std;

ObjetoGenerico::ObjetoGenerico(string nombre, string descripcion, int stock,
                               string tipoEfecto, int valorMin, int valorMax, int duracion)
    : ObjetoMagico(nombre, descripcion, stock, tipoEfecto) {

    this->tipoEfecto = tipoEfecto;
    this->valorMin = valorMin;
    this->valorMax = valorMax;
    this->duracion = duracion;
}

ObjetoGenerico::~ObjetoGenerico() {
    // Destructor
}

void ObjetoGenerico::usar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) {
        cout << " No se puede usar en este objetivo" << endl;
        return ;
    }

    // Calcular valor aleatorio en el rango
    int valor = valorMin + (rand() % (valorMax - valorMin + 1));

    // Aplicar efecto según tipo
    if (tipoEfecto == "curacion") {
        cout << "   [INFO] " << nombre << " restaura " << valor << " puntos de vida!" << endl;
        objetivo->curar(valor);
    }
    else if (tipoEfecto == "buff_ataque") {
        cout << "   [INFO] " << nombre << " aumenta el ataque +" << valor;
        if (duracion > 0) {
            cout << " por " << duracion << " turnos";
        }
        cout << "!" << endl;
        objetivo->aplicarEfecto("ataque", valor, duracion);
    }
    else if (tipoEfecto == "buff_defensa") {
        cout << "   [INFO]  " << nombre << " aumenta la defensa +" << valor;
        if (duracion > 0) {
            cout << " por " << duracion << " turnos";
        }
        cout << "!" << endl;
        objetivo->aplicarEfecto("defensa", valor, duracion);
    }
    else if (tipoEfecto == "especial") {
        cout << "   [INFO] " << nombre << " libera su poder mágico!" << endl;
        cout << "   [INFO] Efecto especial: restaura " << (valor / 2) << " HP y aumenta stats" << endl;
        objetivo->curar(valor / 2);
        objetivo->aplicarEfecto("ataque", valor / 4, duracion);
        objetivo->aplicarEfecto("defensa", valor / 4, duracion);
    }
    else {
        cout << "   [INFO]  Efecto desconocido" << endl;
    }

    marcarUsado();
}