#include "Entidades/Jogador.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Configuracao.h"
#include <cmath>
#include <iostream>
#include <cstddef>

namespace Entidades {

Jogador::Jogador() : Personagem(), 
    linhaAtual(1), frameAtual(0), tempoAnimacao(0.f), 
    agachado(false), 
    olhandoEsquerda(false), olhandoDireita(true), puloPressionado(false), tiroPressionado(false)
{
    x = Config::POSICAO_INICIAL_X;
    y = Config::POSICAO_INICIAL_Y; 

    pFig = new sf::RectangleShape(sf::Vector2f(60.f, 100.f));
    if (pFig != NULL) {
        pFig->setOrigin(30.f, 100.f); 
        pFig->setPosition(sf::Vector2f(x, y));

        if (!texturaJogador.loadFromFile("assets/textures/player.png")) {
            std::cerr << "Erro ao carregar a textura do jogador!" << std::endl;
        } else {
            pFig->setTexture(&texturaJogador);
            larguraFrame = texturaJogador.getSize().x / 8;
            alturaFrame = texturaJogador.getSize().y / 3;
            pFig->setTextureRect(sf::IntRect(0, alturaFrame, larguraFrame, alturaFrame));
        }
    }
}

Jogador::~Jogador() {
}

void Jogador::executar(float dt) {
    float velocidadeX = Config::VELOCIDADE_X;
    float forcaPulo = Config::FORCA_PULO;  
    float gravidade = Config::GRAVIDADE;   
    float dx = 0;

    bool podPular = noChao;
    noChao = false;

    vy += gravidade * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { 
        dx -= 1; 
        olhandoEsquerda = true; 
        olhandoDireita = false; 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
        dx += 1; 
        olhandoDireita = true; 
        olhandoEsquerda = false; 
    }

    bool puloAtual = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    if (puloAtual && !puloPressionado && podPular) {
        vy = forcaPulo;
    }
    puloPressionado = puloAtual;

    x += dx * velocidadeX * dt;
    y += vy * dt;

    if (y > Config::ALTURA_LIMITE_QUEDA) {
        x = Config::POSICAO_INICIAL_X;
        y = Config::POSICAO_INICIAL_Y;
        vy = 0.f;
    }

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setSize(sf::Vector2f(60.f, 100.f));
        pFig->setOrigin(30.f, 100.f);
        
        bool noAr = !podPular || (vy < 0.f);
        if (noAr) {
            linhaAtual = 1; 
            frameAtual = 2; 
        } else if (dx != 0) {
            linhaAtual = 1; 
            tempoAnimacao += dt;
            if (tempoAnimacao >= 0.08f) {
                tempoAnimacao = 0.f;
                frameAtual = (frameAtual + 1) % 8;
            }
        } else {
            linhaAtual = 1;
            frameAtual = 0;
        }

        if (olhandoEsquerda) {
            pFig->setTextureRect(sf::IntRect((frameAtual + 1) * larguraFrame, linhaAtual * alturaFrame, -larguraFrame, alturaFrame));
        } else if (olhandoDireita) {
            pFig->setTextureRect(sf::IntRect(frameAtual * larguraFrame, linhaAtual * alturaFrame, larguraFrame, alturaFrame));
        }
    }

    if (pGG != NULL) {
        pGG->atualizarCamera(sf::Vector2f(x, y));
    }
}

void Jogador::salvar() {
}

sf::FloatRect Jogador::getLimitesColisao() const {
    return sf::FloatRect(x - 20.f, y - 75.f, 40.f, 50.f);
}

void Jogador::mover() {
}

bool Jogador::getAtirou() {
    bool atirouAtual = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    bool disparou = atirouAtual && !tiroPressionado;
    tiroPressionado = atirouAtual;
    return disparou;
}

void Jogador::colidir(Inimigo* pIn) {
    if (pIn) {
        num_vidas--;
    }
}

}