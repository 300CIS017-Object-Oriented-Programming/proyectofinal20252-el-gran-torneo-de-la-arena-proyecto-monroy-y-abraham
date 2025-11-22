//
// Created by Jesus Esteban Monroy on 21/11/2025.
//

#ifndef PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_GUERRERO_H
#define PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_GUERRERO_H
#include "Personaje.h"

class Guerrero : public Personaje {
private:
    float probabilidadCritico;
    float multiplicadorCritico;

    // recuro furia
    // (Funciona inverso al cansancio: necesita acumularla para usar el especial)
    int furia;
    int furiaMaxima;
public:
    Guerrero(string nombre, int nivel);
    ~Guerrero();

    int atacar(Personaje* objetivo) override;
    void realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) override;

private:
    bool intentarGolpeCritico();
    void generarFuria(int cantidad);
};


#endif //PROYECTOFINAL20252_EL_GRAN_TORNEO_DE_LA_ARENA_PROYECTO_MONROY_Y_ABRAHAM_GUERRERO_H