#include "Entidades/Jogador.h"
#include "Entidades/Inimigo.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Configuracao.h"
#include <cmath>
#include <cstddef>
#include <iostream>

namespace Entidades {
namespace Personagens {

Jogador::Jogador(float xInicial, float yInicial, bool eJogadorUm, const std::string& texturaSprite) : Personagem(), pontos(0),
    eJogadorUm(eJogadorUm), xInicial(xInicial), yInicial(yInicial),
    ultimoDx(0.f),
    olhandoDireita(true), puloPressionado(false), tiroPressionado(false),
    tempoRecargaTiro(0.f),
    tempoLento(0.f), tempoInvulneravel(0.f), tempoFlashDano(0.f)
{
    x = xInicial;
    y = yInicial;
    num_vidas = 3;

    pFig = new sf::RectangleShape(sf::Vector2f(60.f, 100.f));
    if (pFig != NULL) {
        pFig->setOrigin(30.f, 100.f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (animacao.carregar(texturaSprite, 8, 3, "Erro ao carregar a textura do jogador!")) {
            pFig->setTexture(animacao.getTextura());
            animacao.aplicar(pFig, 1, false);
        }
    }

    if (bufferDano.loadFromFile("assets/sounds/hit.mp3")) {
        somDano.setBuffer(bufferDano);
    } else {
        std::cerr << "Erro ao carregar som assets/sounds/hit.mp3!" << std::endl;
    }

    if (bufferMorte.loadFromFile("assets/sounds/oof.mp3")) {
        somMorte.setBuffer(bufferMorte);
    } else {
        std::cerr << "Erro ao carregar som assets/sounds/oof.mp3!" << std::endl;
    }
}

Jogador::~Jogador() {
}

void Jogador::resetar() {
    setX(xInicial);
    setY(yInicial);
    setVy(0.f);
    setNoChao(false);

    ultimoDx = 0.f;
    num_vidas = 3;
    pontos = 0;

    olhandoDireita = true;
    puloPressionado = false;
    tiroPressionado = false;
    tempoRecargaTiro = 0.f;

    tempoLento = 0.f;
    tempoInvulneravel = 0.f;
    tempoFlashDano = 0.f;
}

void Jogador::executar(float dt) {
    if (tempoLento > 0.f) {
        tempoLento -= dt;
        if (tempoLento < 0.f) {
            tempoLento = 0.f;
        }
    }

    if (tempoInvulneravel > 0.f) {
        tempoInvulneravel -= dt;
        if (tempoInvulneravel < 0.f) {
            tempoInvulneravel = 0.f;
        }
    }

    if (tempoFlashDano > 0.f) {
        tempoFlashDano -= dt;
        if (tempoFlashDano < 0.f) {
            tempoFlashDano = 0.f;
        }
    }

    if (tempoRecargaTiro > 0.f) {
        tempoRecargaTiro -= dt;
        if (tempoRecargaTiro < 0.f) {
            tempoRecargaTiro = 0.f;
        }
    }

    mover(dt);

    atualizarSprite(dt, ultimoDx);
}

float Jogador::processarMovimento(float dt) {
    float velocidadeX = (tempoLento > 0.f) ? Config::VELOCIDADE_X * 0.4f : Config::VELOCIDADE_X;
    float dx = 0;

    if (sf::Keyboard::isKeyPressed(eJogadorUm ? sf::Keyboard::A : sf::Keyboard::Left)) {
        dx -= 1;
        olhandoDireita = false;
    }
    if (sf::Keyboard::isKeyPressed(eJogadorUm ? sf::Keyboard::D : sf::Keyboard::Right)) {
        dx += 1;
        olhandoDireita = true;
    }

    bool puloAtual = sf::Keyboard::isKeyPressed(eJogadorUm ? sf::Keyboard::W : sf::Keyboard::Up);
    if (puloAtual && !puloPressionado && noChao) {
        vy = Config::FORCA_PULO;
    }
    puloPressionado = puloAtual;

    x += dx * velocidadeX * dt;

    return dx;
}

void Jogador::atualizarSprite(float dt, float dx) {
    if (pFig == NULL) {
        return;
    }

    pFig->setPosition(sf::Vector2f(x, y));
    pFig->setSize(sf::Vector2f(60.f, 100.f));
    pFig->setOrigin(30.f, 100.f);

    bool noAr = !noChao || (vy < 0.f);
    if (noAr) {
        animacao.setFrameAtual(2);
    } else if (dx != 0) {
        animacao.atualizar(dt, 0.08f, 8);
    } else {
        animacao.setFrameAtual(0);
    }

    animacao.aplicar(pFig, 1, !olhandoDireita);

    if (tempoFlashDano > 0.f) {
        pFig->setTexture(animacao.getTexturaBranca());
        pFig->setFillColor(sf::Color::White);
    } else {
        pFig->setTexture(animacao.getTextura());
    }
}

void Jogador::salvar() {
}

sf::FloatRect Jogador::getHitbox() const {
    return sf::FloatRect(x - 20.f, y - 75.f, 40.f, 50.f);
}

void Jogador::mover(float dt) {
    ultimoDx = processarMovimento(dt);
    aplicarGravidade(dt);
}

bool Jogador::getAtirou() {
    bool atirouAtual = sf::Keyboard::isKeyPressed(eJogadorUm ? sf::Keyboard::R : sf::Keyboard::Enter);
    bool disparou = atirouAtual && !tiroPressionado && tempoRecargaTiro <= 0.f;
    tiroPressionado = atirouAtual;

    if (disparou) {
        tempoRecargaTiro = Config::TEMPO_RECARGA_TIRO;
    }

    return disparou;
}

void Jogador::colidir(Inimigo* pIn) {
    if (pIn != NULL) {
        pIn->danificar(this);
    }
}

void Jogador::ficarLento(float duracao) {
    tempoLento = duracao;
}

void Jogador::ativarInvulnerabilidade() {
    tempoInvulneravel = Config::TEMPO_INVULNERAVEL;
}

void Jogador::perderVida() {
    num_vidas--;
    tempoFlashDano = Config::DURACAO_FLASH_DANO;

    if (num_vidas <= 0) {
        somMorte.play();
    } else {
        somDano.play();
    }
}

void Jogador::morrer() {
    num_vidas = 0;
    somMorte.play();
}

}
}