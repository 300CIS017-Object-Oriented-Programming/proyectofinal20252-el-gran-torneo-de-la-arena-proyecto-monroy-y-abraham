//
// Created by Usuario on 15/11/2025.
//

#ifndef UNTITLED1_PERSONAJE_H
#define UNTITLED1_PERSONAJE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;


class ObjetoMagico;

// Estructura para efectos temporales
struct Efecto {
    string tipo;           // "ataque", "defensa"
    int valor;
    int turnosRestantes;
};

class Personaje {
protected:
    string nombre;
    int nivel;
    int vida;
    int vidaMaxima;
    int ataque;
    int ataqueOriginal;
    int defensa;
    int defensaOriginal;
    bool vivo;
    string rol;

    // atributos para la experiencia del personaje
    int experiencia;
    int experienciaNecesaria;

    vector<ObjetoMagico*> objetosEquipados;
    vector<Efecto> efectosActivos;

public:
    // Constructor y destructor
    Personaje(string nombre, int nivel, int vida, int ataque, int defensa, string rol);
    virtual ~Personaje();

    // Métodos virtuales (implemetantacion polimorfismo)
    virtual int atacar(Personaje* objetivo) = 0;
    virtual void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) = 0;

    // Métodos de cada personaje
    void recibirDanio(int danio);
    void curar(int cantidad);
    bool estaVivo() const;

    // Gestión de Objetos
    bool agregarObjeto(ObjetoMagico* objeto);
    bool usarObjeto(int indice);

    // Efectos
    void aplicarEfecto(string tipo, int valor, int duracion);
    void actualizarEfectos();
    void resetearEstadisticas();

    // metodo para ganar experiencia y subir el nivel
    void ganarExperiencia(int cantidad);
    void subirNivel();

    void mostrarEstado() const;

    // Getters obtener
    string getNombre() const { return nombre; }
    int getNivel() const { return nivel; }
    int getVida() const { return vida; }
    int getVidaMaxima() const { return vidaMaxima; }
    int getAtaque() const { return ataque; }
    int getDefensa() const { return defensa; }
    string getRol() const { return rol; }
    vector<ObjetoMagico*> getObjetos() const { return objetosEquipados; }

    // Setters
    void setVida(int v) { vida = v; }
    void setAtaque(int a) { ataque = a; }
    void setDefensa(int d) { defensa = d; }

protected:
    int calcularDanioBase(Personaje* objetivo);
    int aplicarVariacionAleatoria(int valor, int porcentaje = 10);
};

#endif //UNTITLED1_PERSONAJE_H