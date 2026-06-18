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

    void executar(float dt);
    void salvar();
    std::string serializar() const;
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;
};

}
}
}

#endif
