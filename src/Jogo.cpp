#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Plataforma.h"

Jogo::Jogo() : GG(), lista_entidades(), pJogador(0) {
    Ente::setGG(&GG);

    pJogador = new Entidades::Jogador();

    // CHAO
    lista_entidades.incluir(new Entidades::Plataforma(0.f, 700.f, 800.f, 100.f));
    lista_entidades.incluir(new Entidades::Plataforma(920.f, 700.f, 780.f, 100.f));
    lista_entidades.incluir(new Entidades::Plataforma(1850.f, 700.f, 800.f, 100.f));

    // SECAO 1
    lista_entidades.incluir(new Entidades::Plataforma(300.f, 600.f, 150.f, 30.f));
    lista_entidades.incluir(new Entidades::Plataforma(450.f, 540.f, 150.f, 30.f));
    lista_entidades.incluir(new Entidades::Plataforma(600.f, 460.f, 150.f, 30.f));

    lista_entidades.incluir(new Entidades::Plataforma(200.f, 480.f, 100.f, 30.f));
    lista_entidades.incluir(new Entidades::Plataforma(350.f, 400.f, 100.f, 30.f));
    lista_entidades.incluir(new Entidades::Plataforma(500.f, 320.f, 100.f, 30.f));
    
    lista_entidades.incluir(new Entidades::Plataforma(770.f, 420.f, 180.f, 30.f));

    // SECAO 2
    lista_entidades.incluir(new Entidades::Plataforma(1020.f, 620.f, 120.f, 80.f));
    lista_entidades.incluir(new Entidades::Plataforma(1180.f, 540.f, 120.f, 160.f));
    lista_entidades.incluir(new Entidades::Plataforma(1340.f, 460.f, 120.f, 240.f));

    lista_entidades.incluir(new Entidades::Plataforma(1520.f, 380.f, 150.f, 30.f));
    
    lista_entidades.incluir(new Entidades::Plataforma(1680.f, 480.f, 180.f, 30.f));

    // SECAO 3
    lista_entidades.incluir(new Entidades::Plataforma(1950.f, 600.f, 120.f, 30.f));
    lista_entidades.incluir(new Entidades::Plataforma(2100.f, 500.f, 120.f, 30.f));
    lista_entidades.incluir(new Entidades::Plataforma(2250.f, 400.f, 120.f, 30.f));
    lista_entidades.incluir(new Entidades::Plataforma(2400.f, 300.f, 120.f, 30.f));

    // FIM
    lista_entidades.incluir(new Entidades::Plataforma(2600.f, 300.f, 400.f, 600.f));

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

        lista_entidades.percorrer(dt, pJogador);
        
        GG.mostrar();
    }
}