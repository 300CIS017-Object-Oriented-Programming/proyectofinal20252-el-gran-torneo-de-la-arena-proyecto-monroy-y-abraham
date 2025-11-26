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

// Limpia la pantalla "simulada"
void limpiarPantalla() {
    for (int i = 0; i < 50; i++) cout << '\n';
}

void pausa() {
    cout << "\n[Presiona Enter para continuar...]";
    cin.get();
}

// Lee enteros de forma segura
int leerEntero() {
    string entrada;
    while (true) {
        getline(cin, entrada);
        if (entrada.empty()) continue;

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

    // Inicializar sistema
    Guild* miGuild = new Guild("Los Aventureros");
    miGuild->inicializarHeroes();

    Inventario* miInventario = new Inventario();
    miInventario->inicializarObjetos();

    bool salirDelJuego = false;

    while (!salirDelJuego) {
        limpiarPantalla();

        cout << "================================\n";
        cout << "        MENU PRINCIPAL          \n";
        cout << "================================\n";
        cout << "1. Gestionar Heroes\n";
        cout << "2. Inventario\n";
        cout << "3. Tienda de Heroes\n";
        cout << "4. Tienda de Objetos\n";
        cout << "5. Ir a la Arena (Pelear)\n";
        cout << "6. Ver Estadisticas\n";
        cout << "7. Salir\n";
        cout << "================================\n";
        cout << "Elige una opcion: ";

        int opcion = leerEntero();

        switch (opcion) {

            // --- GESTION DE HEROES ---
            case 1: {
                bool salirSub = false;
                while (!salirSub) {
                    limpiarPantalla();
                    cout << "--- GESTION DE HEROES ---\n";
                    cout << "1. Ver lista de heroes\n";
                    cout << "2. Ver detalles de un heroe\n";
                    cout << "3. Despedir a un heroe\n";
                    cout << "4. Volver\n";
                    cout << "Opcion: ";

                    int opH = leerEntero();

                    if (opH == 1) {
                        miGuild->listarHeroes();
                        pausa();
                    }
                    else if (opH == 2) {
                        miGuild->listarHeroes();
                        cout << "\nID del heroe (ej: heroe_1): ";
                        string id; getline(cin, id);

                        Personaje* p = miGuild->consultarHeroe(id);
                        if (p) p->mostrarEstado();
                        else cout << "Heroe no encontrado.\n";
                        pausa();
                    }
                    else if (opH == 3) {
                        miGuild->listarHeroes();
                        cout << "\nID del heroe a despedir: ";
                        string id; getline(cin, id);
                        cout << "¿Seguro que lo despides? (s/n): ";
                        string r; getline(cin, r);
                        if (r == "s" || r == "S") miGuild->eliminarHeroe(id);
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
                    cout << "--- INVENTARIO ---\n";
                    cout << "1. Ver objetos\n";
                    cout << "2. Equipar objeto a heroe\n";
                    cout << "3. Volver\n";
                    cout << "Opcion: ";

                    int opI = leerEntero();

                    if (opI == 1) {
                        miInventario->listarObjetosDetallado();
                        pausa();
                    }
                    else if (opI == 2) {
                        miGuild->listarHeroes();
                        cout << "ID del heroe: ";
                        string id; getline(cin, id);
                        Personaje* p = miGuild->consultarHeroe(id);

                        if (p) {
                            miInventario->listarObjetos();
                            cout << "Nombre EXACTO del objeto: ";
                            string nom; getline(cin, nom);
                            miInventario->asignarObjetoAHeroe(p, nom);
                        } else {
                            cout << "No existe ese heroe.\n";
                        }
                        pausa();
                    }
                    else if (opI == 3) {
                        salirInv = true;
                    }
                }
                break;
            }

            // --- TIENDA HEROES ---
            case 3:
                limpiarPantalla();
                miGuild->tiendaHeroes();
                break;

            // --- TIENDA OBJETOS ---
            case 4:
                limpiarPantalla();
                miGuild->tiendaObjetos(miInventario);
                break;

            // --- ARENA ---
            case 5: {
                limpiarPantalla();
                cout << "--- ARENA DE COMBATE ---\n";

                if (miGuild->todosHeroesMuertos()) {
                    cout << "Tus heroes estan muertos. Ve a la tienda.\n";
                } else {
                    cout << "Heroes vivos: " << miGuild->contarHeroesVivos() << endl;
                    cout << "¿Entrar al combate? (s/n): ";
                    string r; getline(cin, r);

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
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
                pausa();
                break;
        }
    }

    delete miGuild;
    delete miInventario;
    return 0;
}
