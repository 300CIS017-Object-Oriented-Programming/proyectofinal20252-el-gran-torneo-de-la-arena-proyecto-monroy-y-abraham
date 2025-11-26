//
// Created by Jesus Esteban Monroy on 25/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_INVENTARIO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_INVENTARIO_H


#include <string>
#include <unordered_map>
#include <vector>
#include "ObjetoMagico.h"
#include "Personaje.h"

using namespace std;

class Inventario {
private:
    unordered_map<string, ObjetoMagico*> objetosDisponibles;
    vector<ObjetoMagico*> objetosUsados;
    int capacidadMaxima;

public:
    Inventario();
    ~Inventario();

    void inicializarObjetos();
    bool crearObjeto(ObjetoMagico* objeto);
    void listarObjetos();
    void listarObjetosDetallado();
    ObjetoMagico* consultarObjeto(string nombre);
    bool actualizarStock(string nombre, int nuevoStock);
    bool eliminarObjeto(string nombre);
    bool asignarObjetoAHeroe(Personaje* heroe, string nombreObjeto);
    bool retirarObjetoDeHeroe(Personaje* heroe, string nombreObjeto);
    bool verificarDisponibilidad(string nombre);
    void limpiarObjetosUsados();


    // Retorna un vector con todos los objetos disponibles ayuda de un compañero
    vector<ObjetoMagico*> getObjetosDisponibles() {
        vector<ObjetoMagico*> objetos;
        for (auto& par : objetosDisponibles) {
            objetos.push_back(par.second);
        }
        return objetos;
    }

    vector<ObjetoMagico*> getObjetosUsados() { return objetosUsados; }
};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_INVENTARIO_H