#include "Fases/Fase_Marte.h"
#include "Entidades/Plataforma.h"
#include "Entidades/Alien.h"
#include "Entidades/Slime.h"
#include "Entidades/Gosma.h"
#include "Entidades/MinaExtraterrestre.h"
#include <cstdlib>
#include <ctime>

namespace Fases {

Fase_Marte::Fase_Marte() : Fase() {
    criarCenario();
    criarObstaculos();
    criarInimigos();

    lista_ents.incluir(pJogador);
}

Fase_Marte::~Fase_Marte() {
}

void Fase_Marte::criarInimigos() {
    criarAliens();
    criarSlimes();
}

void Fase_Marte::criarAliens() {
    Entidades::Personagens::Alien* inimigo1 = new Entidades::Personagens::Alien(350.f, 300.f);
    lista_ents.incluir(inimigo1);
    GC.incluirInimigo(inimigo1);

    Entidades::Personagens::Alien* inimigo2 = new Entidades::Personagens::Alien(600.f, 300.f);
    lista_ents.incluir(inimigo2);
    GC.incluirInimigo(inimigo2);

    Entidades::Personagens::Alien* inimigo3 = new Entidades::Personagens::Alien(900.f, 400.f);
    lista_ents.incluir(inimigo3);
    GC.incluirInimigo(inimigo3);

    Entidades::Personagens::Alien* inimigo4 = new Entidades::Personagens::Alien(1400.f, 350.f);
    lista_ents.incluir(inimigo4);
    GC.incluirInimigo(inimigo4);

    Entidades::Personagens::Alien* inimigo5 = new Entidades::Personagens::Alien(1800.f, 300.f);
    lista_ents.incluir(inimigo5);
    GC.incluirInimigo(inimigo5);

    Entidades::Personagens::Alien* inimigo6 = new Entidades::Personagens::Alien(2300.f, 350.f);
    lista_ents.incluir(inimigo6);
    GC.incluirInimigo(inimigo6);
}

void Fase_Marte::criarObstaculos() {
    struct plataforma { float x, y, largura, altura; };

    static const plataforma plataformas[] = {
        {250.f,  580.f, 150.f,  30.f},
        {420.f,  500.f, 150.f,  30.f},
        {580.f,  420.f, 150.f,  30.f},
        {150.f,  460.f, 100.f,  30.f},
        {320.f,  380.f, 100.f,  30.f},
        {480.f,  300.f, 100.f,  30.f},
        {720.f,  440.f, 180.f,  30.f},
        {980.f,  600.f, 120.f,  80.f},
        {1300.f, 360.f, 150.f,  30.f},
        {1550.f, 460.f, 180.f,  30.f},
        {1750.f, 560.f, 120.f,  30.f},
        {1900.f, 480.f, 120.f,  30.f},
        {2050.f, 380.f, 120.f,  30.f},
        {2200.f, 280.f, 120.f,  30.f},
        {2500.f, 300.f, 400.f, 600.f}
    };
    const int totalPlataformas = sizeof(plataformas) / sizeof(plataformas[0]);
    const int minimoPlataformas = 7;

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
        Entidades::Obstaculos::Plataforma* p = new Entidades::Obstaculos::Plataforma(d.x, d.y, d.largura, d.altura);
        GC.incluirObstaculo(p);
        lista_ents.incluir(p);
    }

    criarGosmas();

    Entidades::Obstaculos::MinaExtraterrestre* od = NULL;
    od = new Entidades::Obstaculos::MinaExtraterrestre(500.f,  660.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
    od = new Entidades::Obstaculos::MinaExtraterrestre(1100.f, 660.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
    od = new Entidades::Obstaculos::MinaExtraterrestre(1700.f, 660.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
    od = new Entidades::Obstaculos::MinaExtraterrestre(2300.f, 660.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
}

void Fase_Marte::criarSlimes() {
    static const float posicoes[][2] = {
        { 200.f, 300.f},
        { 500.f, 400.f},
        { 850.f, 300.f},
        {1200.f, 350.f},
        {1600.f, 300.f},
        {2000.f, 400.f},
        {2400.f, 300.f}
    };
    const int total   = sizeof(posicoes) / sizeof(posicoes[0]);
    const int minimo  = 3;

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

void Fase_Marte::criarGosmas() {
    Entidades::Obstaculos::Gosma* om = NULL;
    om = new Entidades::Obstaculos::Gosma(250.f,  640.f, 60.f, 60.f); lista_ents.incluir(om);
    om = new Entidades::Obstaculos::Gosma(800.f,  640.f, 60.f, 60.f); lista_ents.incluir(om);
    om = new Entidades::Obstaculos::Gosma(1500.f, 640.f, 60.f, 60.f); lista_ents.incluir(om);
    om = new Entidades::Obstaculos::Gosma(2100.f, 640.f, 60.f, 60.f); lista_ents.incluir(om);
}

}
