#include "Jogo.h"
#include "Ente.h"

Jogo::Jogo() : GG(), lista_entidades(), pJogador(0) {
    Ente::setGG(&GG);
    pJogador = new Entidades::Jogador();
    lista_entidades.incluir(pJogador);
}

Jogo::~Jogo() {
    if (pJogador) {
        delete pJogador;
        pJogador = 0;
    }
}

void Jogo::executar() {
    while (GG.estaAberto()) {
        GG.processarEventos();
        GG.renderizar();
        lista_entidades.percorrer();
        GG.mostrar();
    }
}