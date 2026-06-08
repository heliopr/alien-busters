#include "Entidades/Alien.h"
#include "Entidades/Jogador.h"
#include "Configuracao.h"
#include <iostream>

namespace Entidades {

Alien::Alien(float x_ini, float y_ini) : Inimigo(), raio(20.0f),
    linhaAtual(1), frameAtual(0), tempoAnimacao(0.f),
    olhandoEsquerda(true), olhandoDireita(false) 
{
    x = x_ini;
    y = y_ini; 
    
    pFig = new sf::RectangleShape(sf::Vector2f(72.0f, 72.0f));
    if (pFig != NULL) {
        pFig->setOrigin(36.0f, 48.0f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (!texturaInimigo.loadFromFile("assets/textures/alien.png")) {
            std::cerr << "Erro ao carregar a textura do inimigo facil!" << std::endl;
        } else {
            pFig->setTexture(&texturaInimigo);
            larguraFrame = texturaInimigo.getSize().x / 4;
            alturaFrame = texturaInimigo.getSize().y / 5;
            pFig->setTextureRect(sf::IntRect(0, alturaFrame, larguraFrame, alturaFrame));
        }
    }
}

Alien::~Alien() {
}

void Alien::executar(float dt) {
    vy += Config::GRAVIDADE * dt;
    
    x += velocidadeX * dt;
    y += vy * dt;

    if (y > Config::ALTURA_LIMITE_QUEDA) {
        y = Config::POSICAO_INICIAL_Y;
        vy = 0.f;
    }

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        tempoAnimacao += dt;
        if (tempoAnimacao >= 0.15f) {
            tempoAnimacao = 0.f;
            frameAtual = (frameAtual + 1) % 4;
        }

        if (velocidadeX < 0) {
            olhandoEsquerda = true;
            olhandoDireita = false;
        } else if (velocidadeX > 0) {
            olhandoEsquerda = false;
            olhandoDireita = true;
        }

        if (olhandoEsquerda) {
            linhaAtual = 2;
            pFig->setTextureRect(sf::IntRect((frameAtual + 1) * larguraFrame, linhaAtual * alturaFrame, -larguraFrame, alturaFrame));
        } else if (olhandoDireita) {
            linhaAtual = 2;
            pFig->setTextureRect(sf::IntRect(frameAtual * larguraFrame, linhaAtual * alturaFrame, larguraFrame, alturaFrame));
        }
    }
}

void Alien::salvar() {
}

void Alien::danificar(Jogador* p) {
    if (p != NULL) {
        p->perderVida();
    }
}

sf::FloatRect Alien::getLimitesColisao() const {
    return sf::FloatRect(x - 24.0f, y - 24.0f, 48.0f, 48.0f);
}

void Alien::mover() {

}

}
