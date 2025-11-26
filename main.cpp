#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

// Incluimos todas tus clases
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

// --- FUNCIONES DE UTILIDAD (PARA QUE NO FALLE EL MENU) ---

// Funcion para limpiar la pantalla "a la fuerza" (imprimiendo lineas vacias)
// Esto arregla el error visual de que el menu salga incompleto.
void limpiarPantalla() {
    // Imprimimos 50 saltos de linea para limpiar
    for(int i = 0; i < 50; i++) cout << endl;
}

// Pausa simple
void pausa() {
    cout << "\n[Presiona Enter para continuar...]";
    cin.get();
}

// ESTA FUNCION ES LA SOLUCION AL ERROR:
// Lee un numero de forma segura. Si das Enter vacio, espera.
// Si escribes letras, devuelve -1 para que no se rompa.
int leerEntero() {
    string entrada;
    while (true) {
        getline(cin, entrada);

        // Si el usuario solo dio Enter sin escribir nada, seguimos esperando
        if (entrada.empty()) {
            continue;
        }

        try {
            return stoi(entrada); // Intenta convertir a numero
        } catch (...) {
            return -1; // Si escribio letras o basura
        }
    }
}

// --- PROGRAMA PRINCIPAL ---

int main() {
    srand(time(nullptr));

    cout << "Iniciando sistema..." << endl;

    // 1. Inicializamos Gremio y Inventario
    Guild* miGuild = new Guild("Los Aventureros");
    miGuild->inicializarHeroes();

    Inventario* miInventario = new Inventario();
    miInventario->inicializarObjetos();

    bool salirDelJuego = false;

    // 2. Bucle del Menu
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
        cout << "7. guardar partida" << endl;
        cout << "8. cargar partida" << endl;
        cout << "9. Salir" << endl;
        cout << "================================" << endl;
        cout << "Elige una opcion: ";

        // Usamos la funcion segura. Nunca mas fallara por un Enter.
        int opcion = leerEntero();

        switch (opcion) {
            case 1: { // MENU HEROES
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
                        string id; getline(cin, id);

                        Personaje* p = miGuild->consultarHeroe(id);
                        if (p) p->mostrarEstado();
                        else cout << "Heroe no encontrado." << endl;
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

            case 2: { // MENU INVENTARIO
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
                        cout << "ID del heroe: "; string id; getline(cin, id);
                        Personaje* p = miGuild->consultarHeroe(id);

                        if (p) {
                            miInventario->listarObjetos();
                            cout << "Nombre EXACTO del objeto: "; string nom; getline(cin, nom);
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

            case 3:
                limpiarPantalla();
                miGuild->tiendaHeroes();
                // La tienda tiene su propia pausa interna normalmente
                break;

            case 4:
                limpiarPantalla();
                miGuild->tiendaObjetos(miInventario);
                break;

            case 5: { // ARENA
                limpiarPantalla();
                cout << "--- ARENA DE COMBATE ---" << endl;
                if (miGuild->todosHeroesMuertos()) {
                    cout << "Tus heroes estan muertos. Ve a la Tienda." << endl;
                } else {
                    cout << "Heroes listos: " << miGuild->contarHeroesVivos() << endl;
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

            case 6:
                limpiarPantalla();
                miGuild->mostrarEstadisticas();
                pausa();
                break;



            case 9:
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