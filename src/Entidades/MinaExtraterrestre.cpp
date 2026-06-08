#include "Entidades/MinaExtraterrestre.h"
#include "Entidades/Jogador.h"
#include <cstddef>
#include <cmath>
#include <iostream>

namespace Entidades {

MinaExtraterrestre::MinaExtraterrestre(float x, float y, float largura, float altura, short int dano)
    : Obstaculo(), largura(largura), altura(altura),
      danoVidas(dano), destruido(false)
{
    this->x = x;
    this->y = y;
    danoso = true;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        if (!texturaMina.loadFromFile("assets/textures/mina.png")) {
            std::cerr << "Erro ao carregar a textura da mina!" << std::endl;
            static_cast<sf::RectangleShape*>(pFig)->setFillColor(sf::Color(200, 30, 30, 220));
        } else {
            pFig->setTexture(&texturaMina);
            pFig->setScale(sf::Vector2f(.75f, .75f));
        }
    }
}

MinaExtraterrestre::~MinaExtraterrestre() {
}

void MinaExtraterrestre::executar(float dt) {
    (void)dt;
}

void MinaExtraterrestre::salvar() {
}

void MinaExtraterrestre::obstaculizar(Jogador* p) {
    if (p == NULL || destruido) return;

    if (p->getHitbox().intersects(getHitbox())) {
        aplicarDano(p);
    }
}

void MinaExtraterrestre::aplicarDano(Jogador* p) {
    if (p == NULL || destruido) return;
    std::cout << "Danificar jogador" << std::endl;
    for (short int i = 0; i < danoVidas; ++i) {
        p->perderVida();
    }
    destruido = true;
}

sf::FloatRect MinaExtraterrestre::getHitbox() const {
    if (destruido) return sf::FloatRect(0.f, 0.f, 0.f, 0.f);
    return sf::FloatRect(x, y, largura, altura);
}

}
