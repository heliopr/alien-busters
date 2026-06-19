#include "Entidades/MinaExtraterrestre.h"
#include "Entidades/Jogador.h"
#include <sstream>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <iostream>

namespace AlienBusters {
namespace Entidades {
namespace Obstaculos {

const float MinaExtraterrestre::INTERVALO_PISCAR = 0.15f;
const float MinaExtraterrestre::RAIO_EXPLOSAO = 100.f;

MinaExtraterrestre::MinaExtraterrestre(float x, float y)
    : Obstaculo(), largura(60.f), altura(60.f),
      tempoExplosao(0), tempoRestante(tempoExplosao),
      ativada(false), destruido(false)
{
    this->x = x;
    this->y = y;
    danoso = true;

    tempoExplosao = 0.5f + (std::rand() % 101) / 100.f;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        if (!texturaMina.loadFromFile("assets/textures/mina.png")) {
            std::cerr << "Erro ao carregar a textura da mina!" << std::endl;
            static_cast<sf::RectangleShape*>(pFig)->setFillColor(sf::Color(200, 30, 30, 220));
        } else {
            pFig->setTexture(&texturaMina);
            pFig->setOrigin(sf::Vector2f(-18.f, -10.f));
            pFig->setScale(sf::Vector2f(.65f, .65f));
        }
    }
}

MinaExtraterrestre::~MinaExtraterrestre() {
}

void MinaExtraterrestre::executar(float dt) {
    aplicarGravidade(dt);
    contrariarGravidade(dt);

    if (ativada && !destruido) {
        tempoRestante -= dt;

        if (pFig != NULL) {
            int piscar = static_cast<int>(tempoRestante / INTERVALO_PISCAR);
            if (piscar % 2 == 0) {
                pFig->setFillColor(sf::Color(255, 0, 0));
            } else {
                pFig->setFillColor(sf::Color::White);
            }
        }
    }
}

void MinaExtraterrestre::salvar() {
    buffer.str("");
    buffer.clear();
    if (destruido) {
        return;
    }
    buffer << "MINA ";
    salvarDataBuffer();
}

void MinaExtraterrestre::obstaculizar(Personagens::Jogador* p) {
    if (destruido) return;

    if (!ativada) {
        if (colidiuComJogador(p)) {
            ativada = true;
            tempoRestante = tempoExplosao;
        }
        return;
    }

    if (tempoRestante <= 0.f) {
        aplicarDano(p);
    }
}

void MinaExtraterrestre::aplicarDano(Personagens::Jogador* p) {
    if (jogadorDentroDoRaio(p)) {
        p->perderVida();
    }

    destruir();
}

bool MinaExtraterrestre::jogadorDentroDoRaio(Personagens::Jogador* p) const {
    if (p == NULL) return false;

    sf::FloatRect boxJogador = p->getHitbox();
    float centroMinaX = x + largura / 2.f;
    float centroMinaY = y + altura / 2.f;
    float centroJogadorX = boxJogador.left + boxJogador.width / 2.f;
    float centroJogadorY = boxJogador.top + boxJogador.height / 2.f;

    float dx = centroJogadorX - centroMinaX;
    float dy = centroJogadorY - centroMinaY;

    return std::sqrt(dx * dx + dy * dy) <= RAIO_EXPLOSAO;
}

sf::FloatRect MinaExtraterrestre::getHitbox() const {
    return sf::FloatRect(x, y, largura, altura);
}

}
}
}
