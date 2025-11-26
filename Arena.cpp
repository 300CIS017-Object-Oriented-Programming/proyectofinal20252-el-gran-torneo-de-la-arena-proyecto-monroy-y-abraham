//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#include "Arena.h"

#include "Arena.h"
#include "ObjetoGenerico.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// Lectura segura de enteros
int leerIntArena() {
    string linea;
    while (true) {
        std::getline(cin, linea);
        if (linea.empty()) continue;
        try {
            return std::stoi(linea);
        } catch (...) {
            return -1;
        }
    }
}

// Constructor
Arena::Arena(Guild* guild, Inventario* inv) {
    this->guild = guild;
    this->inventario = inv;
    turnoActual = 0;
    objetosUsadosTotal = 0;
    combateActivo = false;
    equipoGanador = "";
}

// Destructor
Arena::~Arena() {
    for (size_t i = 0; i < enemigos.size(); i++) {
        delete enemigos[i];
    }
    enemigos.clear();
}

// Configuración de enemigos
void Arena::inicializarEnemigos() {
    cout << "\n=== GENERACION DE OPONENTES ===\n";

    cout << "¿Cuantos enemigos desea enfrentar? (1-6): ";
    int numEnemigos = leerIntArena();
    if (numEnemigos < 1) numEnemigos = 1;
    if (numEnemigos > 6) numEnemigos = 6;

    cout << "\nSeleccione la dificultad:\n";
    cout << " 1. Facil\n";
    cout << " 2. Normal\n";
    cout << " 3. Dificil\n";
    cout << "Opcion: ";

    int dificultad = leerIntArena();

    int nivelMin = 1;
    float multiplicadorStats = 1.0f;

    switch (dificultad) {
        case 1:
            nivelMin = 1;
            multiplicadorStats = 0.8f;
            break;
        case 2:
            nivelMin = 3;
            multiplicadorStats = 1.0f;
            break;
        case 3:
            nivelMin = 5;
            multiplicadorStats = 1.3f;
            break;
        default:
            nivelMin = 3;
            multiplicadorStats = 1.0f;
            break;
    }

    cout << "\n[INFO] Generando " << numEnemigos << " oponentes...\n\n";

    string roles[]   = {"Guerrero", "Mago", "Sanador"};
    string nombres[] = {"Goblin", "Orco", "Esqueleto", "Bandido", "Lobo"};

    for (int i = 0; i < numEnemigos; i++) {
        string nombre = nombres[std::rand() % 5] + " " + std::to_string(i + 1);
        string rol    = roles[std::rand() % 3];

        int nivel   = nivelMin + (std::rand() % 3);
        int vida    = static_cast<int>((60 + nivel * 12) * multiplicadorStats);
        int ataque  = static_cast<int>((18 + nivel * 3)  * multiplicadorStats);
        int defensa = static_cast<int>((12 + nivel * 2)  * multiplicadorStats);

        Oponente* enemigo = new Oponente(nombre, nivel, vida, ataque, defensa, rol);

        if (std::rand() % 100 < 50) {
            asignarObjetoAleatorioAEnemigo(enemigo);
        }

        enemigos.push_back(enemigo);
        cout << " [ENEMIGO] " << nombre << " (" << rol << ") - Nivel " << nivel << endl;
    }

    cout << "\n[OK] Enemigos listos para el combate.\n";
}

void Arena::asignarObjetoAleatorioAEnemigo(Oponente* enemigo) {
    ObjetoMagico* pocion = new ObjetoGenerico(
        "Pocion Oscura", "Restaura salud", 1, "curacion", 30, 50, 0
    );
    enemigo->agregarObjeto(pocion);
}

bool Arena::deberiaUsarObjeto(Personaje* p, ObjetoMagico* o) {
    if (!o || o->fueUsado()) return false;
    if (o->getTipo() == "curacion" && p->getVida() < p->getVidaMaxima() / 2) return true;
    return false;
}

