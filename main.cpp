//
// Created by Jesus Esteban Monroy on 25/11/2025.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

#include "Guild.h"
#include "Inventario.h"
#include "Arena.h"
#include "Guerrero.h"
#include "Mago.h"
#include "Sanador.h"
#include "Paladin.h"
#include "Arquero.h"
#include "ObjetoGenerico.h"

using namespace std;

// Limpia la pantalla simulando un clear
void limpiarPantalla() {
    for (int i = 0; i < 50; i++) cout << '\n';
}

void pausa() {
    cout << "\n[Presiona Enter para continuar...]";
    cin.get();
}

// Lee enteros de forma segura desde stdin
int leerEntero() {
    string entrada;
    while (true) {
        getline(cin, entrada);

        if (entrada.empty()) {
            continue;
        }

        try {
            return stoi(entrada);
        } catch (...) {
            return -1;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Iniciando sistema..." << endl;

    // Inicializar Guild y Inventario
    Guild* miGuild = new Guild("Los Aventureros");
    miGuild->inicializarHeroes();

    Inventario* miInventario = new Inventario();
    miInventario->inicializarObjetos();

    bool salirDelJuego = false;

    while (!salirDelJuego) {
        limpiarPantalla();

        cout << "================================" << endl;
        cout << "        MENU PRINCIPAL          " << endl;
        cout << "================================" << endl;
        cout << "1. Gestionar Heroes" << endl;
        cout << "2. Inventario" << endl;
        cout << "3. Tienda de Heroes" << endl;
        cout << "4. Tienda de Objetos" << endl;
        cout << "5. IR A LA ARENA (Pelear)" << endl;
        cout << "6. Ver Estadisticas" << endl;
        cout << "7. Salir" << endl;
        cout << "================================" << endl;
        cout << "Elige una opcion: ";

        int opcion = leerEntero();

        switch (opcion) {
            // --- GESTION DE HEROES ---
            case 1: {
                bool salirSub = false;
                while (!salirSub) {
                    limpiarPantalla();
                    cout << "--- GESTION DE HEROES ---" << endl;
                    cout << "1. Ver lista de heroes" << endl;
                    cout << "2. Ver detalles de un heroe" << endl;
                    cout << "3. Despedir a un heroe" << endl;
                    cout << "4. Volver al menu principal" << endl;
                    cout << "Opcion: ";

                    int opH = leerEntero();

                    if (opH == 1) {
                        miGuild->listarHeroes();
                        pausa();
                    }
                    else if (opH == 2) {
                        miGuild->listarHeroes();
                        cout << "\nEscribe el ID del heroe (ej: heroe_1): ";
                        string id;
                        getline(cin, id);

                        Personaje* p = miGuild->consultarHeroe(id);
                        if (p)
                            p->mostrarEstado();
                        else
                            cout << "Heroe no encontrado." << endl;

                        pausa();
                    }
                    else if (opH == 3) {
                        miGuild->listarHeroes();
                        cout << "\nID del heroe a despedir: ";
                        string id;
                        getline(cin, id);
                        cout << "¿Seguro que lo despides? (s/n): ";
                        string r;
                        getline(cin, r);
                        if (r == "s" || r == "S")
                            miGuild->eliminarHeroe(id);
                        pausa();
                    }
                    else if (opH == 4) {
                        salirSub = true;
                    }
                }
                break;
            }

            // --- INVENTARIO ---
            case 2: {
                bool salirInv = false;
                while (!salirInv) {
                    limpiarPantalla();
                    cout << "--- INVENTARIO ---" << endl;
                    cout << "1. Ver objetos" << endl;
                    cout << "2. Equipar objeto a heroe" << endl;
                    cout << "3. Volver" << endl;
                    cout << "Opcion: ";

                    int opI = leerEntero();

                    if (opI == 1) {
                        miInventario->listarObjetosDetallado();
                        pausa();
                    }
                    else if (opI == 2) {
                        miGuild->listarHeroes();
                        cout << "ID del heroe: ";
                        string id;
                        getline(cin, id);
                        Personaje* p = miGuild->consultarHeroe(id);

                        if (p) {
                            miInventario->listarObjetos();
                            cout << "Nombre EXACTO del objeto: ";
                            string nom;
                            getline(cin, nom);
                            miInventario->asignarObjetoAHeroe(p, nom);
                        } else {
                            cout << "No existe ese heroe." << endl;
                        }
                        pausa();
                    }
                    else if (opI == 3) {
                        salirInv = true;
                    }
                }
                break;
            }

            // --- TIENDA DE HEROES ---
            case 3:
                limpiarPantalla();
                miGuild->tiendaHeroes();
                break;

            // --- TIENDA DE OBJETOS ---
            case 4:
                limpiarPantalla();
                miGuild->tiendaObjetos(miInventario);
                break;

            // --- ARENA ---
            case 5: {
                limpiarPantalla();
                cout << "--- ARENA DE COMBATE ---" << endl;

                if (miGuild->todosHeroesMuertos()) {
                    cout << "Tus heroes estan muertos. Ve a la Tienda." << endl;
                } else {
                    cout << "Heroes listos: " << miGuild->contarHeroesVivos() << endl;
                    cout << "¿Entrar al combate? (s/n): ";
                    string r;
                    getline(cin, r);

                    if (r == "s" || r == "S") {
                        Arena* arena = new Arena(miGuild, miInventario);
                        arena->inicializarEnemigos();
                        arena->prepararCombate();
                        arena->iniciarCombate();
                        delete arena;
                    }
                }
                pausa();
                break;
            }

            // --- ESTADISTICAS ---
            case 6:
                limpiarPantalla();
                miGuild->mostrarEstadisticas();
                pausa();
                break;

            // --- SALIR ---
            case 7:
                salirDelJuego = true;
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion no valida." << endl;
                pausa();
                break;
        }
    }

    delete miGuild;
    delete miInventario;
    return 0;
}
