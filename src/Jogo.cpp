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
    sf::Clock clock;

    while (GG.estaAberto()) {
        float dt = clock.restart().asSeconds();

        GG.processarEventos();

        GG.renderizar();

        lista_entidades.percorrer(dt);
        
        GG.mostrar();
    }
}