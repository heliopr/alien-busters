#include "Fases/Fase.h"
#include "Entidades/Chao.h"

namespace Fases {

Fase::Fase() : Ente(), lista_ents(), GC(), pJogador(0) {
    pJogador = new Entidades::Jogador();
    GC.setJogador(pJogador);
}

Fase::~Fase() {
    if (pJogador) {
        delete pJogador;
        pJogador = 0;
    }
}

void Fase::executar(float dt) {
    lista_ents.percorrer(dt, pJogador);
    GC.executar();
}

void Fase::desenhar() {
}

void Fase::criarCenario() {
    Entidades::Chao* chao1 = new Entidades::Chao(0.f, 700.f, 800.f, 100.f);
    Entidades::Chao* chao2 = new Entidades::Chao(920.f, 700.f, 780.f, 100.f);
    Entidades::Chao* chao3 = new Entidades::Chao(1850.f, 700.f, 800.f, 100.f);

    GC.incluirChao(chao1);
    GC.incluirChao(chao2);
    GC.incluirChao(chao3);

    lista_ents.incluir(chao1);
    lista_ents.incluir(chao2);
    lista_ents.incluir(chao3);
}

}
