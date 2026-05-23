#include <cmath>

#include "Entidades/Jogador.h"

namespace Entidades {

Jogador::Jogador() : Entidade() {
    x = 100;
    y = 100;
    pFig = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    pFig->setFillColor(sf::Color(100, 150, 255));
    pFig->setPosition(sf::Vector2f(x, y));
}

Jogador::~Jogador() {
    if (pFig) {
        delete pFig;
        pFig = 0;
    }
}

void Jogador::executar(float dt) {
    int velocidade = 5;
    int dx = 0, dy = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dx -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dx += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dy -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dy += 1;

    double d = std::sqrt(dx*dx + dy*dy);
    if (d > 0) {
        x += (velocidade * (dx/d)) * dt;
        y += (velocidade * (dy/d)) * dt;
    }

    if (pFig) {
        pFig->setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
    }

    desenhar(); // TODO: REMOVER
}

void Jogador::salvar() {
}

}
