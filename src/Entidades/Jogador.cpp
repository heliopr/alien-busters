#include "Entidades/Jogador.h"
#include "Entidades/Inimigo.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Configuracao.h"
#include <cmath>
#include <cstddef>

namespace Entidades {
namespace Personagens {

Jogador::Jogador() : Personagem(), pontos(0),
    olhandoEsquerda(false), olhandoDireita(true), puloPressionado(false), tiroPressionado(false),
    lento(false), tempoLento(0.f),
    invulneravel(false), tempoInvulneravel(0.f), tempoFlashDano(0.f)
{
    x = Config::POSICAO_INICIAL_X;
    y = Config::POSICAO_INICIAL_Y;
    num_vidas = 3;

    pFig = new sf::RectangleShape(sf::Vector2f(60.f, 100.f));
    if (pFig != NULL) {
        pFig->setOrigin(30.f, 100.f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (animacao.carregar("assets/textures/player.png", 8, 3, "Erro ao carregar a textura do jogador!")) {
            pFig->setTexture(animacao.getTextura());
            animacao.aplicar(pFig, 1, false);
        }
    }
}

Jogador::~Jogador() {
}

void Jogador::executar(float dt) {
    float velocidadeX = Config::VELOCIDADE_X;

    if (lento) {
        tempoLento -= dt;
        if (tempoLento <= 0.f) {
            lento = false;
            tempoLento = 0.f;
        } else {
            velocidadeX *= 0.4f;
        }
    }

    if (invulneravel) {
        tempoInvulneravel -= dt;
        if (tempoInvulneravel <= 0.f) {
            invulneravel = false;
            tempoInvulneravel = 0.f;
        }
    }

    if (tempoFlashDano > 0.f) {
        tempoFlashDano -= dt;
        if (tempoFlashDano < 0.f) {
            tempoFlashDano = 0.f;
        }
    }
    float forcaPulo = Config::FORCA_PULO;
    float dx = 0;

    bool podPular = noChao;

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
    sofrerGravidade(dt);


    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setSize(sf::Vector2f(60.f, 100.f));
        pFig->setOrigin(30.f, 100.f);

        bool noAr = !podPular || (vy < 0.f);
        if (noAr) {
            animacao.setFrameAtual(2);
        } else if (dx != 0) {
            animacao.atualizar(dt, 0.08f, 8);
        } else {
            animacao.setFrameAtual(0);
        }

        animacao.aplicar(pFig, 1, olhandoEsquerda);

        if (tempoFlashDano > 0.f) {
            pFig->setTexture(animacao.getTexturaBranca());
        } else {
            pFig->setTexture(animacao.getTextura());
        }
    }

    if (pGG != NULL) {
        pGG->atualizarCamera(sf::Vector2f(x, y));
    }
}

void Jogador::salvar() {
}

sf::FloatRect Jogador::getHitbox() const {
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
    if (pIn != NULL) {
        pIn->danificar(this);
    }
}

void Jogador::ficarLento(float duracao) {
    lento = true;
    tempoLento = duracao;
}

void Jogador::ativarInvulnerabilidade() {
    invulneravel = true;
    tempoInvulneravel = Config::TEMPO_INVULNERAVEL;
}

void Jogador::perderVida() {
    num_vidas--;
    tempoFlashDano = Config::DURACAO_FLASH_DANO;
}

void Jogador::morrer() {
    num_vidas = 0;
}

}
}