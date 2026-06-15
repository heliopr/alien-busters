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

Fase_Lua::Fase_Lua(Entidades::Personagens::Jogador* pJogador, Entidades::Personagens::Jogador* pJogador2, const std::string& nome1, const std::string& nome2) : Fase(pJogador, pJogador2, nome1, nome2) {
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
    Entidades::Personagens::Alien* inimigo1 = new Entidades::Personagens::Alien(400.f, 300.f);
    lista_ents.incluir(inimigo1);
    GC.incluirInimigo(inimigo1);

    Entidades::Personagens::Alien* inimigo2 = new Entidades::Personagens::Alien(500.f, 300.f);
    lista_ents.incluir(inimigo2);
    GC.incluirInimigo(inimigo2);

    Entidades::Personagens::Alien* inimigo3 = new Entidades::Personagens::Alien(1200.f, 400.f);
    lista_ents.incluir(inimigo3);
    GC.incluirInimigo(inimigo3);

    Entidades::Personagens::Alien* inimigo4 = new Entidades::Personagens::Alien(1700.f, 350.f);
    lista_ents.incluir(inimigo4);
    GC.incluirInimigo(inimigo4);

    Entidades::Personagens::Alien* inimigo5 = new Entidades::Personagens::Alien(2200.f, 300.f);
    lista_ents.incluir(inimigo5);
    GC.incluirInimigo(inimigo5);
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
        GC.incluirObstaculo(p);
        lista_ents.incluir(p);
    }

    Entidades::Obstaculos::Chao* parede1 = new Entidades::Obstaculos::Chao(1020.f, 620.f, 120.f, 80.f, corLua);
    Entidades::Obstaculos::Chao* parede2 = new Entidades::Obstaculos::Chao(2600.f, 300.f, 400.f, 600.f, corLua);
    GC.incluirObstaculo(parede1);
    GC.incluirObstaculo(parede2);
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
    const int total  = sizeof(posicoes) / sizeof(posicoes[0]);
    const int minimo = 3;

    int indices[total];
    for (int i = 0; i < total; ++i) indices[i] = i;
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = indices[i]; indices[i] = indices[j]; indices[j] = tmp;
    }

    int quantidade = minimo + std::rand() % (total - minimo + 1);
    for (int i = 0; i < quantidade; ++i) {
        Entidades::Obstaculos::Gosma* om = new Entidades::Obstaculos::Gosma(posicoes[indices[i]][0], posicoes[indices[i]][1]);
        lista_ents.incluir(om);
    }
}

void Fase_Lua::criarFoguete() {
    Entidades::Foguete* foguete = new Entidades::Foguete(2380.f, 540.f);
    lista_ents.incluir(foguete);
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
    const int total  = sizeof(posicoes) / sizeof(posicoes[0]);
    const int minimo = 2;

    int indices[total];
    for (int i = 0; i < total; ++i) indices[i] = i;
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = indices[i]; indices[i] = indices[j]; indices[j] = tmp;
    }

    int quantidade = minimo + std::rand() % (total - minimo + 1);
    for (int i = 0; i < quantidade; ++i) {
        Entidades::Personagens::Slime* s = new Entidades::Personagens::Slime(posicoes[indices[i]][0], posicoes[indices[i]][1]);
        lista_ents.incluir(s);
        GC.incluirInimigo(s);
    }
}

}
