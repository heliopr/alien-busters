#ifndef SLIME_H
#define SLIME_H

#include "Entidades/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace AlienBusters {
namespace Entidades {
namespace Personagens {

class Slime : public Inimigo {
private:
    float nivel;

public:
    Slime(float x = 0.f, float y = 0.f);
    ~Slime();

    void executar(float dt = 0.f);
    void salvar();
    void danificar(Jogador* p);
    int pontosAoMorrer() const;
    sf::FloatRect getHitbox() const;

    float getNivel() const;
    void setNivel(float n);
};

}
}
}

#endif
