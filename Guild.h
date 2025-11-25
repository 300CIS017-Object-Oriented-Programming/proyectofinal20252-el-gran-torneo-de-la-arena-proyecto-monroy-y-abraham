//
// Created by Usuario on 25/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_GUILD_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_GUILD_H


#include <string>
#include <unordered_map>
#include <vector>
#include "Personaje.h"
#include "Inventario.h" // Se añade para tiendaObjetos

using namespace std;

class Guild {
private:
    string nombreGuild;
    unordered_map<string, Personaje*> heroes;
    int contadorHeroes;
    int victorias;
    int monedas;
    int puntos;

public:
    Guild(string nombre);
    ~Guild();

    void inicializarHeroes();
    bool agregarHeroe(Personaje* heroe);
    bool eliminarHeroe(string id);
    Personaje* consultarHeroe(string id);
    Personaje* buscarHeroe(string nombre);
    void listarHeroes();

    vector<Personaje*> getHeroesVivos();
    bool todosHeroesMuertos();
    int contarHeroesVivos();
    void incrementarVictorias();
    void mostrarEstadisticas();

    // metodos economicos y tienda
    void tiendaHeroes();
    void tiendaObjetos(Inventario* inventario); // Necesita el inventario global
    void incrementarMonedas(int cantidad);
    void incrementarPuntos(int cantidad);

    // Getters
    string getNombre() const { return nombreGuild; }
    unordered_map<string, Personaje*> getHeroes() { return heroes; }
    int getVictorias() const { return victorias; }
    int getMonedas() const { return monedas; }
    int getPuntos() const { return puntos; }

private:
    string generarID();
};



#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_GUILD_H