#ifndef GOSMA_H
#define GOSMA_H

#include "Entidades/Obstaculo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Obstaculos {

class Gosma : public Obstaculo {
private:
    float largura;
    float altura;
    sf::Texture textura;
    float tempoLentidao;

public:
    Gosma(float x, float y);
    ~Gosma();

    void executar(float dt);
    void salvar();
    void obstaculizar(Personagens::Jogador* p);

    sf::FloatRect getHitbox() const;
};

}
}

#endif
