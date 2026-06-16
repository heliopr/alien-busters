#ifndef ALIEN_H
#define ALIEN_H

#include "Entidades/Inimigo.h"
#include "Entidades/AnimacaoSprite.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Personagens {

class Alien : public Inimigo {
private:
    float velocidade;
    AnimacaoSprite animacao;
    bool olhandoDireita;

public:
    Alien(float x = 400.f, float y = 300.f);
    ~Alien();

    void executar(float dt);
    void salvar();
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;
};

}
}

#endif
