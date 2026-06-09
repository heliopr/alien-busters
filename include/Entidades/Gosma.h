#ifndef GOSMA_H
#define GOSMA_H

#include "Entidades/Obstaculo.h"

namespace Entidades {
namespace Obstaculos {

class Gosma : public Obstaculo {
private:
    float largura;
    float altura;

public:
    Gosma(float x, float y, float largura = 120.f, float altura = 80.f);
    ~Gosma();

    void executar(float dt);
    void salvar();
    void obstaculizar(Personagens::Jogador* p);

    sf::FloatRect getHitbox() const;
};

}
}

#endif
