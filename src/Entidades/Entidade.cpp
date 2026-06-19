#include "Entidades/Entidade.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

namespace AlienBusters {
namespace Entidades {

Entidade::Entidade() : Ente(), x(0.0f), y(0.0f), vy(0.0f) {
    pFig = NULL;
}

Entidade::~Entidade() {
    if (pFig) {
        delete pFig;
        pFig = NULL;
    }
}

void Entidade::desenhar() {
    Ente::desenhar();
    if (pGG && pGG->getMostrarHitboxes()) {
        pGG->desenharRetangulo(getHitbox(), sf::Color::Red, 2.f);
    }
}

void Entidade::salvarDataBuffer() {
    buffer << x << " " << y;
}

float Entidade::getX() const {
    return x;
}

void Entidade::setX(float novoX) {
    x = novoX;
    if (pFig) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

float Entidade::getY() const {
    return y;
}

void Entidade::setY(float novoY) {
    y = novoY;
    if (pFig) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

float Entidade::getVy() const {
    return vy;
}

void Entidade::setVy(float v) {
    vy = v;
}

void Entidade::aplicarGravidade(float dt, float gravidade) {
    vy += gravidade * dt;
    y += vy * dt;
}

void Entidade::contrariarGravidade(float dt) {
    y -= vy * dt;
    vy = 0.f;
}

}
}