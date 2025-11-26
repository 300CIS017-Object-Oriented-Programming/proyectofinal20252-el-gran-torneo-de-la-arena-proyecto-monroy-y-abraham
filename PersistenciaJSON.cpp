//
// Created by Usuario on 26/11/2025.
//

#include "PersistenciaJSON.h"

#include "persistenciaJSON.h"
#include "Guerrero.h"
#include "Mago.h"
#include "Sanador.h"
#include "Paladin.h"
#include "Arquero.h"
#include "ObjetoGenerico.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Funcion auxiliar para limpiar texto del JSON
string limpiarValor(string valor) {
    valor.erase(remove(valor.begin(), valor.end(), '\"'), valor.end());
    valor.erase(remove(valor.begin(), valor.end(), ','), valor.end());
    size_t first = valor.find_first_not_of(" \t");
    if (string::npos == first) return valor;
    size_t last = valor.find_last_not_of(" \t");
    return valor.substr(first, (last - first + 1));
}

void GestorArchivos::guardarPartida(Guild* guild, Inventario* inventario) {
    ofstream archivo("partida.json");

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo crear el archivo." << endl;
        return;
    }

    archivo << "{\n";

    // Economia
    archivo << "  \"monedas\": " << guild->getMonedas() << ",\n";
    archivo << "  \"puntos\": " << guild->getPuntos() << ",\n";

    // Heroes
    archivo << "  \"heroes\": [\n";
    auto heroes = guild->getHeroes();
    int i = 0;
    for (auto par : heroes) {
        Personaje* h = par.second;
        if (h->estaVivo()) {
            archivo << "    {\n";
            archivo << "      \"nombre\": \"" << h->getNombre() << "\",\n";
            archivo << "      \"rol\": \"" << h->getRol() << "\",\n";
            archivo << "      \"nivel\": " << h->getNivel() << ",\n";
            archivo << "      \"vida\": " << h->getVida() << ",\n";
            archivo << "      \"experiencia\": " << h->getExperiencia() << "\n";

            archivo << "    }";
            if (i < heroes.size() - 1) archivo << ",";
            archivo << "\n";
        }
        i++;
    }
    archivo << "  ],\n";

    // Inventario
    archivo << "  \"inventario\": [\n";
    vector<ObjetoMagico*> objetos = inventario->getObjetosDisponibles();
    for (size_t j = 0; j < objetos.size(); j++) {
        archivo << "    { \"nombre\": \"" << objetos[j]->getNombre() << "\", \"tipo\": \"" << objetos[j]->getTipo() << "\" }";
        if (j < objetos.size() - 1) archivo << ",";
        archivo << "\n";
    }
    archivo << "  ]\n";

    archivo << "}\n";
    archivo.close();
    cout << "[EXITO] Partida guardada correctamente." << endl;
}

bool GestorArchivos::cargarPartida(Guild* guild, Inventario* inventario) {
    ifstream archivo("partida.json");
    if (!archivo.is_open()) {
        cout << "[ERROR] No existe archivo de guardado." << endl;
        return false;
    }

    string linea;
    string tempRol, tempNombre;
    int tempNivel = 1, tempVida = 100, tempXP = 0;

    cout << "Cargando datos..." << endl;

    while (getline(archivo, linea)) {
        // Cargar Economia
        if (linea.find("\"monedas\":") != string::npos) {
            string valor = linea.substr(linea.find(":") + 1);
            int m = stoi(limpiarValor(valor));
            guild->incrementarMonedas(-guild->getMonedas());
            guild->incrementarMonedas(m);
        }
        if (linea.find("\"puntos\":") != string::npos) {
            string valor = linea.substr(linea.find(":") + 1);
            int p = stoi(limpiarValor(valor));
            guild->incrementarPuntos(-guild->getPuntos());
            guild->incrementarPuntos(p);
        }

        // Cargar Datos de Heroes
        if (linea.find("\"nombre\":") != string::npos) {
            tempNombre = limpiarValor(linea.substr(linea.find(":") + 1));
        }
        if (linea.find("\"rol\":") != string::npos) {
            tempRol = limpiarValor(linea.substr(linea.find(":") + 1));
        }
        if (linea.find("\"nivel\":") != string::npos) {
            string v = linea.substr(linea.find(":") + 1);
            tempNivel = stoi(limpiarValor(v));
        }
        if (linea.find("\"vida\":") != string::npos) {
            string v = linea.substr(linea.find(":") + 1);
            tempVida = stoi(limpiarValor(v));
        }
        if (linea.find("\"experiencia\":") != string::npos) {
            string v = linea.substr(linea.find(":") + 1);
            tempXP = stoi(limpiarValor(v));
        }

        // Procesar Heroe al cerrar la llave }
        if (linea.find("}") != string::npos && !tempNombre.empty() && !tempRol.empty()) {

            // Buscamos si el heroe YA EXISTE (Caso Arthos/Selene)
            Personaje* existente = guild->buscarHeroe(tempNombre);

            if (existente != nullptr) {
                // SI EXISTE: ACTUALIZAMOS SUS DATOS
                existente->setVida(tempVida);
                existente->setNivel(tempNivel); // Actualizamos nivel
                existente->setExperiencia(tempXP); // Actualizamos XP
                cout << " - Actualizado: " << tempNombre << " (Nvl " << tempNivel << ", XP " << tempXP << ")" << endl;
            }
            else {
                // SI NO EXISTE: LO CREAMOS NUEVO
                Personaje* nuevo = nullptr;
                if (tempRol == "Guerrero") nuevo = new Guerrero(tempNombre, tempNivel);
                else if (tempRol == "Mago") nuevo = new Mago(tempNombre, tempNivel);
                else if (tempRol == "Sanador") nuevo = new Sanador(tempNombre, tempNivel);
                else if (tempRol == "Paladin") nuevo = new Paladin(tempNombre, tempNivel);
                else if (tempRol == "Arquero") nuevo = new Arquero(tempNombre, tempNivel);

                if (nuevo) {
                    nuevo->setVida(tempVida);
                    nuevo->setExperiencia(tempXP);
                    guild->agregarHeroe(nuevo);
                    cout << " - Recuperado: " << tempNombre << " (Nvl " << tempNivel << ", XP " << tempXP << ")" << endl;
                }
            }
            // Resetear temporales
            tempNombre = ""; tempRol = ""; tempXP = 0; tempNivel = 1;
        }
    }

    archivo.close();
    cout << "[CARGADO] Datos restaurados correctamente." << endl;
    return true;
}