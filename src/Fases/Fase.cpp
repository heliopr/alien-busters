#include "Fases/Fase.h"
#include "Entidades/Chao.h"

#include "Entidades/Projetil.h"

namespace Fases {

Fase::Fase() : Ente(), lista_ents(), GC(), pJogador(0) {
    pJogador = new Entidades::Jogador();
    GC.setJogador(pJogador);
    GC.setListaEntidades(&lista_ents);
}

Fase::~Fase() {
    if (pJogador) {
        delete pJogador;
        pJogador = 0;
    }
}

void Fase::executar(float dt) {
    if (pJogador && pJogador->getAtirou()) {
        float vx = pJogador->getOlhandoDireita() ? 500.f : -500.f;
        float x_proj = pJogador->getX() + (pJogador->getOlhandoDireita() ? 22.f : -22.f);
        float y_proj = pJogador->getY();
        Entidades::Projetil* p = new Entidades::Projetil(x_proj, y_proj - 50.f, vx, 0.f);
        lista_ents.incluir(p);
        GC.incluirProjetil(p);
    }

    lista_ents.percorrer(dt, pJogador);
    GC.executar();
}

void Fase::desenhar() {
}

void Fase::criarCenario() {
    Entidades::Chao* chao1 = new Entidades::Chao(0.f, 700.f, 800.f, 100.f);
    Entidades::Chao* chao2 = new Entidades::Chao(920.f, 700.f, 780.f, 100.f);
    Entidades::Chao* chao3 = new Entidades::Chao(1850.f, 700.f, 800.f, 100.f);

    GC.incluirObstaculo(chao1);
    GC.incluirObstaculo(chao2);
    GC.incluirObstaculo(chao3);

    lista_ents.incluir(chao1);
    lista_ents.incluir(chao2);
    lista_ents.incluir(chao3);

    /*Entidades::Projetil* proj = new Entidades::Projetil(100.f, 600.f, 200.f, 0.f);
    GC.incluirProjetil(proj);
    lista_ents.incluir(proj);*/
}

}
