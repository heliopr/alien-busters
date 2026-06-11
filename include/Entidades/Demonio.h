#ifndef DEMONIO_H
#define DEMONIO_H

#include "Entidades/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Personagens {

class Demonio : public Inimigo {
public:
    Demonio(float x = 400.f, float y = 300.f);
    ~Demonio();

    void executar(float dt);
    void salvar();
    void mover();
    sf::FloatRect getHitbox() const;
};

}
}

#endif
