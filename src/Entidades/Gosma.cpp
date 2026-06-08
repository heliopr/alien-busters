#include "Entidades/Gosma.h"
#include "Entidades/Jogador.h"
#include <cstddef>

namespace Entidades {

Gosma::Gosma(float x, float y, float largura, float altura)
    : Obstaculo(), largura(largura), altura(altura) {
    this->x = x;
    this->y = y;
    danoso = false;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color(50, 50, 200, 160));
    }
}

Gosma::~Gosma() {
}

void Gosma::executar(float dt) {
}

void Gosma::salvar() {
}

void Gosma::obstaculizar(Jogador* p) {
    if (p == NULL) return;

    if (p->getLimitesColisao().intersects(getLimitesColisao())) {
        p->ficarLento(3.0f);
    }
}

sf::FloatRect Gosma::getLimitesColisao() const {
    return sf::FloatRect(x, y, largura, altura);
}

}
