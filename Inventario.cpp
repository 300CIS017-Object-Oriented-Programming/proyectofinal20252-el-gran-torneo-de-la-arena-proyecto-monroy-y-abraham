//
// Created by Jesus Esteban Monroy on 25/11/2025.
//
#include "Inventario.h"
#include "PocionVida.h"
#include "AmuletoFuria.h"
#include "EscudoBendito.h"
#include "TalismanVelocidad.h"
#include "CristalMagico.h"
#include "TomoConocimiento.h"
#include "ElixirSombrio.h"
#include "RunaProtectora.h"
#include "ObjetoGenerico.h"
#include <iostream>

using std::cout;
using std::endl;


Inventario::Inventario() {
    this->capacidadMaxima = 100;
}

Inventario::~Inventario() {
    for (auto& par : objetosDisponibles) {
        delete par.second;
    }
    objetosDisponibles.clear();
    objetosUsados.clear();
}

void Inventario::inicializarObjetos() {
    cout << "\n  Inicializando inventario global...\n" << endl;

    // Objetos predefinidos del juego
    crearObjeto(new PocionVida(10));
    crearObjeto(new AmuletoFuria(5));
    crearObjeto(new EscudoBendito(5));
    crearObjeto(new TalismanVelocidad(3));
    crearObjeto(new CristalMagico(4));
    crearObjeto(new TomoConocimiento(2));
    crearObjeto(new ElixirSombrio(2));
    crearObjeto(new RunaProtectora(4));

    // Objetos genéricos de ejemplo (OPCIONAL - puedes comentar esto)
    cout << "\n Agregando objetos especiales de ejemplo...\n" << endl;

    // Ejemplo 1: Poción Superior
    crearObjeto(new ObjetoGenerico(
        "PocionSuperior",
        "Poción mejorada que restaura más vida",
        3,
        "curacion",
        40,
        60,
        0
    ));

    // Ejemplo 2: Espada de Poder
    crearObjeto(new ObjetoGenerico(
        "EspadaPoder",
        "Aumenta enormemente el ataque",
        2,
        "buff_ataque",
        15,
        20,
        2
    ));

    // Ejemplo 3: Armadura Mística
    crearObjeto(new ObjetoGenerico(
        "ArmaduraMistica",
        "Protección mágica avanzada",
        2,
        "buff_defensa",
        20,
        30,
        3
    ));

    cout << "\n  Inventario inicializado con " << objetosDisponibles.size() << " tipos de objetos\n" << endl;
}

bool Inventario::crearObjeto(ObjetoMagico* objeto) {
    if (!objeto) return false;

    string nombre = objeto->getNombre();

    if (objetosDisponibles.find(nombre) != objetosDisponibles.end()) {
        cout << "  El objeto " << nombre << " ya existe" << endl;
        delete objeto;
        return false;
    }

    objetosDisponibles[nombre] = objeto;
    cout << "✓ " << nombre << " x" << objeto->getStock() << endl;
    return true;
}

void Inventario::listarObjetos() {
    if (objetosDisponibles.empty()) {
        cout << "   El inventario está vacío" << endl;
        return;
    }

    cout << "\n--------------------------------------------" << endl;
    cout << "--       INVENTARIO GLOBAL DEL TORNEO        --" << endl;
    cout << "----------------------------------------------" << endl;

    for (auto& par : objetosDisponibles) {
        ObjetoMagico* obj = par.second;
        cout << "-- " << obj->getNombre();
        int espacios = 20 - obj->getNombre().length();
        for (int i = 0; i < espacios; i++) cout << " ";
        cout << " Stock: " << obj->getStock();

        // Ajustar espacios según el número
        if (obj->getStock() < 10) cout << "           ";
        else cout << "          ";
        cout << "--" << endl;
    }

    cout << "------------------------------------------------" << endl;
}

void Inventario::listarObjetosDetallado() {
    if (objetosDisponibles.empty()) {
        cout << "   El inventario está vacío" << endl;
        return;
    }

    cout << "\n--------------------------------------------" << endl;
    cout << "     OBJETOS MAGICOS DISPONIBLES" << endl;
    cout << "-----------------------------------------------\n" << endl;

    int contador = 1;
    for (auto& par : objetosDisponibles) {
        ObjetoMagico* obj = par.second;
        cout << contador++ << ". " << obj->getNombre() << endl;
        cout << "     Descripcion: " << obj->getDescripcion() << endl;
        cout << "     Tipo: " << obj->getTipo() << endl;
        cout << "     Stock disponible: " << obj->getStock() << endl;
        cout << endl;
    }
}

ObjetoMagico* Inventario::consultarObjeto(string nombre) {
    auto it = objetosDisponibles.find(nombre);
    if (it == objetosDisponibles.end()) {
        return nullptr;
    }
    return it->second;
}

bool Inventario::actualizarStock(string nombre, int nuevoStock) {
    ObjetoMagico* obj = consultarObjeto(nombre);

    if (!obj) {
        cout << " Objeto no encontrado" << endl;
        return false;
    }

    obj->setStock(nuevoStock);
    cout << "✓ Stock de " << nombre << " actualizado a " << nuevoStock << endl;
    return true;
}

bool Inventario::eliminarObjeto(string nombre) {
    auto it = objetosDisponibles.find(nombre);

    if (it == objetosDisponibles.end()) {
        cout << "  Objeto no encontrado" << endl;
        return false;
    }

    if (it->second->getStock() > 0) {
        cout << "  No se puede eliminar: aún hay stock disponible ("
             << it->second->getStock() << " unidades)" << endl;
        cout << "   Primero debe reducir el stock a 0" << endl;
        return false;
    }

    delete it->second;
    objetosDisponibles.erase(it);

    cout << "✓ " << nombre << " eliminado del inventario" << endl;
    return true;
}

bool Inventario::asignarObjetoAHeroe(Personaje* heroe, string nombreObjeto) {
    if (!heroe) {
        cout << "  Héroe no válido" << endl;
        return false;
    }

    ObjetoMagico* obj = consultarObjeto(nombreObjeto);

    if (!obj) {
        cout << "  Objeto '" << nombreObjeto << "' no encontrado" << endl;
        return false;
    }

    if (obj->getStock() <= 0) {
        cout << "  Sin stock disponible de " << nombreObjeto << endl;
        return false;
    }

    if (!heroe->agregarObjeto(obj)) {
        return false;
    }

    obj->reducirStock();
    return true;
}

bool Inventario::retirarObjetoDeHeroe(Personaje* heroe, string nombreObjeto) {
    // Implementación básica
    ObjetoMagico* obj = consultarObjeto(nombreObjeto);
    if (obj) {
        obj->aumentarStock(1);
        cout << "✓ " << nombreObjeto << " devuelto al inventario" << endl;
        return true;
    }
    return false;
}

bool Inventario::verificarDisponibilidad(string nombre) {
    ObjetoMagico* obj = consultarObjeto(nombre);
    return (obj && obj->getStock() > 0);
}

void Inventario::limpiarObjetosUsados() {
    objetosUsados.clear();
}