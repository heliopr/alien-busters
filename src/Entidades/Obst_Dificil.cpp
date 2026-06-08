#include "Entidades/Obst_Dificil.h"
#include "Entidades/Jogador.h"
#include <cstddef>
#include <cmath>
#include <iostream>

namespace Entidades {

Obst_Dificil::Obst_Dificil(float x, float y, float largura, float altura, short int dano)
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

Obst_Dificil::~Obst_Dificil() {
}

void Obst_Dificil::executar(float dt) {
    (void)dt;
}

void Obst_Dificil::salvar() {
}

void Obst_Dificil::obstaculizar(Jogador* p) {
    if (p == NULL || destruido) return;

    if (p->getLimitesColisao().intersects(getLimitesColisao())) {
        aplicarDano(p);
    }
}

void Obst_Dificil::aplicarDano(Jogador* p) {
    if (p == NULL || destruido) return;
    std::cout << "Danificar jogador" << std::endl;
    for (short int i = 0; i < danoVidas; ++i) {
        p->perderVida();
    }
    destruido = true;
}

sf::FloatRect Obst_Dificil::getLimitesColisao() const {
    if (destruido) return sf::FloatRect(0.f, 0.f, 0.f, 0.f);
    return sf::FloatRect(x, y, largura, altura);
}

}
