#ifndef LASER_H
#define LASER_H

#include "Entidades/Projetil.h"
#include <SFML/Audio.hpp>

namespace Entidades {

class Laser : public Projetil {
private:
    static sf::SoundBuffer bufferLaser;
    static sf::Sound somLaser;
    static bool somCarregado;

public:
    Laser(float x = 0.f, float y = 0.f, float vx = 0.f, float vy = 0.f,
          Personagens::Jogador* dono = 0, bool inimigo = false);
    ~Laser();

    sf::FloatRect getHitbox() const;
};

}

#endif
