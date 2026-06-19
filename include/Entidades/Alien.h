#ifndef ALIEN_H
#define ALIEN_H

#include "Entidades/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace AlienBusters {
namespace Entidades {
namespace Personagens {

class Alien : public Inimigo {
private:
    float velocidade;

public:
    Alien(float x = 400.f, float y = 300.f);
    ~Alien();

    void executar(float dt = 0.f);
    void salvar();
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;

    float getVelocidade() const { return velocidade; }
    void setVelocidade(float v) { velocidade = v; velocidadeX = v; }
};

}
}
}

#endif
