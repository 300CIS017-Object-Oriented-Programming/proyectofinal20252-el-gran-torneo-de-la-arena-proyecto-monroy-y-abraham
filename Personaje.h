//
// Created by Usuario on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PERSONAJE_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PERSONAJE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Forward declaration
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

    // NUEVOS ATRIBUTOS DE EXPERIENCIA
    int experiencia;
    int experienciaNecesaria;

    vector<ObjetoMagico*> objetosEquipados;
    vector<Efecto> efectosActivos;

public:
    // Constructor y destructor
    Personaje(string nombre, int nivel, int vida, int ataque, int defensa, string rol);
    virtual ~Personaje();

    // Métodos virtuales puros
    virtual int atacar(Personaje* objetivo) = 0;
    virtual void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) = 0;

    // Métodos comunes
    void recibirDanio(int danio);
    void curar(int cantidad);
    bool estaVivo() const;

    // Gestión de Objetos
    bool agregarObjeto(ObjetoMagico* objeto);
    bool usarObjeto(int indice);

    // Efectos
    void aplicarEfecto(string tipo, int valor, int duracion);
    void actualizarEfectos();
    void resetearEstadisticas(); // Vuelve stats a la normalidad tras batalla

    // NUEVOS METODOS DE NIVEL
    void ganarExperiencia(int cantidad);
    void subirNivel();

    void mostrarEstado() const;

    // Getters
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

    // persisntecia json
    int getExperiencia() const { return experiencia; }
    void setExperiencia(int xp) { experiencia = xp; }
    void setNivel(int n) { nivel = n; }



protected:
    int calcularDanioBase(Personaje* objetivo);
    int aplicarVariacionAleatoria(int valor, int porcentaje = 10);
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_PERSONAJE_H