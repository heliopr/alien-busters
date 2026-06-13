#ifndef GOLEM_H
#define GOLEM_H

#include "Entidades/Inimigo.h"
#include "Entidades/AnimacaoSprite.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Personagens {

class Golem : public Inimigo {
private:
    AnimacaoSprite animacao;

public:
    Golem(float x = 400.f, float y = 300.f);
    ~Golem();

    void executar(float dt);
    void salvar();
    void mover();
    sf::FloatRect getHitbox() const;
};

}
}

#endif
