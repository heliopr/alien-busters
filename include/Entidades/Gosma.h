#ifndef GOSMA_H
#define GOSMA_H

#include "Entidades/Obstaculo.h"
#include <SFML/Graphics.hpp>

namespace AlienBusters {
namespace Entidades {
namespace Obstaculos {

class Gosma : public Obstaculo {
private:
    float largura;
    float altura;
    sf::Texture textura;
    float tempoLentidao;

public:
    Gosma(float x = 0.f, float y = 0.f);
    ~Gosma();

    void executar(float dt = 0.f);
    void salvar();
    void obstaculizar(Personagens::Jogador* p);

    bool colide() const { return false; }
    sf::FloatRect getHitbox() const;
};

}
}
}

#endif
