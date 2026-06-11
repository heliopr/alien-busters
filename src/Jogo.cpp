#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Plataforma.h"

Jogo::Jogo() : GG(), faseAtual(0), pJog1(0), menu(this), telaMorte(), estado(ESTADO_MENU) {
    Ente::setGG(&GG);
    pJog1 = new Entidades::Personagens::Jogador();
}

Jogo::~Jogo() {
    if (faseAtual) {
        delete faseAtual;
        faseAtual = 0;
    }

    delete pJog1;
    pJog1 = 0;
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

            if (evento.type == sf::Event::KeyPressed) {
                // navegação do Menu
                if (estado == ESTADO_MENU) {
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
                                faseAtual = new Fases::Fase_Lua(pJog1);
                                estado = ESTADO_JOGANDO;
                            } else if (fase == 1) {
                                delete faseAtual;
                                faseAtual = new Fases::Fase_Marte(pJog1);
                                estado = ESTADO_JOGANDO;
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
                else if (estado == ESTADO_TELA_MORTE) {
                    if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
                        telaMorte.subirOpcao();
                    }
                    else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
                        telaMorte.descerOpcao();
                    }
                    else if (evento.key.code == sf::Keyboard::Enter) {
                        if (telaMorte.getOpcaoSelecionada() == 0) {
                            if (faseAtual) {
                                faseAtual->reiniciar();
                            }
                            telaMorte.resetar();
                            estado = ESTADO_JOGANDO;
                        } else {
                            delete faseAtual;
                            faseAtual = 0;
                            menu.sairSubmenu();
                            telaMorte.resetar();
                            estado = ESTADO_MENU;
                        }
                    }
                }
            }
        }

        GG.renderizar();

        if (estado == ESTADO_MENU) {
            menu.desenhar();
        }
        else if (estado == ESTADO_JOGANDO) {
            if (faseAtual) {
                faseAtual->executar(dt);
                if (faseAtual->jogadorPerdeu()) {
                    estado = ESTADO_TELA_MORTE;
                }
            }
        }
        else {
            if (faseAtual) {
                faseAtual->desenhar();
            }
            telaMorte.desenhar();
        }

        GG.mostrar();
    }
}