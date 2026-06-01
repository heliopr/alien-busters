#include "Entidades/Plataforma.h"
#include <cstddef>

namespace Entidades {

Plataforma::Plataforma(float x, float y, float largura, float altura) 
    : Obstaculo(), altura(altura), largura(largura) {
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color(145, 60, 25));
    }
}

Plataforma::~Plataforma() {
}

void Plataforma::executar(float) {
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Plataforma::obstaculizar(Jogador*) {
    // TODO
}

sf::FloatRect Plataforma::getLimitesColisao() const {
    return sf::FloatRect(x, y, largura, altura);
}

void Plataforma::salvar() {   
}

}