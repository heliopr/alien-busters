#ifndef SLIME_H
#define SLIME_H

#include "Entidades/Inimigo.h"
#include "Entidades/AnimacaoSprite.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Personagens {

class Slime : public Inimigo {
private:
    float nivel;
    AnimacaoSprite animacao;

public:
    Slime(float x = 400.f, float y = 300.f);
    ~Slime();

    void executar(float dt);
    void salvar();
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;
};

}
}

#endif
