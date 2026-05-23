#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Plataforma.h"

Jogo::Jogo() : GG(), lista_entidades(), pJogador(0) {
    Ente::setGG(&GG);

    pJogador = new Entidades::Jogador();
    lista_entidades.incluir(pJogador);

    Entidades::Plataforma *plataforma = new Entidades::Plataforma();
    lista_entidades.incluir(plataforma);
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