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
    Gosma(float x, float y);
    ~Gosma();

    void executar(float dt);
    void salvar();
    std::string serializar() const;
    void obstaculizar(Personagens::Jogador* p);

    bool colide() const { return false; }
    sf::FloatRect getHitbox() const;
};

}
}
}

#endif
