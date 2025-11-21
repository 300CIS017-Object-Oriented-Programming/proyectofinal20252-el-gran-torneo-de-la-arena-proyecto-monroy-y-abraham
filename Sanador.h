#ifndef UNTITLED1_SANADOR_H
#define UNTITLED1_SANADOR_H
#include "Personaje.h"

class sanador :public Personaje {
private
    int curacion;
    float efectividadMin;
    float efectividadMax;
    // recurso mana
    int mana;
    int manaMaximo;
public:
    Sanador(string nombre, int nivel);
    ~Sanador();

    int atacar(personaje* objetivo) override;
    void realizarAccion(vector<Personaje*>& aliados, vector<personaje*>& enemigos) override;

private:
    int curarAliado(Personaje* aliado);
    float calcularEfectividad();
    // No necesita mas metodos privados complejo