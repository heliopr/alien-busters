#include "Fases/Fase_Lua.h"
#include "Entidades/Plataforma.h"
#include "Entidades/Chao.h"
#include "Entidades/Alien.h"
#include "Entidades/Slime.h"
#include "Entidades/Gosma.h"
#include "Entidades/Foguete.h"
#include <cstdlib>
#include <ctime>

namespace Fases {

Fase_Lua::Fase_Lua(Entidades::Personagens::Jogador* pJogador, Entidades::Personagens::Jogador* pJogador2, const std::string& nome1, const std::string& nome2)
    : Fase(pJogador, pJogador2, nome1, nome2),
      maxAliens(5), maxSlimes(4), maxGosmas(6) {
    criarCenario();
    criarObstaculos();
    criarInimigos();
    criarFoguete();
}

Fase_Lua::~Fase_Lua() {
}

void Fase_Lua::criarCenario() {
    static const sf::Color corLua(140, 140, 160);
    Fase::criarCenario(corLua);
}

void Fase_Lua::criarInimigos() {
    criarSlimes();
    criarAliens();
}

void Fase_Lua::criarAliens() {
    static const float posicoes[][2] = {
        { 400.f, 300.f},
        { 500.f, 300.f},
        {1200.f, 400.f},
        {1700.f, 350.f},
        {2200.f, 300.f}
    };
    const int total = sizeof(posicoes) / sizeof(posicoes[0]);

    int quantidade = (maxAliens < total) ? maxAliens : total;
    for (int i = 0; i < quantidade; ++i) {
        Entidades::Personagens::Alien* inimigo = new Entidades::Personagens::Alien(posicoes[i][0], posicoes[i][1]);
        lista_ents.incluir(inimigo);
        pGC->incluirInimigo(inimigo);
    }
}

void Fase_Lua::criarObstaculos() {
    static const sf::Color corLua(140, 140, 160);

    struct plataforma { float x, y; };

    static const plataforma plataformas[] = {
        {300.f,  600.f},
        {450.f,  540.f},
        {600.f,  460.f},
        {200.f,  480.f},
        {350.f,  400.f},
        {500.f,  320.f},
        {770.f,  420.f},
        {1520.f, 380.f},
        {1680.f, 480.f},
        {1950.f, 600.f},
        {2100.f, 500.f},
        {2250.f, 400.f},
        {2400.f, 300.f}
    };
    const int totalPlataformas = sizeof(plataformas) / sizeof(plataformas[0]);
    const int minimoPlataformas = 3;

    static bool sementeInicializada = false;
    if (!sementeInicializada) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        sementeInicializada = true;
    }

    int indices[totalPlataformas];
    for (int i = 0; i < totalPlataformas; ++i) {
        indices[i] = i;
    }
    for (int i = totalPlataformas - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    int quantidade = minimoPlataformas + (std::rand() % (totalPlataformas - minimoPlataformas + 1));

    for (int i = 0; i < quantidade; ++i) {
        const plataforma& d = plataformas[indices[i]];
        Entidades::Obstaculos::Plataforma* p = new Entidades::Obstaculos::Plataforma(d.x, d.y, corLua);
        pGC->incluirObstaculo(p);
        lista_ents.incluir(p);
    }

    Entidades::Chao* parede1 = new Entidades::Chao(1020.f, 620.f, 120.f, 80.f, corLua);
    Entidades::Chao* parede2 = new Entidades::Chao(2600.f, 300.f, 400.f, 600.f, corLua);
    pGC->incluirChao(parede1);
    pGC->incluirChao(parede2);
    lista_ents.incluir(parede1);
    lista_ents.incluir(parede2);

    criarGosmas();
}

void Fase_Lua::criarGosmas() {
    static const float posicoes[][2] = {
        { 150.f, 640.f},
        { 300.f, 640.f},
        { 600.f, 640.f},
        { 940.f, 640.f},
        {1300.f, 640.f},
        {1550.f, 640.f},
        {1980.f, 640.f},
        {2400.f, 640.f}
    };
    const int total = sizeof(posicoes) / sizeof(posicoes[0]);

    std::vector<sf::Vector2f> p = sortearPosicoes(posicoes, total, 3, maxGosmas);
    for (size_t i = 0; i < p.size(); ++i) {
        Entidades::Obstaculos::Gosma* om = new Entidades::Obstaculos::Gosma(p[i].x, p[i].y);
        pGC->incluirObstaculo(om);
        lista_ents.incluir(om);
    }
}

void Fase_Lua::criarFoguete() {
    pFoguete = new Entidades::Foguete(2380.f, 540.f);
    lista_ents.incluir(pFoguete);
}

void Fase_Lua::criarSlimes() {
    static const float posicoes[][2] = {
        { 350.f, 300.f},
        { 700.f, 400.f},
        {1100.f, 350.f},
        {1500.f, 300.f},
        {1900.f, 400.f},
        {2350.f, 300.f}
    };
    const int total = sizeof(posicoes) / sizeof(posicoes[0]);

    std::vector<sf::Vector2f> p = sortearPosicoes(posicoes, total, 2, maxSlimes);
    for (size_t i = 0; i < p.size(); ++i) {
        Entidades::Personagens::Slime* s = new Entidades::Personagens::Slime(p[i].x, p[i].y);
        lista_ents.incluir(s);
        pGC->incluirInimigo(s);
    }
}

}
