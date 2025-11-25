//
// Created by Usuario on 25/11/2025.
//

#include "Guild.h"
#include "Guerrero.h"
#include "Mago.h"
#include "Sanador.h"
#include "Paladin.h"
#include "Arquero.h"
#include "ObjetoGenerico.h"
#include <iostream>

using namespace std;

Guild::Guild(string nombre) {
    this->nombreGuild = nombre;
    this->contadorHeroes = 0;
    this->victorias = 0;
    // Recursos iniciales para que el usuario pueda comprar algo al inicio
    this->monedas = 300;
    this->puntos = 50;
}

Guild::~Guild() {
    for (auto& par : heroes) {
        delete par.second;
    }
    heroes.clear();
}

void Guild::inicializarHeroes() {
    cout << "\n[INFO] Inicializando Guild \"" << nombreGuild << "\"...\n" << endl;

    // Héroes iniciales
    agregarHeroe(new Guerrero("Arthos", 1));
    agregarHeroe(new Sanador("Selene", 1));

    cout << "\n[INFO] Has recibido 2 heroes iniciales." << endl;
    cout << "[INFO] Visita la TIENDA DE HEROES para reclutar mas miembros con tus monedas.\n" << endl;
}

bool Guild::agregarHeroe(Personaje* heroe) {
    if (!heroe) {
        cout << "[!] Error: Heroe nulo" << endl;
        return false;
    }

    string id = generarID();
    heroes[id] = heroe;

    cout << "[OK] " << heroe->getNombre() << " (" << heroe->getRol()
         << ") - Nivel " << heroe->getNivel() << " [ID: " << id << "]" << endl;

    return true;
}

bool Guild::eliminarHeroe(string id) {
    auto it = heroes.find(id);

    if (it == heroes.end()) {
        cout << "[!] Heroe con ID " << id << " no encontrado" << endl;
        return false;
    }

    string nombre = it->second->getNombre();
    delete it->second;
    heroes.erase(it);

    cout << "[OK] " << nombre << " ha sido retirado de la guild" << endl;
    return true;
}

Personaje* Guild::consultarHeroe(string id) {
    auto it = heroes.find(id);

    if (it == heroes.end()) {
        return nullptr;
    }

    return it->second;
}

Personaje* Guild::buscarHeroe(string nombre) {
    for (auto& par : heroes) {
        if (par.second->getNombre() == nombre) {
            return par.second;
        }
    }
    return nullptr;
}

void Guild::listarHeroes() {
    if (heroes.empty()) {
        cout << "[!] La guild no tiene heroes" << endl;
        return;
    }

    cout << "\n=================================================" << endl;
    cout << "         HEROES DE " << nombreGuild << endl;
    cout << "=================================================" << endl;

    for (auto& par : heroes) {
        Personaje* heroe = par.second;
        cout << "[" << par.first << "] ";
        cout << heroe->getNombre() << " (" << heroe->getRol() << ")" << endl;
        cout << "  Vida: " << heroe->getVida() << "/" << heroe->getVidaMaxima();
        cout << " | Atk: " << heroe->getAtaque();
        cout << " | Def: " << heroe->getDefensa() << endl;
        cout << "-------------------------------------------------" << endl;
    }

    cout << "==================================================" << endl;
}

vector<Personaje*> Guild::getHeroesVivos() {
    vector<Personaje*> vivos;

    for (auto& par : heroes) {
        if (par.second->estaVivo()) {
            vivos.push_back(par.second);
        }
    }

    return vivos;
}

bool Guild::todosHeroesMuertos() {
    for (auto& par : heroes) {
        if (par.second->estaVivo()) {
            return false;
        }
    }
    return true;
}

int Guild::contarHeroesVivos() {
    int count = 0;
    for (auto& par : heroes) {
        if (par.second->estaVivo()) {
            count++;
        }
    }
    return count;
}

void Guild::incrementarVictorias() {
    victorias++;
}

void Guild::incrementarMonedas(int cantidad) {
    monedas += cantidad;
}

void Guild::incrementarPuntos(int cantidad) {
    puntos += cantidad;
}

void Guild::mostrarEstadisticas() {
    cout << "\n[INFO] ESTADISTICAS DE LA GUILD" << endl;
    cout << "=================================" << endl;
    cout << "Nombre: " << nombreGuild << endl;
    cout << "Heroes totales: " << heroes.size() << endl;
    cout << "Heroes vivos: " << contarHeroesVivos() << endl;
    cout << "Victorias: " << victorias << endl;
    cout << "---------------------------------" << endl;
    cout << "TESORERIA:" << endl;
    cout << "Monedas de Oro: " << monedas << endl;
    cout << "Puntos de Gremio: " << puntos << endl;
    cout << "=================================\n" << endl;
}

string Guild::generarID() {
    contadorHeroes++;
    return "heroe_" + to_string(contadorHeroes);
}

// =========================================================
//               IMPLEMENTACIÓN DE LAS TIENDAS
// =========================================================

