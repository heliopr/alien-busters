#include "Entidades/Laser.h"

namespace Entidades {

Laser::Laser(float x, float y, float vx, float vy, Personagens::Jogador* dono)
    : Projetil(x, y, vx, vy, dono) {

    pFig = new sf::RectangleShape(sf::Vector2f(20.f, 6.f));
    if (pFig != NULL) {
        pFig->setOrigin(10.f, 3.f);
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color::Red);
    }
}

Laser::~Laser() {}

sf::FloatRect Laser::getHitbox() const {
    return sf::FloatRect(x - 10.f, y - 3.f, 20.f, 6.f);
}

}
