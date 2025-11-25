//
// Created by Usuario on 21/11/2025.
//

#include "Personaje.h"
#include "ObjetoMagico.h"
#include <iostream>
#include <vector>
#include <cstdlib>


using namespace std;

Personaje::Personaje(std::string nombre, int nivel, int vida, int ataque, int defensa, std::string rol)
    : nombre(nombre),
      nivel(nivel),
      vida(vida),
      vidaMaxima(vida),
      ataque(ataque),
      ataqueOriginal(ataque),
      defensa(defensa),
      defensaOriginal(defensa),
      vivo(true),
      rol(rol),
      experiencia(0),
      experienciaNecesaria(100 * nivel) {  // XP base por nivel
}

Personaje::~Personaje() {
    objetosEquipados.clear();
    efectosActivos.clear();
}


// --- SISTEMA DE EXPERIENCIA Y NIVEL ---

void Personaje::ganarExperiencia(int cantidad) {
    if (!vivo) return;

    experiencia += cantidad;
    cout << " > " << nombre << " gana " << cantidad << " XP." << endl;

    // Por si sube más de un nivel de golpe
    while (experiencia >= experienciaNecesaria) {
        experiencia -= experienciaNecesaria;
        subirNivel();
    }

    cout << "   [Progreso Nvl " << (nivel + 1)
         << ": " << experiencia << "/" << experienciaNecesaria << "]" << endl;
}

void Personaje::subirNivel() {
    nivel++;

    // Cada nuevo nivel exige más XP
    experienciaNecesaria = nivel * 150;

    int aumentoVida    = 15 + (nivel * 2);
    int aumentoAtaque  = 3;
    int aumentoDefensa = 2;

    vidaMaxima      += aumentoVida;
    vida             = vidaMaxima;      // Se cura al subir de nivel
    ataqueOriginal  += aumentoAtaque;
    ataque           = ataqueOriginal;
    defensaOriginal += aumentoDefensa;
    defensa          = defensaOriginal;

    cout << "\n   ***********************************" << endl;
    cout << "   * LEVEL UP: " << nombre
         << " sube a Nivel " << nivel << " *" << endl;
    cout << "   * HP Max: " << vidaMaxima
         << " (+" << aumentoVida << ")" << endl;
    cout << "   * Ataque: " << ataque
         << " (+" << aumentoAtaque << ")" << endl;
    cout << "   * Defensa: " << defensa
         << " (+" << aumentoDefensa << ")" << endl;
    cout << "   ***********************************\n" << endl;
}

// --- VIDA, DAÑO Y CURACIÓN ---

void Personaje::recibirDanio(int danio) {
    if (danio < 0) danio = 0;

    vida -= danio;

    if (vida <= 0) {
        vida = 0;
        vivo = false;
        cout << "   [X] " << nombre << " ha sido derrotado." << endl;
    }
}

void Personaje::curar(int cantidad) {
    if (!vivo) return;

    vida += cantidad;
    if (vida > vidaMaxima) vida = vidaMaxima;

    cout << "   [+] " << nombre << " recupera " << cantidad << " HP." << endl;
}

bool Personaje::estaVivo() const {
    return vivo && vida > 0;
}

// --- INVENTARIO Y OBJETOS ---

bool Personaje::agregarObjeto(ObjetoMagico* objeto) {
    if (objetosEquipados.size() >= 2) {
        cout << "   [!] Inventario lleno (máx. 2 objetos)." << endl;
        return false;
    }

    objetosEquipados.push_back(objeto);
    cout << "   [OK] " << objeto->getNombre() << " equipado." << endl;
    return true;
}

bool Personaje::usarObjeto(int indice) {
    if (indice < 0 || indice >= static_cast<int>(objetosEquipados.size()))
        return false;

    ObjetoMagico* objeto = objetosEquipados[indice];

    if (objeto->fueUsado()) {
        cout << "   [!] Objeto ya usado." << endl;
        return false;
    }

    cout << "   [ITEM] " << nombre << " usa " << objeto->getNombre() << endl;
    objeto->usar(this);
    return true;
}

// --- EFECTOS (BUFFS / DEBUFFS) ---

void Personaje::aplicarEfecto(std::string tipo, int valor, int duracion) {
    Efecto nuevo = { tipo, valor, duracion };
    efectosActivos.push_back(nuevo);

    if (tipo == "ataque") {
        ataque += valor;
        cout << "   [BUFF] Ataque sube a " << ataque
             << " por " << duracion << " turnos." << endl;
    } else if (tipo == "defensa") {
        defensa += valor;
        cout << "   [BUFF] Defensa sube a " << defensa
             << " por " << duracion << " turnos." << endl;
    }
}

void Personaje::actualizarEfectos() {
    for (int i = static_cast<int>(efectosActivos.size()) - 1; i >= 0; --i) {
        efectosActivos[i].turnosRestantes--;

        if (efectosActivos[i].turnosRestantes <= 0) {

            if (efectosActivos[i].tipo == "ataque") {
                ataque -= efectosActivos[i].valor;
            } else if (efectosActivos[i].tipo == "defensa") {
                defensa -= efectosActivos[i].valor;
            }

            cout << "   [INFO] El efecto de "
                 << efectosActivos[i].tipo << " terminó." << endl;

            efectosActivos.erase(efectosActivos.begin() + i);
        }
    }
}

// --- STATUS DEL PERSONAJE ---

void Personaje::mostrarEstado() const {
    cout << "--------------------------------" << endl;
    cout << nombre << " (" << rol << ")  NVL " << nivel << endl;
    cout << "HP: " << vida << "/" << vidaMaxima << endl;
    cout << "XP: " << experiencia << "/" << experienciaNecesaria << endl;
    cout << "ATK: " << ataque << " | DEF: " << defensa << endl;
    cout << "--------------------------------" << endl;
}

// --- CÁLCULOS DE DAÑO ---

int Personaje::calcularDanioBase(Personaje* objetivo) {
    int danio = ataque - objetivo->getDefensa();
    if (danio < 0) danio = 0;
    return aplicarVariacionAleatoria(danio, 10);
}

int Personaje::aplicarVariacionAleatoria(int valor, int porcentaje) {
    int variacion = (valor * porcentaje) / 100;
    if (variacion == 0) return valor;

    int rango = variacion * 2 + 1;
    int ajuste = (std::rand() % rango) - variacion;

    return valor + ajuste;
}