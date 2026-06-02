#include "Entidades/Chao.h"
#include <cstddef>

namespace Entidades {

Chao::Chao(float x, float y, float largura, float altura) : 
    Obstaculo(), altura(altura), largura(largura) 
{
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color(145, 60, 25));
    }
}

Chao::~Chao() {
}

void Chao::executar(float dt) {
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Chao::obstaculizar(Jogador *p) {
}

void Chao::salvar() {
    // TODO
}

sf::FloatRect Chao::getLimitesColisao() const {
    return sf::FloatRect(x, y, largura, altura);
}

}