// Preparar combate: mostrar héroes y equipar objetos
void Arena::prepararCombate() {
    cout << "\n=== PREPARACION DEL COMBATE ===\n\n";

    cout << "[INFO] TUS HEROES:\n";
    auto todosHeroes = guild->getHeroes();
    int contador = 1;
    for (auto& par : todosHeroes) {
        Personaje* h = par.second;
        if (h->estaVivo()) {
            cout << " " << contador++ << ". " << h->getNombre()
                 << " (" << h->getRol() << ") - NV " << h->getNivel() << endl;
        }
    }

    cout << "\n¿Equipar objetos de forma aleatoria? (s/n): ";
    string r;
    std::getline(cin, r);

    if (r == "s" || r == "S") {
        asignarObjetosAleatoriosAHeroes();
    } else {
        cout << "\nEquipamiento manual...\n";
        distribuirObjetos();
    }

    cout << "\n[OK] Todo listo. Presiona ENTER para empezar la batalla...";
    cin.get();
}


// Equipamiento manual
void Arena::distribuirObjetos() {
    bool equipando = true;

    while (equipando) {
        cout << "\n--- EQUIPAMIENTO MANUAL ---\n";
        cout << "1. Equipar un objeto a un heroe\n";
        cout << "2. Terminar\n";
        cout << "Opcion: ";

        int op = leerIntArena();

        if (op == 2) {
            equipando = false;
        } else if (op == 1) {

            cout << "\n--- SELECCIONA UN HEROE ---\n";
            auto heroesMap = guild->getHeroes();
            vector<Personaje*> listaHeroes;
            int i = 1;

            for (auto par : heroesMap) {
                if (par.second->estaVivo()) {
                    cout << i << ". " << par.second->getNombre()
                         << " [Items: " << par.second->getObjetos().size() << "/2]\n";
                    listaHeroes.push_back(par.second);
                    i++;
                }
            }

            cout << "Numero del heroe: ";
            int hIdx = leerIntArena();

            if (hIdx > 0 && hIdx <= static_cast<int>(listaHeroes.size())) {
                Personaje* heroeElegido = listaHeroes[hIdx - 1];

                cout << "\n--- INVENTARIO DISPONIBLE ---\n";
                inventario->listarObjetos();

                cout << "Nombre del objeto a equipar: ";
                string nombreObj;
                std::getline(cin, nombreObj);

                inventario->asignarObjetoAHeroe(heroeElegido, nombreObj);
            } else {
                cout << "Heroe no valido.\n";
            }

        } else {
            cout << "Opcion no valida.\n";
        }
    }

    cout << "Equipamiento finalizado.\n";
}

// Equipamiento automático
void Arena::asignarObjetosAleatoriosAHeroes() {
    auto heroes = guild->getHeroes();
    auto items  = inventario->getObjetosDisponibles();

    if (items.empty()) {
        cout << "No tienes objetos para equipar.\n";
        return;
    }

    int count = 0;
    for (auto par : heroes) {
        Personaje* h = par.second;
        if (h->estaVivo() && h->getObjetos().size() < 2) {

            ObjetoMagico* obj = items[std::rand() % items.size()];

            if (obj->getStock() > 0) {
                if (inventario->asignarObjetoAHeroe(h, obj->getNombre())) {
                    count++;
                }
            }
        }
    }

    cout << "Se han equipado " << count << " objetos aleatoriamente.\n";
}

// Bucle principal de combate
void Arena::iniciarCombate() {
    combateActivo = true;
    turnoActual = 0;

    while (combateActivo) {
        ejecutarTurno();

        if (verificarFinCombate()) {
            combateActivo = false;
            mostrarResumen();
        }
    }
}

