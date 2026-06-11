#include "Entidades/MinaExtraterrestre.h"
#include "Entidades/Jogador.h"
#include <cstddef>
#include <cmath>
#include <iostream>

namespace Entidades {
namespace Obstaculos {

MinaExtraterrestre::MinaExtraterrestre(float x, float y, float tempoExplosao)
    : Obstaculo(), largura(60.f), altura(60.f),
      tempoExplosao(tempoExplosao), destruido(false)
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
    sofrerGravidade(dt);
    contrariarGravidade(dt);
}

void MinaExtraterrestre::salvar() {
}

void MinaExtraterrestre::obstaculizar(Personagens::Jogador* p) {
    if (!destruido && colidiuComJogador(p)) {
        aplicarDano(p);
    }
}

void MinaExtraterrestre::aplicarDano(Personagens::Jogador* p) {
    if (p == NULL || destruido) return;
    p->perderVida();
    destruido = true;
}

sf::FloatRect MinaExtraterrestre::getHitbox() const {
    if (destruido) return sf::FloatRect(0.f, 0.f, 0.f, 0.f);
    return sf::FloatRect(x, y, largura, altura);
}

}
}
