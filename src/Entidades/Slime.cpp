#include "Entidades/Slime.h"
#include "Entidades/Jogador.h"
#include "Configuracao.h"
#include <cstdlib>
#include <iostream>

namespace Entidades {
namespace Personagens {

Slime::Slime(float x_ini, float y_ini)
    : Inimigo(), frameAtual(0), tempoAnimacao(0.f), larguraFrame(0), alturaFrame(0)
{
    x = x_ini;
    y = y_ini;

    float v = 40.f + std::rand() % 40;
    velocidadeX = (std::rand() % 2 == 0) ? v : -v;

    pFig = new sf::RectangleShape(sf::Vector2f(64.f, 64.f));
    if (pFig != NULL) {
        pFig->setOrigin(32.f, 48.f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (!textura.loadFromFile("assets/textures/slime.png")) {
            std::cerr << "Erro ao carregar textura do slime!" << std::endl;
            pFig->setFillColor(sf::Color(0, 200, 80));
        } else {
            pFig->setTexture(&textura);
            larguraFrame = textura.getSize().x / 8;
            alturaFrame  = textura.getSize().y / 4;
            pFig->setTextureRect(sf::IntRect(0, 0, larguraFrame, alturaFrame));
        }
    }
}

Slime::~Slime() {
}

void Slime::executar(float dt) {
    vy += Config::GRAVIDADE * dt;
    x  += velocidadeX * dt;
    y  += vy * dt;

    if (y > Config::ALTURA_LIMITE_QUEDA) {
        y  = Config::POSICAO_INICIAL_Y;
        vy = 0.f;
    }

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        tempoAnimacao += dt;
        if (tempoAnimacao >= 0.2f) {
            tempoAnimacao = 0.f;
            frameAtual = (frameAtual + 1) % 8;
        }

        if (velocidadeX < 0) {
            pFig->setTextureRect(sf::IntRect((frameAtual + 1) * larguraFrame, 0, -larguraFrame, alturaFrame));
        } else {
            pFig->setTextureRect(sf::IntRect(frameAtual * larguraFrame, 0, larguraFrame, alturaFrame));
        }
    }
}

void Slime::salvar() {
}

void Slime::mover() {
}

void Slime::danificar(Jogador* p) {
    if (p != NULL) {
        p->perderVida();
    }
}

sf::FloatRect Slime::getHitbox() const {
    return sf::FloatRect(x - 28.f, y - 28.f, 56.f, 56.f);
}

}
}
