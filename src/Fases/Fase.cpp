#include "Fases/Fase.h"
#include "Entidades/Chao.h"
#include "Entidades/Inimigo.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Configuracao.h"
#include <cmath>
#include <vector>
#include <cstdlib>

namespace Fases {

Fase::Fase(Entidades::Personagens::Jogador* pJogador, Entidades::Personagens::Jogador* pJogador2,
           const std::string& nome1, const std::string& nome2)
    : Ente(), lista_ents(), pGC(Gerenciadores::Gerenciador_Colisoes::getInstancia()),
      pJogador(pJogador), pJogador2(pJogador2),
      nomeJogador(nome1), nomeJogador2(nome2) {
    pGC->setJogador(pJogador);
    pGC->setJogador2(pJogador2);
    pGC->setListaEntidades(&lista_ents);

    if (pJogador) {
        pJogador->resetar();
    }
    if (pJogador2) {
        pJogador2->resetar();
    }
}

Fase::~Fase() {
    pGC->limpar();
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

    pJog->atirar();
    pJog->executar(dt);
}

Entidades::Personagens::Jogador* Fase::jogadorMaisProximo(float x, float y) const {
    Entidades::Personagens::Jogador* maisProximo = 0;
    float menorDist = 0.f;

    Entidades::Personagens::Jogador* candidatos[2] = { pJogador, pJogador2 };
    for (int i = 0; i < 2; ++i) {
        Entidades::Personagens::Jogador* jog = candidatos[i];
        if (jog == 0 || jog->estaMorto()) {
            continue;
        }
        float dx = jog->getX() - x;
        float dy = jog->getY() - y;
        float dist = dx * dx + dy * dy;
        if (maisProximo == 0 || dist < menorDist) {
            menorDist = dist;
            maisProximo = jog;
        }
    }

    return maisProximo;
}

void Fase::processarInimigos(float dt) {
    const std::vector<Entidades::Personagens::Inimigo*>& inimigos = pGC->getInimigos();

    for (std::size_t i = 0; i < inimigos.size(); ++i) {
        Entidades::Personagens::Inimigo* ini = inimigos[i];
        if (ini == 0) {
            continue;
        }

        Entidades::Personagens::Jogador* alvo = jogadorMaisProximo(ini->getX(), ini->getY());
        if (alvo == 0) {
            continue;
        }

        ini->atirar(alvo, dt);
    }
}

std::vector<sf::Vector2f> Fase::sortearPosicoes(const float posicoes[][2], int total, int minimo, int maximo) const {
    int teto = (maximo < total) ? maximo : total;
    if (teto < minimo) {
        teto = minimo;
    }

    std::vector<int> indices(total);
    for (int i = 0; i < total; ++i) {
        indices[i] = i;
    }
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i+1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    int quantidade = minimo + std::rand() % (teto-minimo+1);

    std::vector<sf::Vector2f> escolhidas;
    for (int i = 0; i < quantidade; ++i) {
        escolhidas.push_back(sf::Vector2f(posicoes[indices[i]][0], posicoes[indices[i]][1]));
    }
    return escolhidas;
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
    processarInimigos(dt);

    if (jogadorPerdeu()) {
        desenhar();
        return;
    }

    lista_ents.percorrer(dt);
    pGC->executar();

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
            
            if (!nomeJogador.empty()) {
                sf::Text nomeText;
                nomeText.setFont(pGG->getFont());
                nomeText.setString(nomeJogador);
                nomeText.setCharacterSize(20);
                nomeText.setFillColor(sf::Color::White);
                nomeText.setPosition(sf::Vector2f(50.f, 115.f));
                pGG->desenharTextoTela(&nomeText);
            }
        }
        if (pJogador2 != 0) {
            pGG->desenharHUD(pJogador2->getPontos(), pJogador2->getX(), pJogador2->getY(),
                             pJogador2->getNumVidas(), true, false);
            
            if (!nomeJogador2.empty()) {
                sf::Text nomeText;
                nomeText.setFont(pGG->getFont());
                nomeText.setString(nomeJogador2);
                nomeText.setCharacterSize(20);
                nomeText.setFillColor(sf::Color(120, 170, 255));
                nomeText.setPosition(sf::Vector2f(1220.f, 115.f));
                pGG->desenharTextoTela(&nomeText);
            }
        }
    }
}

void Fase::criarCenario() {
    criarCenario(sf::Color(145, 60, 25));
}

void Fase::criarCenario(const sf::Color& cor) {
    Entidades::Chao* chao1 = new Entidades::Chao(0.f, 700.f, 800.f, 100.f, cor);
    Entidades::Chao* chao2 = new Entidades::Chao(920.f, 700.f, 780.f, 100.f, cor);
    Entidades::Chao* chao3 = new Entidades::Chao(1850.f, 700.f, 800.f, 100.f, cor);

    pGC->incluirChao(chao1);
    pGC->incluirChao(chao2);
    pGC->incluirChao(chao3);

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
    pGC->limpar();
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
