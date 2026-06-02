#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Plataforma.h"
#include "Entidades/Chao.h"

Jogo::Jogo() : GG(), faseAtual(new Fases::Fase_Primeira()), menu(this), noMenu(true), pJog1(0) {
    Ente::setGG(&GG);
}

Jogo::~Jogo() {
    if (faseAtual) {
        delete faseAtual;
        faseAtual = 0;
    }
}

void Jogo::executar() {
    sf::Clock clock;

    while (GG.estaAberto()) { 
        float dt = clock.restart().asSeconds();

        sf::Event evento;
        while (GG.coletarEventos(evento)) { 
            if (evento.type == sf::Event::Closed) {
                GG.fecharJanela();
            }

            // navegação do Menu
            if (noMenu && evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
                    menu.subirOpcao();
                }
                else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
                    menu.descerOpcao();
                }
                else if (evento.key.code == sf::Keyboard::Enter) {
                    if (menu.getOpcaoSelecionada() == 0) {
                        noMenu = false; // Começa o jogo!
                    } 
                    else if (menu.getOpcaoSelecionada() == 1) {
                        GG.fecharJanela(); // Fecha o jogo pelo Menu!
                    }
                }
            }
        }

        GG.renderizar();

        if (noMenu) {
            menu.desenhar();
        } 
        else {
            if (faseAtual) {
                faseAtual->executar(dt);
                if (faseAtual->getPrecisaResetar()) {
                    delete faseAtual;
                    faseAtual = new Fases::Fase_Primeira();
                }
            }
        }

        GG.mostrar();
    }
}