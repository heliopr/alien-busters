#include "Entidades/Plataforma.h"
#include "Entidades/Jogador.h"
#include "Configuracao.h"
#include <cstddef>
#include <cmath>

namespace Entidades {
namespace Obstaculos {

Plataforma::Plataforma(float x, float y, float largura, float altura)
    : Obstaculo(), altura(altura), largura(largura), pisada(false), caindo(false), tempoPisada(0.f), vy(0.f), posXOriginal(x), posYOriginal(y), tempoRespawn(0.f), surgindo(false), tempoSurgindo(0.f) {
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(sf::Color(145, 60, 25));
    }
}

Plataforma::~Plataforma() {
}

void Plataforma::jogadorPisou() {
    if (!pisada && !caindo && !surgindo) {
        pisada = true;
    }
}

void Plataforma::executar(float dt) {
    if (surgindo) {
        tempoSurgindo += dt;
        int alpha = (int)((tempoSurgindo / 1.0f) * 255);
        if (alpha > 255) {
            alpha = 255;
            surgindo = false;
            tempoSurgindo = 0.f;
        }
        if (pFig != NULL) {
            pFig->setFillColor(sf::Color(145, 60, 25, alpha));
        }
    }

    if (pisada && !caindo) {
        tempoPisada += dt;
        float offset = std::sin(tempoPisada * 50.f) * 3.f;
        x = posXOriginal + offset;

        if (tempoPisada >= 2.0f) {
            caindo = true;
            x = posXOriginal;
        }
    }

    if (caindo) {
        vy += Config::GRAVIDADE * dt;
        y += vy * dt;

        tempoRespawn += dt;
        if (tempoRespawn >= 5.0f) {
            caindo = false;
            pisada = false;
            tempoPisada = 0.f;
            tempoRespawn = 0.f;
            vy = 0.f;
            x = posXOriginal;
            y = posYOriginal;
            surgindo = true;
            if (pFig != NULL) {
                pFig->setFillColor(sf::Color(145, 60, 25, 0));
            }
        }
    }

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Plataforma::obstaculizar(Personagens::Jogador* p) {
    if (p == NULL || caindo) return;

    sf::FloatRect boxPlayer = p->getHitbox();
    sf::FloatRect boxPlat = getHitbox();
    sf::FloatRect interseccao;

    if (boxPlayer.intersects(boxPlat, interseccao)) {
        bool colisaoVertical = interseccao.width >= interseccao.height;
        bool jogadorPorCima = boxPlayer.top + boxPlayer.height / 2.f < boxPlat.top + boxPlat.height / 2.f;
        if (colisaoVertical && jogadorPorCima) {
            jogadorPisou();
        }
    }
}

sf::FloatRect Plataforma::getHitbox() const {
    return sf::FloatRect(x, y, largura, altura);
}

void Plataforma::salvar() {
}

}
}
