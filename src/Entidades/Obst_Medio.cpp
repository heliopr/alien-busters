#include "Entidades/Obst_Medio.h"
#include "Entidades/Jogador.h"
#include <cstddef>

namespace Entidades {

Obst_Medio::Obst_Medio(float x, float y, float largura, float altura)
    : Obstaculo(), largura(largura), altura(altura) {
    this->x = x;
    this->y = y;
    danoso = false;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color(120, 50, 200, 160));
        pFig->setOutlineColor(sf::Color(180, 100, 255, 220));
        pFig->setOutlineThickness(2.f);
    }
}

Obst_Medio::~Obst_Medio() {
}

void Obst_Medio::executar(float dt) {
}

void Obst_Medio::salvar() {
}

void Obst_Medio::obstaculizar(Jogador* p) {
}

sf::FloatRect Obst_Medio::getLimitesColisao() const {
    return sf::FloatRect(x, y, largura, altura);
}

}
