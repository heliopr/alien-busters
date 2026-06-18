#ifndef PEDRA_H
#define PEDRA_H

#include "Entidades/Projetil.h"
#include <SFML/Audio.hpp>

namespace AlienBusters {
namespace Entidades {
namespace Projeteis {

class Pedra : public Projetil {
private:
    float rotacao;

    static sf::SoundBuffer bufferPedra;
    static sf::Sound somPedra;
    static bool somCarregado;

    static sf::Texture texturaPedra;
    static bool texturaCarregada;

public:
    Pedra(float x = 0.f, float y = 0.f, float vx = 0.f, float vy = 0.f,
          Personagens::Jogador* dono = 0, bool inimigo = false);
    ~Pedra();

    void executar(float dt);
    sf::FloatRect getHitbox() const;
    void quicar();
};

}
}
}

#endif
