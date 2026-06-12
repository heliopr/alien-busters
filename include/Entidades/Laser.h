#ifndef LASER_H
#define LASER_H

#include "Entidades/Projetil.h"

namespace Entidades {

class Laser : public Projetil {
public:
    Laser(float x = 0.f, float y = 0.f, float vx = 0.f, float vy = 0.f, Personagens::Jogador* dono = 0);
    ~Laser();

    sf::FloatRect getHitbox() const;
};

}

#endif
