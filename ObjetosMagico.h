//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OBJETOSMAGICOS_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OBJETOSMAGICOS_H

#include <string>
using namespace std;


class Personaje;

class ObjetoMagico {
protected:
    string nombre;
    string descripcion;
    int stockGlobal;
    bool usado;
    string tipo;

public:
    ObjetoMagico(string nombre, string descripcion, int stock, string tipo);
    virtual ~ObjetoMagico();


    virtual void usar(Personaje* objetivo) = 0;

    // Métodos comunes
    void reducirStock();
    void aumentarStock(int cantidad);
    void marcarUsado();
    bool fueUsado() const;

    // Getters
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    int getStock() const { return stockGlobal; }
    string getTipo() const { return tipo; }

    // Setters
    void setStock(int stock) { stockGlobal = stock; }
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_OBJETOSMAGICOS_H