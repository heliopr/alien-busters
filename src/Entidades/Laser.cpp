#include "Entidades/Laser.h"
#include <iostream>

namespace Entidades {

sf::SoundBuffer Laser::bufferLaser;
sf::Sound Laser::somLaser;
bool Laser::somCarregado = false;

Laser::Laser(float x, float y, float vx, float vy, Personagens::Jogador* dono)
    : Projetil(x, y, vx, vy, dono) {

    pFig = new sf::RectangleShape(sf::Vector2f(20.f, 6.f));
    if (pFig != NULL) {
        pFig->setOrigin(10.f, 3.f);
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color::Red);
    }

    if (!somCarregado) {
        if (bufferLaser.loadFromFile("assets/sounds/laser.wav")) {
            somLaser.setBuffer(bufferLaser);
            somCarregado = true;
        } else {
            std::cerr << "Erro ao carregar som assets/sounds/laser.wav!" << std::endl;
        }
    }

    if (somCarregado) {
        somLaser.play();
    }
}

Laser::~Laser() {}

sf::FloatRect Laser::getHitbox() const {
    return sf::FloatRect(x - 10.f, y - 3.f, 20.f, 6.f);
}

}
