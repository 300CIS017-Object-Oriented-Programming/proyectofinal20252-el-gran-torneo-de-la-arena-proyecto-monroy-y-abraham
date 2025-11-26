//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ARENA_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ARENA_H


#include <vector>
#include <string>
#include "Guild.h"
#include "Oponente.h"
#include "Inventario.h"

using namespace std;

class Arena {
private:
    Guild* guild;
    vector<Oponente*> enemigos;
    Inventario* inventario;
    int turnoActual;
    int objetosUsadosTotal;
    vector<string> registroCombate;
    bool combateActivo;
    string equipoGanador;

public:
    Arena(Guild* guild, Inventario* inv);
    ~Arena();

    void inicializarEnemigos();
    void prepararCombate();
    void distribuirObjetos();
    void iniciarCombate();
    void mostrarResumen();

    int getTurnoActual() const { return turnoActual; }
    int getObjetosUsados() const { return objetosUsadosTotal; }

private:
    void ejecutarTurno();
    void turnoHeroes();
    void turnoEnemigos();
    bool verificarFinCombate();
    string determinarGanador();
    void registrarAccion(string accion);
    void mostrarEstadoCombate();
    void actualizarEfectosTodos();
    vector<Personaje*> getEnemigosVivos();

    void asignarObjetoAleatorioAEnemigo(Oponente* enemigo);
    void asignarObjetosAleatoriosAHeroes();
    bool deberiaUsarObjeto(Personaje* personaje, ObjetoMagico* objeto);
};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_ARENA_H