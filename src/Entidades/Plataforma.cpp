#include "Entidades/Plataforma.h"
#include "Configuracao.h"
#include <cstddef>
#include <cmath>

namespace Entidades {

Plataforma::Plataforma(float x, float y, float largura, float altura) 
    : Obstaculo(), altura(altura), largura(largura), pisada(false), caindo(false), tempoPisada(0.f), vy(0.f), posXOriginal(x) {
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
    if (!pisada && !caindo) {
        pisada = true;
    }
}

void Plataforma::executar(float dt) {
    if (pisada && !caindo) {
        tempoPisada += dt;
        float offset = std::sin(tempoPisada * 50.f) * 3.f; 
        x = posXOriginal + offset;
        
        if (tempoPisada >= 1.0f) {
            caindo = true;
            x = posXOriginal;
        }
    }

    if (caindo) {
        vy += Config::GRAVIDADE * dt;
        y += vy * dt;
    }

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Plataforma::obstaculizar(Jogador*) {
    // TODO
}

sf::FloatRect Plataforma::getLimitesColisao() const {
    return sf::FloatRect(x, y, largura, altura);
}

void Plataforma::salvar() {   
}

}