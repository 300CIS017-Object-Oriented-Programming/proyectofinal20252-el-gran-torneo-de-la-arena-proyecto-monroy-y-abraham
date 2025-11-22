//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_SANADOR_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_SANADOR_H
#incliude "Perosnaje.h"

class Sanador : public Personaje {
private:
    int curacionBase;
    float efectividadMin;
    float efectividadMax;

    // RECURSO: MANA
    int mana;
    int manaMaximo;

public:
    Sanador(string nombre, int nivel);
    ~Sanador();

    int atacar(Personaje* objetivo) override;
    void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) override;



};

#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_SANADOR_H