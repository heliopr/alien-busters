#include "Entidades/Projetil.h"

namespace Entidades {

Projetil::Projetil(float x, float y, float vx, float vy) : Entidade(), ativo(true), vx(vx), vy(vy) {
    this->x = x;
    this->y = y;
    
    pFig = new sf::RectangleShape(sf::Vector2f(10.f, 10.f));
    if (pFig != NULL) {
        pFig->setOrigin(5.f, 5.f);
        pFig->setPosition(sf::Vector2f(x, y));
        static_cast<sf::RectangleShape*>(pFig)->setFillColor(sf::Color::Yellow);
    }
}

Projetil::~Projetil() {}

void Projetil::salvar() {
    // TODO
}

void Projetil::executar(float dt) {
    if (!ativo) return;

    x += vx * dt;
    y += vy * dt;

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }

    if (x < -1000.f || x > 5000.f || y > 3000.f || y < -1000.f) {
        ativo = false;
    }
}

sf::FloatRect Projetil::getLimitesColisao() const {
    return sf::FloatRect(x - 5.f, y - 5.f, 10.f, 10.f);
}

}