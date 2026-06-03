#ifndef OBST_MEDIO_H
#define OBST_MEDIO_H

#include "Entidades/Obstaculo.h"

namespace Entidades {

class Obst_Medio : public Obstaculo {
private:
    float largura;
    float altura;

public:
    Obst_Medio(float x, float y, float largura = 120.f, float altura = 80.f);
    ~Obst_Medio();

    void executar(float dt);
    void salvar();
    void obstaculizar(Jogador* p);

    sf::FloatRect getLimitesColisao() const;
};

}

#endif
