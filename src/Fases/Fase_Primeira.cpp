#include "Fases/Fase_Primeira.h"
#include "Entidades/Plataforma.h"
#include "Entidades/Alien.h"
#include "Entidades/Gosma.h"
#include "Entidades/MinaExtraterrestre.h"
#include <cstdlib>
#include <ctime>

namespace Fases {

Fase_Primeira::Fase_Primeira() : Fase() {
    criarCenario();
    criarObstaculos();
    criarInimigos();

    lista_ents.incluir(pJogador);
}

Fase_Primeira::~Fase_Primeira() {
}

void Fase_Primeira::criarInimigos() {
    Entidades::Personagens::Alien* inimigo1 = new Entidades::Personagens::Alien(400.f, 300.f);
    lista_ents.incluir(inimigo1);
    GC.incluirInimigo(inimigo1);

    Entidades::Personagens::Alien* inimigo2 = new Entidades::Personagens::Alien(700.f, 300.f);
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

void Fase_Primeira::criarObstaculos() {
    struct plataforma { float x, y, largura, altura; };

    static const plataforma plataformas[] = {
        {300.f,  600.f, 150.f,  30.f},
        {450.f,  540.f, 150.f,  30.f},
        {600.f,  460.f, 150.f,  30.f},
        {200.f,  480.f, 100.f,  30.f},
        {350.f,  400.f, 100.f,  30.f},
        {500.f,  320.f, 100.f,  30.f},
        {770.f,  420.f, 180.f,  30.f},
        {1020.f, 620.f, 120.f,  80.f},
        //{1180.f, 540.f, 120.f, 160.f},
        //{1340.f, 460.f, 120.f, 240.f},
        {1520.f, 380.f, 150.f,  30.f},
        {1680.f, 480.f, 180.f,  30.f},
        {1950.f, 600.f, 120.f,  30.f},
        {2100.f, 500.f, 120.f,  30.f},
        {2250.f, 400.f, 120.f,  30.f},
        {2400.f, 300.f, 120.f,  30.f},
        {2600.f, 300.f, 400.f, 600.f}
    };
    const int totalPlataformas = sizeof(plataformas) / sizeof(plataformas[0]);
    const int minimoPlataformas = 6;

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

    Entidades::Obstaculos::Gosma* om = NULL;
    om = new Entidades::Obstaculos::Gosma(300.f,  640.f, 60.f, 60.f); lista_ents.incluir(om);
    om = new Entidades::Obstaculos::Gosma(940.f, 640.f, 60.f, 60.f); lista_ents.incluir(om);
    om = new Entidades::Obstaculos::Gosma(1980.f, 640.f, 60.f, 60.f); lista_ents.incluir(om);

    Entidades::Obstaculos::MinaExtraterrestre* od = NULL;
    od = new Entidades::Obstaculos::MinaExtraterrestre(600.f,  660.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
    od = new Entidades::Obstaculos::MinaExtraterrestre(1450.f, 660.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
    od = new Entidades::Obstaculos::MinaExtraterrestre(2250.f, 660.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
}

}
