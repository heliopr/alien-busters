#include "Fases/Fase.h"
#include "Entidades/Chao.h"
#include "Entidades/Projetil.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Configuracao.h"

namespace Fases {

Fase::Fase(Entidades::Personagens::Jogador* pJogador, Entidades::Personagens::Jogador* pJogador2)
    : Ente(), lista_ents(), GC(), pJogador(pJogador), pJogador2(pJogador2) {
    GC.setJogador(pJogador);
    GC.setJogador2(pJogador2);
    GC.setListaEntidades(&lista_ents);

    if (pJogador) {
        pJogador->resetar();
    }
    if (pJogador2) {
        pJogador2->resetar();
    }
}

Fase::~Fase() {
    GC.limpar();
    lista_ents.limpar();
}

void Fase::processarJogador(Entidades::Personagens::Jogador* pJog, float dt) {
    if (pJog == 0 || pJog->estaMorto()) {
        return;
    }

    if (pJog->getY() > Config::ALTURA_LIMITE_QUEDA) {
        pJog->morrer();
        return;
    }

    if (pJog->getAtirou()) {
        float vx = pJog->getOlhandoDireita() ? 500.f : -500.f;
        float x_proj = pJog->getX() + (pJog->getOlhandoDireita() ? 22.f : -22.f);
        float y_proj = pJog->getY();
        Entidades::Projetil* p = new Entidades::Projetil(x_proj, y_proj - 50.f, vx, 0.f, pJog);
        lista_ents.incluir(p);
        GC.incluirProjetil(p);
    }

    pJog->executar(dt);
}

void Fase::atualizarCamera() {
    if (pGG == 0) {
        return;
    }

    float somaX = 0.f, somaY = 0.f;
    int n = 0;
    if (pJogador != 0 && !pJogador->estaMorto()) {
        somaX += pJogador->getX();
        somaY += pJogador->getY();
        ++n;
    }
    if (pJogador2 != 0 && !pJogador2->estaMorto()) {
        somaX += pJogador2->getX();
        somaY += pJogador2->getY();
        ++n;
    }

    if (n > 0) {
        pGG->atualizarCamera(sf::Vector2f(somaX / n, somaY / n));
    }
}

void Fase::executar(float dt) {
    processarJogador(pJogador, dt);
    processarJogador(pJogador2, dt);

    if (jogadorPerdeu()) {
        desenhar();
        return;
    }

    Entidades::Personagens::Jogador* j1 = (pJogador != 0 && !pJogador->estaMorto()) ? pJogador : 0;
    Entidades::Personagens::Jogador* j2 = (pJogador2 != 0 && !pJogador2->estaMorto()) ? pJogador2 : 0;
    lista_ents.percorrer(dt, j1, j2);
    GC.executar();

    atualizarCamera();
    desenhar();
}

void Fase::desenhar() {
    lista_ents.desenhar();

    if (!jogadorPerdeu()) {
        if (pJogador != 0 && !pJogador->estaMorto()) {
            pJogador->desenhar();
        }
        if (pJogador2 != 0 && !pJogador2->estaMorto()) {
            pJogador2->desenhar();
        }
    }

    if (pGG != 0) {
        if (pJogador != 0) {
            pGG->desenharHUD(pJogador->getPontos(), pJogador->getX(), pJogador->getY(),
                             pJogador->getNumVidas(), false, true);
        }
        if (pJogador2 != 0) {
            pGG->desenharHUD(pJogador2->getPontos(), pJogador2->getX(), pJogador2->getY(),
                             pJogador2->getNumVidas(), true, false);
        }
    }
}

void Fase::criarCenario() {
    criarCenario(sf::Color(145, 60, 25));
}

void Fase::criarCenario(const sf::Color& cor) {
    Entidades::Obstaculos::Chao* chao1 = new Entidades::Obstaculos::Chao(0.f, 700.f, 800.f, 100.f, cor);
    Entidades::Obstaculos::Chao* chao2 = new Entidades::Obstaculos::Chao(920.f, 700.f, 780.f, 100.f, cor);
    Entidades::Obstaculos::Chao* chao3 = new Entidades::Obstaculos::Chao(1850.f, 700.f, 800.f, 100.f, cor);

    GC.incluirObstaculo(chao1);
    GC.incluirObstaculo(chao2);
    GC.incluirObstaculo(chao3);

    lista_ents.incluir(chao1);
    lista_ents.incluir(chao2);
    lista_ents.incluir(chao3);
}

bool Fase::jogadorPerdeu() const {
    bool p1Morto = (pJogador == 0) || pJogador->estaMorto();
    bool p2Morto = (pJogador2 == 0) || pJogador2->estaMorto();
    return p1Morto && p2Morto;
}

void Fase::reiniciar() {
    GC.limpar();
    lista_ents.limpar();

    if (pJogador) {
        pJogador->resetar();
    }
    if (pJogador2) {
        pJogador2->resetar();
    }

    criarCenario();
    criarObstaculos();
    criarInimigos();
}

}
