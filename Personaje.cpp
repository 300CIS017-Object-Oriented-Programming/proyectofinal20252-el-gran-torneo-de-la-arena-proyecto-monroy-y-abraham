//
// Created by Usuario on 21/11/2025.
//

#include "Personaje.h"
#include "ObjetoMagico.h"
#include <iostream>

using namespace std;

Personaje::Personaje(string nombre, int nivel, int vida, int ataque, int defensa, string rol) {
    this->nombre = nombre;
    this->nivel = nivel;
    this->vida = vida;
    this->vidaMaxima = vida;
    this->ataque = ataque;
    this->ataqueOriginal = ataque;
    this->defensa = defensa;
    this->defensaOriginal = defensa;
    this->vivo = true;
    this->rol = rol;

    // XP empieza en 0
    this->experiencia = 0;

    // --- AJUSTE DE DIFICULTAD ---
    // Formula estandar: Nivel * 100.
    // Nivel 1 pide 100 XP.
    this->experienciaNecesaria = 100 * nivel;
}

Personaje::~Personaje() {
    objetosEquipados.clear();
    efectosActivos.clear();
}

// --- SISTEMA DE NIVEL ---

void Personaje::ganarExperiencia(int cantidad) {
    if (!vivo) return;

    experiencia += cantidad;
    cout << " > " << nombre << " gana " << cantidad << " XP." << endl;

    // Bucle por si sube varios niveles de golpe
    while (experiencia >= experienciaNecesaria) {
        experiencia -= experienciaNecesaria;
        subirNivel();
    }

    // Mostrar barra de progreso
    cout << "   [Progreso Nvl " << nivel+1 << ": " << experiencia << "/" << experienciaNecesaria << "]" << endl;
}

void Personaje::subirNivel() {
    nivel++;
    // Cada nivel es mas dificil de alcanzar (factor 150)
    experienciaNecesaria = nivel * 150;

    // Aumentos de estadisticas
    int aumentoVida = 15 + (nivel * 2);
    int aumentoAtaque = 3;
    int aumentoDefensa = 2;

    vidaMaxima += aumentoVida;
    vida = vidaMaxima; // Curacion total al subir
    ataqueOriginal += aumentoAtaque;
    ataque = ataqueOriginal;
    defensaOriginal += aumentoDefensa;
    defensa = defensaOriginal;

    cout << "\n   *****************************************" << endl;
    cout << "   * ¡LEVEL UP! " << nombre << " sube a Nivel " << nivel << "! *" << endl;
    cout << "   * HP Max: " << vidaMaxima << " (+" << aumentoVida << ")" << endl;
    cout << "   * Ataque: " << ataque << " (+" << aumentoAtaque << ")" << endl;
    cout << "   *****************************************\n" << endl;
}

// --- RESTO DE METODOS ---

void Personaje::recibirDanio(int danio) {
    if (danio < 0) danio = 0;
    vida -= danio;
    if (vida <= 0) {
        vida = 0;
        vivo = false;
        cout << "   [X] " << nombre << " ha sido derrotado!" << endl;
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

bool Personaje::agregarObjeto(ObjetoMagico* objeto) {
    if (objetosEquipados.size() >= 2) {
        cout << "   [!] Inventario lleno (Max 2)." << endl;
        return false;
    }
    objetosEquipados.push_back(objeto);
    cout << "   [OK] " << objeto->getNombre() << " equipado." << endl;
    return true;
}

bool Personaje::usarObjeto(int indice) {
    if (indice < 0 || indice >= objetosEquipados.size()) return false;
    ObjetoMagico* objeto = objetosEquipados[indice];

    if (objeto->fueUsado()) {
        cout << "   [!] Objeto ya usado." << endl;
        return false;
    }

    cout << "   [ITEM] " << nombre << " usa " << objeto->getNombre() << endl;
    objeto->usar(this);
    return true;
}

void Personaje::aplicarEfecto(string tipo, int valor, int duracion) {
    Efecto nuevo = {tipo, valor, duracion};
    efectosActivos.push_back(nuevo);

    if (tipo == "ataque") {
        ataque += valor;
        cout << "   [BUFF] Ataque sube a " << ataque << " por " << duracion << " turnos." << endl;
    } else if (tipo == "defensa") {
        defensa += valor;
        cout << "   [BUFF] Defensa sube a " << defensa << " por " << duracion << " turnos." << endl;
    }
}

void Personaje::actualizarEfectos() {
    for (int i = efectosActivos.size() - 1; i >= 0; i--) {
        efectosActivos[i].turnosRestantes--;
        if (efectosActivos[i].turnosRestantes <= 0) {
            if (efectosActivos[i].tipo == "ataque") ataque -= efectosActivos[i].valor;
            else if (efectosActivos[i].tipo == "defensa") defensa -= efectosActivos[i].valor;

            cout << "   [INFO] El efecto de " << efectosActivos[i].tipo << " termino." << endl;
            efectosActivos.erase(efectosActivos.begin() + i);
        }
    }
}

void Personaje::mostrarEstado() const {
    cout << "--------------------------------" << endl;
    cout << nombre << " (" << rol << ") NVL " << nivel << endl;
    cout << "HP: " << vida << "/" << vidaMaxima << " | XP: " << experiencia << "/" << experienciaNecesaria << endl;
    cout << "ATK: " << ataque << " | DEF: " << defensa << endl;
    cout << "--------------------------------" << endl;
}

int Personaje::calcularDanioBase(Personaje* objetivo) {
    int danio = ataque - objetivo->getDefensa();
    if (danio < 0) danio = 0;
    return aplicarVariacionAleatoria(danio, 10);
}

int Personaje::aplicarVariacionAleatoria(int valor, int porcentaje) {
    int variacion = (valor * porcentaje) / 100;
    if (variacion == 0) return valor;
    int ajuste = (rand() % (variacion * 2 + 1)) - variacion;
    return valor + ajuste;
}