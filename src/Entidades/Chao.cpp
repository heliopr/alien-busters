#include "Chao.h"
#include <cstddef>

namespace Entidades {

Chao::Chao(float x, float y, float largura, float altura) : 
    Entidade(), altura(altura), largura(largura) 
{
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color(145, 60, 25)); // Retângulo Laranja Sólido do Chão
    }
}

Chao::~Chao() {
}

void Chao::executar(float dt) {
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Chao::salvar() {
}

sf::FloatRect Chao::getLimitesColisao() const {
    return sf::FloatRect(x, y, largura, altura);
}

}