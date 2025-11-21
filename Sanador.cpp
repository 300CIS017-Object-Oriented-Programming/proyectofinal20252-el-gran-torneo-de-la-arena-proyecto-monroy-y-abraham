#include "Sanador.h"
#include <iostream>
#include <limits>

using namespace std;

Sanador::Sanador(string nombre, int nivel)
    : Personaje(nombre, nivel, 90 + (nivel * 9), 12 + nivel, 15 + nivel, "Sanador") {
    this->curacionBase = 25 + (nivel * 3);
    this->efectividadMin = 0.70f;
    this->efectividadMax = 1.2f;

    // Mana
    this->manaMaximo = 100;
    this->mana = 100;
}

Sanador::~Sanador() {}

int Sanador::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return 0;

    cout << "   [ATK] " << nombre << " golpea para robar esencia." << endl;
    int danio = calcularDanioBase(objetivo) / 2;
    if (danio < 5) danio = 5;

    cout << "   [DANIO] " << danio << " puntos." << endl;
    objetivo->recibirDanio(danio);

    // Recupera Mana al atacar
    int rec = 20;
    mana += rec;
    if (mana > manaMaximo) mana = manaMaximo;
    cout << "   [MANA] Recuperas " << rec << " de Mana." << endl;

    return danio;
}

int Sanador::curarAliado(Personaje* aliado) {
    if (!aliado || !aliado->estaVivo()) return 0;

    float efectividad = calcularEfectividad();
    int cantidad = static_cast<int>(curacionBase * efectividad);

    cout << "   [HEAL] " << nombre << " sana a " << aliado->getNombre() << endl;
    aliado->curar(cantidad);

    return cantidad;
}

float Sanador::calcularEfectividad() {
    float rango = efectividadMax - efectividadMin;
    float random = static_cast<float>(rand() % 100) / 100.0f;
    return efectividadMin + (rango * random);
}

// --- INTERACCION ---
void Sanador::realizarAccion(vector<Personaje*>& aliados, vector<Personaje*>& enemigos) {
    if (!estaVivo()) return;

    cout << "\n-- Turno de " << nombre << " (Sanador) --" << endl;
    // Barra de Mana
    cout << "Mana: " << mana << "/" << manaMaximo << " [";
    for(int i=0; i<10; i++) cout << (i < mana/10 ? "+" : " ");
    cout << "]" << endl;

    cout << "1. Ataque Drenante (Recupera 20 Mana)" << endl;

    if (mana >= 30) cout << "2. Curar Aliado (Gasta 30 Mana)" << endl;
    else cout << "2. [Sin Mana] Curar Aliado" << endl;

    cout << "3. Usar Objeto" << endl;
    cout << "Elige: ";

    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opcion == 1) {
        cout << "\n--- ATACAR A QUIEN? ---" << endl;
        for (int i = 0; i < enemigos.size(); i++) {
            cout << " " << i + 1 << ". " << enemigos[i]->getNombre()
                 << " [Vida: " << enemigos[i]->getVida() << "]" << endl;
        }
        int idx; cout << "Num: "; cin >> idx; cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Personaje* obj = (idx > 0 && idx <= enemigos.size()) ? enemigos[idx-1] : enemigos[0];
        atacar(obj);

    } else if (opcion == 2 && mana >= 30) {
        cout << "\n--- CURAR A QUIEN? ---" << endl;
        for (int i = 0; i < aliados.size(); i++) {
            cout << " " << i + 1 << ". " << aliados[i]->getNombre()
                 << " [HP: " << aliados[i]->getVida() << "/" << aliados[i]->getVidaMaxima() << "]" << endl;
        }
        int idx; cout << "Num: "; cin >> idx; cin.ignore(numeric_limits<streamsize>::max(), '\n');

        mana -= 30; // Gasto
        if (idx > 0 && idx <= aliados.size()) curarAliado(aliados[idx - 1]);
        else curarAliado(this);

    } else if (opcion == 3) {
        if (!objetosEquipados.empty()) usarObjeto(0);
        else cout << "Sin objetos." << endl;
    } else {
        cout << "Opcion no valida o falta mana." << endl;
    }
}