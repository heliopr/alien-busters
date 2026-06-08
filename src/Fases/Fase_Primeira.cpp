#include "Fases/Fase_Primeira.h"
#include "Entidades/Plataforma.h"
#include "Entidades/Alien.h"
#include "Entidades/Gosma.h"
#include "Entidades/MinaTerrestre.h"

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
    Entidades::Alien* inimigo1 = new Entidades::Alien(400.f, 300.f);
    lista_ents.incluir(inimigo1);
    GC.incluirInimigo(inimigo1);

    Entidades::Alien* inimigo2 = new Entidades::Alien(700.f, 300.f);
    lista_ents.incluir(inimigo2);
    GC.incluirInimigo(inimigo2);

    Entidades::Alien* inimigo3 = new Entidades::Alien(1200.f, 400.f);
    lista_ents.incluir(inimigo3);
    GC.incluirInimigo(inimigo3);

    Entidades::Alien* inimigo4 = new Entidades::Alien(1700.f, 350.f);
    lista_ents.incluir(inimigo4);
    GC.incluirInimigo(inimigo4);

    Entidades::Alien* inimigo5 = new Entidades::Alien(2200.f, 300.f);
    lista_ents.incluir(inimigo5);
    GC.incluirInimigo(inimigo5);
}

void Fase_Primeira::criarObstaculos() {
    Entidades::Plataforma* p = 0;

    p = new Entidades::Plataforma(300.f, 600.f, 150.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(450.f, 540.f, 150.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(600.f, 460.f, 150.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);

    p = new Entidades::Plataforma(200.f, 480.f, 100.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(350.f, 400.f, 100.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(500.f, 320.f, 100.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    
    p = new Entidades::Plataforma(770.f, 420.f, 180.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);

    p = new Entidades::Plataforma(1020.f, 620.f, 120.f, 80.f);  GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(1180.f, 540.f, 120.f, 160.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(1340.f, 460.f, 120.f, 240.f); GC.incluirObstaculo(p); lista_ents.incluir(p);

    p = new Entidades::Plataforma(1520.f, 380.f, 150.f, 30.f);  GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(1680.f, 480.f, 180.f, 30.f);  GC.incluirObstaculo(p); lista_ents.incluir(p);

    p = new Entidades::Plataforma(1950.f, 600.f, 120.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(2100.f, 500.f, 120.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(2250.f, 400.f, 120.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);
    p = new Entidades::Plataforma(2400.f, 300.f, 120.f, 30.f); GC.incluirObstaculo(p); lista_ents.incluir(p);

    p = new Entidades::Plataforma(2600.f, 300.f, 400.f, 600.f); GC.incluirObstaculo(p); lista_ents.incluir(p);

    Entidades::Gosma* om = NULL;
    om = new Entidades::Gosma(640.f,  400.f, 60.f, 60.f); lista_ents.incluir(om);
    om = new Entidades::Gosma(1100.f, 500.f, 60.f, 60.f); lista_ents.incluir(om);
    om = new Entidades::Gosma(1750.f, 400.f, 60.f, 60.f); lista_ents.incluir(om);

    Entidades::MinaTerrestre* od = NULL;
    od = new Entidades::MinaTerrestre(850.f,  380.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
    od = new Entidades::MinaTerrestre(1450.f, 420.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
    od = new Entidades::MinaTerrestre(2150.f, 460.f, 60.f, 60.f, 1); GC.incluirObstaculoDificil(od); lista_ents.incluir(od);
}

}
