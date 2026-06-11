#include "Entidades/Demonio.h"
#include <cstdlib>
#include <cstddef>

namespace Entidades {
namespace Personagens {

Demonio::Demonio(float x_ini, float y_ini)
    : Inimigo()
{
    x = x_ini;
    y = y_ini;

    float v = 40.f + std::rand() % 40;
    velocidadeX = (std::rand() % 2 == 0) ? v : -v;

    pFig = new sf::RectangleShape(sf::Vector2f(64.f, 64.f));
    if (pFig != NULL) {
        pFig->setOrigin(32.f, 32.f);
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color::Red);
    }
}

Demonio::~Demonio() {
}

void Demonio::executar(float dt) {
    moverComGravidade(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Demonio::salvar() {
}

void Demonio::mover() {
}

sf::FloatRect Demonio::getHitbox() const {
    return sf::FloatRect(x - 32.f, y - 32.f, 64.f, 64.f);
}

}
}
