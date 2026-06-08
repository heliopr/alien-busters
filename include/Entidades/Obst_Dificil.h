#ifndef OBST_DIFICIL_H
#define OBST_DIFICIL_H

#include "Entidades/Obstaculo.h"

namespace Entidades {

class Obst_Dificil : public Obstaculo {
private:
    float largura;
    float altura;
    short int danoVidas;
    bool destruido;

public:
    Obst_Dificil(float x, float y, float largura = 60.f, float altura = 60.f, short int dano = 1);
    ~Obst_Dificil();

    void executar(float dt);
    void salvar();
    void obstaculizar(Jogador* p);
    void aplicarDano(Jogador* p);

    sf::FloatRect getLimitesColisao() const;

    bool getDestruido() const { return destruido; }
    void destruir() { destruido = true; }
};

}

#endif
