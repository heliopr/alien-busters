#include "Entidades/Chao.h"
#include <cstddef>

namespace Entidades {
namespace Obstaculos {

Chao::Chao(float x, float y, float largura, float altura, sf::Color cor) :
    Obstaculo(), altura(altura), largura(largura)
{
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(cor);
    }
}

Chao::~Chao() {
}

void Chao::executar(float dt) {
    sofrerGravidade(dt);
    contrariarGravidade(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Chao::obstaculizar(Personagens::Jogador *p) {
}

void Chao::salvar() {
    // TODO
}

sf::FloatRect Chao::getHitbox() const {
    return sf::FloatRect(x, y, largura, altura);
}

}
}
