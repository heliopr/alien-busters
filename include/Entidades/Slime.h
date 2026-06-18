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
    Slime(float x = 400.f, float y = 300.f);
    ~Slime();

    void executar(float dt);
    void salvar();
    std::string serializar() const;
    void danificar(Jogador* p);
    int pontosAoMorrer() const;
    sf::FloatRect getHitbox() const;
};

}
}
}

#endif