void Arena::ejecutarTurno() {
    turnoActual++;
    cout << "\n======= TURNO " << turnoActual << " =======\n";

    actualizarEfectosTodos();

    cout << ">>> TUS HEROES <<<\n";
    turnoHeroes();

    if (verificarFinCombate()) return;

    cout << "\n>>> ENEMIGOS (Enter) <<<";
    cin.get();

    turnoEnemigos();
}

// Turno de los héroes
void Arena::turnoHeroes() {
    auto misHeroes    = guild->getHeroesVivos();
    auto enemigosVivos = getEnemigosVivos();

    for (auto h : misHeroes) {
        if (h->estaVivo() && !enemigosVivos.empty()) {

            h->realizarAccion(misHeroes, enemigosVivos);

            enemigosVivos = getEnemigosVivos();
            if (enemigosVivos.empty()) break;

            cout << "(Enter para siguiente heroe...)";
            cin.get();
        }
    }
}

// Turno de los enemigos
void Arena::turnoEnemigos() {
    auto misHeroes = guild->getHeroesVivos();

    for (auto e : enemigos) {
        if (e->estaVivo() && !misHeroes.empty()) {

            bool uso = false;
            auto objs = e->getObjetos();

            for (size_t i = 0; i < objs.size(); i++) {
                if (deberiaUsarObjeto(e, objs[i])) {
                    cout << "[IA] " << e->getNombre()
                         << " usa " << objs[i]->getNombre() << endl;
                    e->usarObjeto(static_cast<int>(i));
                    uso = true;
                    break;
                }
            }

            if (!uso) {
                vector<Personaje*> susAliados = getEnemigosVivos();
                e->realizarAccion(susAliados, misHeroes);
            }

            misHeroes = guild->getHeroesVivos();
            if (misHeroes.empty()) break;
        }
    }

    cout << "\nFin del turno enemigo. Enter...";
    cin.get();
}

// Verificar fin del combate
bool Arena::verificarFinCombate() {
    if (getEnemigosVivos().empty()) {
        equipoGanador = "Guild del jugador";
        guild->incrementarVictorias();
        return true;
    }
    if (guild->todosHeroesMuertos()) {
        equipoGanador = "Enemigos";
        return true;
    }
    return false;
}

// Resumen final del combate
void Arena::mostrarResumen() {
    cout << "\n--- FIN DEL COMBATE ---\n";

    int oro  = 0;
    int ptos = 0;

    if (equipoGanador == "Guild del jugador") {
        cout << "VICTORIA. Ganaste la pelea.\n";

        oro  = 100 + static_cast<int>(enemigos.size()) * 20;
        ptos = 50;

        int xpGanada = 30 + static_cast<int>(enemigos.size()) * 15;
        cout << "\n--- EXPERIENCIA ---\n";

        vector<Personaje*> sobrevivientes = guild->getHeroesVivos();
        for (auto h : sobrevivientes) {
            h->ganarExperiencia(xpGanada);
        }

    } else {
        cout << "DERROTA. Tus heroes cayeron.\n";
        oro  = 10;
        ptos = 5;
    }

    guild->incrementarMonedas(oro);
    guild->incrementarPuntos(ptos);

    cout << "\nRecompensas: " << oro << " monedas | " << ptos << " puntos.\n";
    cout << "Presiona Enter para salir...";
    cin.get();
}

// Métodos placeholder
void Arena::registrarAccion(string) {}
void Arena::mostrarEstadoCombate() {}
string Arena::determinarGanador() { return equipoGanador; }

// Actualizar efectos en todos
void Arena::actualizarEfectosTodos() {
    for (auto h : guild->getHeroesVivos()) {
        h->actualizarEfectos();
    }
    for (auto e : enemigos) {
        if (e->estaVivo()) e->actualizarEfectos();
    }
}

// Obtener enemigos vivos
vector<Personaje*> Arena::getEnemigosVivos() {
    vector<Personaje*> v;
    for (auto e : enemigos) {
        if (e->estaVivo()) v.push_back(e);
    }
    return v;
}