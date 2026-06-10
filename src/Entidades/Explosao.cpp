#include "Entidades/Explosao.h"
#include <iostream>
#include <cstddef>

namespace Entidades {

const int Explosao::NUM_FRAMES  = 12;
const float Explosao::TEMPO_FRAME = 0.06f;

Explosao::Explosao(float x, float y)
    : Entidade(), frameAtual(0), tempoAnimacao(0.f),
      larguraFrame(0), alturaFrame(0), terminada(false)
{
    this->x = x;
    this->y = y;

    if (!textura.loadFromFile("assets/textures/explosao.png")) {
        std::cerr << "Erro ao carregar explosao.png" << std::endl;
        terminada = true;
        return;
    }

    larguraFrame = static_cast<int>(textura.getSize().x) / NUM_FRAMES;
    alturaFrame  = static_cast<int>(textura.getSize().y);

    pFig = new sf::RectangleShape(sf::Vector2f(
        static_cast<float>(larguraFrame),
        static_cast<float>(alturaFrame)));

    if (pFig != NULL) {
        pFig->setTexture(&textura);
        pFig->setTextureRect(sf::IntRect(0, 0, larguraFrame, alturaFrame));
        pFig->setOrigin(larguraFrame / 2.f, alturaFrame / 2.f);
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

Explosao::~Explosao() {
}

void Explosao::executar(float dt) {
    sofrerGravidade(dt);
    contrariarGravidade(dt);

    if (terminada) return;

    tempoAnimacao += dt;
    if (tempoAnimacao >= TEMPO_FRAME) {
        tempoAnimacao = 0.f;
        frameAtual++;
        if (frameAtual >= NUM_FRAMES) {
            terminada = true;
            return;
        }
        if (pFig != NULL) {
            pFig->setTextureRect(sf::IntRect(
                frameAtual * larguraFrame, 0, larguraFrame, alturaFrame));
        }
    }
}

void Explosao::salvar() {
}

sf::FloatRect Explosao::getHitbox() const {
    return sf::FloatRect(x, y, 0.f, 0.f); // sem colisão
}

}
