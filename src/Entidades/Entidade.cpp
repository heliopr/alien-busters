#include "Entidades/Entidade.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

namespace Entidades {

Entidade::Entidade() : Ente(), x(0.0f), y(0.0f) {
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
        pGG->desenharRetangulo(getLimitesColisao(), sf::Color::Red, 2.f);
    }
}

void Entidade::salvarDataBuffer() {
    
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

}