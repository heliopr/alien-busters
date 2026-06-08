#ifndef CHAO_H
#define CHAO_H

#include "Obstaculo.h"

namespace Entidades {

class Chao : public Obstaculo {
private:
    float altura;
    float largura;

public:
    Chao(float x, float y, float largura, float altura);
    ~Chao();

    void executar(float dt);
    void salvar();
    void obstaculizar(Jogador *p);
    sf::FloatRect getHitbox() const;
};

}

#endif