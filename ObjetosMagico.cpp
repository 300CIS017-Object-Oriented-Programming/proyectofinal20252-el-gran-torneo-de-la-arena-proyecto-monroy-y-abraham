//
// Created by Usuario on 15/11/2025.
//

#include "ObjetoMagico.h"

#include "ObjetoMagico.h"
#include <iostream>

using namespace std;

ObjetoMagico::ObjetoMagico(string nombre, string descripcion, int stock, string tipo) {
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->stockGlobal = stock;
    this->usado = false;
    this->tipo = tipo;
}

ObjetoMagico::~ObjetoMagico() {
    // Destructor base
}

void ObjetoMagico::reducirStock() {
    if (stockGlobal > 0) {
        stockGlobal--;
    }
}

void ObjetoMagico::aumentarStock(int cantidad) {
    stockGlobal += cantidad;
    if (stockGlobal < 0) {
        stockGlobal = 0;
    }
}

void ObjetoMagico::marcarUsado() {
    usado = true;
}

bool ObjetoMagico::fueUsado() const {
    return usado;
}