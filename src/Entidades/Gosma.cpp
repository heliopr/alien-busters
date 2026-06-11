#include "Entidades/Gosma.h"
#include "Entidades/Jogador.h"
#include <cstddef>
#include <iostream>

namespace Entidades {
namespace Obstaculos {

Gosma::Gosma(float x, float y)
    : Obstaculo(), largura(60.f), altura(60.f) {
    this->x = x;
    this->y = y;
    danoso = false;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        if (!textura.loadFromFile("assets/textures/gosma.png")) {
            std::cerr << "Erro ao carregar textura da gosma!" << std::endl;
            pFig->setFillColor(sf::Color(50, 50, 200, 160));
        } else {
            pFig->setTexture(&textura);
            pFig->setOrigin(sf::Vector2f(0.0f, -30.0f));
        }
    }
}

Gosma::~Gosma() {
}

void Gosma::executar(float dt) {
    sofrerGravidade(dt);
    contrariarGravidade(dt);
}

void Gosma::salvar() {
}

void Gosma::obstaculizar(Personagens::Jogador* p) {
    if (colidiuComJogador(p) && p->getNoChao()) {
        p->ficarLento(1.0f);
    }
}

sf::FloatRect Gosma::getHitbox() const {
    return sf::FloatRect(x, y, largura, altura);
}

}
}
