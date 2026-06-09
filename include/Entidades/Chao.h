#ifndef CHAO_H
#define CHAO_H

#include "Entidades/Obstaculo.h"

namespace Entidades {
namespace Obstaculos {

class Chao : public Obstaculo {
private:
    float altura;
    float largura;

public:
    Chao(float x, float y, float largura, float altura);
    ~Chao();

    void executar(float dt);
    void salvar();
    void obstaculizar(Personagens::Jogador *p);
    sf::FloatRect getHitbox() const;
};

}
}

#endif
