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
}

Personaje::~Personaje() {
    objetosEquipados.clear();
    efectosActivos.clear();
}

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
    if (vida > vidaMaxima) {
        vida = vidaMaxima;
    }

    cout << "   [HEAL] " << nombre << " recupera " << cantidad << " puntos de vida" << endl;
    cout << "   [HP] Vida actual: " << vida << "/" << vidaMaxima << endl;
}

bool Personaje::estaVivo() const {
    return vivo && vida > 0;
}

bool Personaje::agregarObjeto(ObjetoMagico* objeto) {
    if (objetosEquipados.size() >= 2) {
        cout << "   [!] " << nombre << " ya tiene 2 objetos equipados" << endl;
        return false;
    }

    objetosEquipados.push_back(objeto);
    cout << "   [OK] " << objeto->getNombre() << " equipado a " << nombre << endl;
    return true;
}

bool Personaje::usarObjeto(int indice) {
    if (indice < 0 || indice >= objetosEquipados.size()) {
        cout << "   [!] Indice de objeto invalido" << endl;
        return false;
    }

    ObjetoMagico* objeto = objetosEquipados[indice];

    if (objeto->fueUsado()) {
        cout << "   [!] Este objeto ya fue usado" << endl;
        return false;
    }

    cout << "   [ITEM] " << nombre << " usa " << objeto->getNombre() << "!" << endl;
    objeto->usar(this);

    return true;
}

void Personaje::aplicarEfecto(string tipo, int valor, int duracion) {
    Efecto nuevoEfecto;
    nuevoEfecto.tipo = tipo;
    nuevoEfecto.valor = valor;
    nuevoEfecto.turnosRestantes = duracion;

    efectosActivos.push_back(nuevoEfecto);

    if (tipo == "ataque") {
        ataque += valor;
        cout << "   [BUFF] Ataque aumentado: " << ataqueOriginal << " -> " << ataque
             << " (+" << valor << ") por " << duracion << " turnos" << endl;
    } else if (tipo == "defensa") {
        defensa += valor;
        cout << "   [BUFF] Defensa aumentada: " << defensaOriginal << " -> " << defensa
             << " (+" << valor << ") por " << duracion << " turnos" << endl;
    }
}

void Personaje::actualizarEfectos() {
    for (int i = efectosActivos.size() - 1; i >= 0; i--) {
        efectosActivos[i].turnosRestantes--;

        if (efectosActivos[i].turnosRestantes <= 0) {
            string tipo = efectosActivos[i].tipo;
            int valor = efectosActivos[i].valor;

            if (tipo == "ataque") {
                ataque -= valor;
                cout << "   [INFO] Efecto de ataque de " << nombre << " termino" << endl;
            } else if (tipo == "defensa") {
                defensa -= valor;
                cout << "   [INFO] Efecto de defensa de " << nombre << " termino" << endl;
            }

            efectosActivos.erase(efectosActivos.begin() + i);
        }
    }
}

void Personaje::resetearEstadisticas() {
    ataque = ataqueOriginal;
    defensa = defensaOriginal;
    efectosActivos.clear();
}

void Personaje::mostrarEstado() const {
    cout << "----------------------------------------" << endl;
    cout << "  " << nombre << " (" << rol << ") - Nivel " << nivel << endl;
    cout << "----------------------------------------" << endl;
    cout << "  Vida: " << vida << "/" << vidaMaxima << endl;
    cout << "  Ataque: " << ataque;
    if (ataque != ataqueOriginal) cout << " (" << ataqueOriginal << ")";
    cout << endl;
    cout << "  Defensa: " << defensa;
    if (defensa != defensaOriginal) cout << " (" << defensaOriginal << ")";
    cout << endl;
    cout << "  Objetos: " << objetosEquipados.size() << "/2" << endl;

    if (!efectosActivos.empty()) {
        cout << "  Efectos activos: " << efectosActivos.size() << endl;
    }

    cout << "----------------------------------------" << endl;
}

int Personaje::calcularDanioBase(Personaje* objetivo) {
    int danioBase = ataque - objetivo->getDefensa();
    if (danioBase < 0) danioBase = 0;

    danioBase = aplicarVariacionAleatoria(danioBase, 10);

    return danioBase;
}

int Personaje::aplicarVariacionAleatoria(int valor, int porcentaje) {
    int variacion = (valor * porcentaje) / 100;
    int ajuste = (rand() % (variacion * 2 + 1)) - variacion;
    return valor + ajuste;
}