void Guild::tiendaHeroes() {
    bool salirTienda = false;

    while (!salirTienda) {
        cout << "\n=================================================" << endl;
        cout << "              MERCADO DE MERCENARIOS             " << endl;
        cout << "=================================================" << endl;
        cout << " Tus Monedas: " << monedas << endl;
        cout << "-------------------------------------------------" << endl;
        cout << " CLASES DISPONIBLES:" << endl;
        cout << " 1. Guerrero [Tanque/Daño]   - Costo: 100 Monedas" << endl;
        cout << " 2. Mago     [Daño Magico]   - Costo: 120 Monedas" << endl;
        cout << " 3. Sanador  [Soporte/Cura]  - Costo: 80  Monedas" << endl;
        cout << " 4. Paladin  [Tanque Puro]   - Costo: 110 Monedas" << endl;
        cout << " 5. Arquero  [Daño Rapido]   - Costo: 90  Monedas" << endl;
        cout << " 0. Volver al menu principal" << endl;
        cout << "=================================================" << endl;
        cout << "Seleccione a quien desea contratar: ";

        int opcion;
        cin >> opcion;
        cin.ignore();

        if (opcion == 0) {
            salirTienda = true;
            continue;
        }

        int costo = 0;
        string rol = "";

        switch (opcion) {
            case 1: costo = 100; rol = "Guerrero"; break;
            case 2: costo = 120; rol = "Mago"; break;
            case 3: costo = 80;  rol = "Sanador"; break;
            case 4: costo = 110; rol = "Paladin"; break;
            case 5: costo = 90;  rol = "Arquero"; break;
            default:
                cout << "[!] Opcion no valida." << endl;
                continue;
        }

        if (monedas < costo) {
            cout << "\n[!] No tienes suficientes monedas. Necesitas " << costo << "." << endl;
        } else {
            cout << "\nHas elegido contratar a un " << rol << "." << endl;
            cout << "Ingrese el nombre para el nuevo heroe: ";
            string nombre;
            getline(cin, nombre);

            Personaje* nuevo = nullptr;

            if (rol == "Guerrero") nuevo = new Guerrero(nombre, 1);
            else if (rol == "Mago") nuevo = new Mago(nombre, 1);
            else if (rol == "Sanador") nuevo = new Sanador(nombre, 1);
            else if (rol == "Paladin") nuevo = new Paladin(nombre, 1);
            else if (rol == "Arquero") nuevo = new Arquero(nombre, 1);

            if (nuevo && agregarHeroe(nuevo)) {
                monedas -= costo;
                cout << "\n[$$$] Transaccion completada. Monedas restantes: " << monedas << endl;
            } else {
                delete nuevo;
            }
        }
    }
}

void Guild::tiendaObjetos(Inventario* inventario) {
    bool salirTienda = false;

    while (!salirTienda) {
        cout << "\n=================================================" << endl;
        cout << "            TIENDA DE OBJETOS MAGICOS            " << endl;
        cout << "=================================================" << endl;
        cout << " Monedas: " << monedas << " | Puntos: " << puntos << endl;
        cout << "-------------------------------------------------" << endl;
        cout << " 1. Comprar Objeto Existente (Restock) - 50 Monedas" << endl;
        cout << " 2. CREAR Objeto Personalizado         - 100 Monedas + 20 Puntos" << endl;
        cout << " 0. Volver" << endl;
        cout << "=================================================" << endl;
        cout << "Opcion: ";

        int opcion;
        cin >> opcion;
        cin.ignore();

        if (opcion == 0) {
            salirTienda = true;
            continue;
        }

        if (opcion == 1) {
            // Comprar stock de objetos existentes
            inventario->listarObjetos();
            cout << "\nIngrese el nombre exacto del objeto a comprar: ";
            string nombreObj;
            getline(cin, nombreObj);

            ObjetoMagico* obj = inventario->consultarObjeto(nombreObj);
            if (obj) {
                int precio = 50;
                if (monedas >= precio) {
                    obj->aumentarStock(1);
                    monedas -= precio;
                    cout << "\n[OK] Compraste 1 unidad de " << obj->getNombre() << endl;
                    cout << "     Nuevo stock: " << obj->getStock() << endl;
                } else {
                    cout << "[!] No tienes suficientes monedas." << endl;
                }
            } else {
                cout << "[!] Ese objeto no existe en el inventario." << endl;
            }

        } else if (opcion == 2) {
            // Crear objeto personalizado (Sistema de Crafting)
            int costoMonedas = 100;
            int costoPuntos = 20;

            if (monedas >= costoMonedas && puntos >= costoPuntos) {
                cout << "\n--- FORJA MAGICA DE OBJETOS ---" << endl;
                string nombre, desc, tipo;
                int min, max, dur;

                cout << "Nombre del nuevo objeto: ";
                getline(cin, nombre);
                cout << "Descripcion breve: ";
                getline(cin, desc);
                cout << "Tipo (curacion / buff_ataque / buff_defensa / especial): ";
                getline(cin, tipo);

                // Validación simple del tipo
                if (tipo != "curacion" && tipo != "buff_ataque" && tipo != "buff_defensa" && tipo != "especial") {
                    cout << "[!] Tipo de magia desconocido. La forja falló." << endl;
                    continue;
                }

                cout << "Potencia Minima: "; cin >> min;
                cout << "Potencia Maxima: "; cin >> max;
                cout << "Duracion (turnos, 0 si es instantaneo): "; cin >> dur;
                cin.ignore();

                ObjetoMagico* nuevoObj = new ObjetoGenerico(nombre, desc, 1, tipo, min, max, dur);

                if (inventario->crearObjeto(nuevoObj)) {
                    monedas -= costoMonedas;
                    puntos -= costoPuntos;
                    cout << "\n[OK] ¡El objeto ha sido forjado con exito!" << endl;
                } else {
                    delete nuevoObj;
                    cout << "[!] Ya existe un objeto con ese nombre." << endl;
                }

            } else {
                cout << "[!] No tienes suficientes recursos para forjar objetos." << endl;
            }
        }
    }
}