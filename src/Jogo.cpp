#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Plataforma.h"

Jogo::Jogo() : GG(), faseAtual(0), pJog1(0), menu(this), noMenu(true) {
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
                    if (menu.getEmSubmenu()) {
                        int fase = menu.getOpcaoFaseSelecionada();
                        if (fase == 0) {
                            delete faseAtual;
                            faseAtual = new Fases::Fase_Lua();
                            noMenu = false;
                        } else if (fase == 1) {
                            delete faseAtual;
                            faseAtual = new Fases::Fase_Marte();
                            noMenu = false;
                        } else if (fase == 2) {
                            menu.sairSubmenu();
                        }
                    } else {
                        if (menu.getOpcaoSelecionada() == 0) {
                            menu.entrarSubmenu();
                        } else if (menu.getOpcaoSelecionada() == 1) {
                            GG.fecharJanela();
                        }
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
            }
        }

        GG.mostrar();
    }
}