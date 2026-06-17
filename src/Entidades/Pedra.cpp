#include "Entidades/Pedra.h"
#include <iostream>

namespace Entidades {
namespace Projeteis {

sf::SoundBuffer Pedra::bufferPedra;
sf::Sound Pedra::somPedra;
bool Pedra::somCarregado = false;

sf::Texture Pedra::texturaPedra;
bool Pedra::texturaCarregada = false;

Pedra::Pedra(float x, float y, float vx, float vy, Personagens::Jogador* dono, bool inimigo)
    : Projetil(x, y, vx, vy, dono, inimigo), rotacao(0.f) {

    sofreGravidade = true;
    quicavel = true;

    if (!texturaCarregada) {
        if (texturaPedra.loadFromFile("assets/textures/pedra.png")) {
            texturaCarregada = true;
        } else {
            std::cerr << "Erro ao carregar textura assets/textures/pedra.png!" << std::endl;
        }
    }

    pFig = new sf::RectangleShape(sf::Vector2f(30.f, 30.f));
    if (pFig != NULL) {
        pFig->setOrigin(15.f, 15.f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (texturaCarregada) {
            pFig->setTexture(&texturaPedra);
        } else {
            pFig->setFillColor(sf::Color(128, 128, 128));
        }
    }

    if (!somCarregado) {
        if (bufferPedra.loadFromFile("assets/sounds/pedra.mp3")) {
            somPedra.setBuffer(bufferPedra);
            somCarregado = true;
        } else {
            std::cerr << "Erro ao carregar som assets/sounds/pedra.mp3!" << std::endl;
        }
    }

    if (somCarregado) {
        somPedra.play();
    }
}

Pedra::~Pedra() {}

void Pedra::executar(float dt) {
    Projetil::executar(dt);

    if (pFig != NULL) {
        rotacao += 180.f * dt;
        pFig->setRotation(rotacao);
    }
}

sf::FloatRect Pedra::getHitbox() const {
    return sf::FloatRect(x - 15.f, y - 15.f, 30.f, 30.f);
}

void Pedra::quicar() {
    if (somCarregado) {
        somPedra.play();
    }
}

}
}
