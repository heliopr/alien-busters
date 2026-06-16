#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Plataforma.h"
#include "Configuracao.h"

Jogo::Jogo() : GG(), pGerenciadorPontuacoes(0), faseAtual(0), pJog1(0), pJog2(0), 
               menu(this), telaMorte(), estado(ESTADO_MENU), nomeJogadorAtual(""), 
               nomeJogador2Atual(""), faseSelecionada(-1) {
    Ente::setGG(&GG);

    Entidades::Personagens::ControlesJogador controles1(
        sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::R);
    pJog1 = new Entidades::Personagens::Jogador(
        Config::POSICAO_INICIAL_X, Config::POSICAO_INICIAL_Y, controles1);

    Entidades::Personagens::ControlesJogador controles2(
        sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Enter);
    pJog2 = new Entidades::Personagens::Jogador(
        Config::POSICAO_INICIAL_X + 70.f, Config::POSICAO_INICIAL_Y, controles2, "assets/textures/player2.png");

    pGerenciadorPontuacoes = new Gerenciadores::Gerenciador_Pontuacoes("ranking.dat");
}

Jogo::~Jogo() {
    if (faseAtual) {
        delete faseAtual;
        faseAtual = 0;
    }

    delete pJog1;
    pJog1 = 0;

    delete pJog2;
    pJog2 = 0;

    if (pGerenciadorPontuacoes) {
        delete pGerenciadorPontuacoes;
        pGerenciadorPontuacoes = 0;
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

            // Tratar entrada de texto para entrada de nome
            if (evento.type == sf::Event::TextEntered) {
                if (menu.emTelaEntradaNome() || menu.emTelaEntradaNomeJ2()) {
                    menu.adicionarLetraAoNome(evento.text.unicode);
                }
            }

            if (evento.type == sf::Event::KeyPressed) {
                if (estado == ESTADO_TELA_MORTE) {
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
                            // Salvar pontuação quando volta ao menu
                            if (!nomeJogadorAtual.empty() && pJog1->getPontos() > 0) {
                                pGerenciadorPontuacoes->adicionarPontuacao(nomeJogadorAtual, pJog1->getPontos());
                            }
                            if (!nomeJogador2Atual.empty() && pJog2->getPontos() > 0) {
                                pGerenciadorPontuacoes->adicionarPontuacao(nomeJogador2Atual, pJog2->getPontos());
                            }
                            delete faseAtual;
                            faseAtual = 0;
                            menu.resetarMenu();
                            telaMorte.resetar();
                            estado = ESTADO_MENU;
                            nomeJogadorAtual = "";
                            nomeJogador2Atual = "";
                            faseSelecionada = -1;
                        }
                    }
                }
                // Tratamento para tela de entrada de nome
                else if (menu.emTelaEntradaNome()) {
                    if (evento.key.code == sf::Keyboard::Enter) {
                        std::string nome = menu.getNomeJogador();
                        if (!nome.empty() && faseSelecionada >= 0) {
                            nomeJogadorAtual = nome;
                            
                            if (menu.getNumJogadores() == 2) {
                                // Vai para tela de entrada do jogador 2
                                menu.irParaNomeJogador2();
                            } else {
                                // 1 jogador: iniciar jogo
                                Entidades::Personagens::Jogador* p2 = 0;
                                
                                if (faseSelecionada == 0) {
                                    delete faseAtual;
                                    faseAtual = new Fases::Fase_Lua(pJog1, p2, nomeJogadorAtual, "");
                                } else if (faseSelecionada == 1) {
                                    delete faseAtual;
                                    faseAtual = new Fases::Fase_Marte(pJog1, p2, nomeJogadorAtual, "");
                                }
                                
                                if (faseAtual) {
                                    pJog1->resetar();
                                    estado = ESTADO_JOGANDO;
                                    faseSelecionada = -1;
                                    menu.confirmarNome();
                                }
                            }
                        }
                    }
                    else if (evento.key.code == sf::Keyboard::BackSpace) {
                        menu.removerLetraDoNome();
                    }
                    else if (evento.key.code == sf::Keyboard::Escape) {
                        faseSelecionada = -1;
                        nomeJogadorAtual = "";
                        nomeJogador2Atual = "";
                        menu.voltarDaTelaNome();
                    }
                }
                // Tratamento para tela de entrada de nome do jogador 2
                else if (menu.emTelaEntradaNomeJ2()) {
                    if (evento.key.code == sf::Keyboard::Enter) {
                        std::string nome2 = menu.getNomeJogador2();
                        if (!nome2.empty() && faseSelecionada >= 0) {
                            nomeJogador2Atual = nome2;
                            
                            // 2 jogadores: iniciar jogo com ambos
                            Entidades::Personagens::Jogador* p2 = pJog2;
                            
                            if (faseSelecionada == 0) {
                                delete faseAtual;
                                faseAtual = new Fases::Fase_Lua(pJog1, p2, nomeJogadorAtual, nomeJogador2Atual);
                            } else if (faseSelecionada == 1) {
                                delete faseAtual;
                                faseAtual = new Fases::Fase_Marte(pJog1, p2, nomeJogadorAtual, nomeJogador2Atual);
                            }
                            
                            if (faseAtual) {
                                pJog1->resetar();
                                pJog2->resetar();
                                estado = ESTADO_JOGANDO;
                                faseSelecionada = -1;
                                menu.confirmarNomeJ2();
                            }
                        }
                    }
                    else if (evento.key.code == sf::Keyboard::BackSpace) {
                        menu.removerLetraDoNome();
                    }
                    else if (evento.key.code == sf::Keyboard::Escape) {
                        // Volta para tela de entrada do jogador 1
                        nomeJogador2Atual = "";
                        menu.entrarTelaNome();
                    }
                }
                // Tratamento para tela de ranking
                else if (menu.emTelaRanking()) {
                    if (evento.key.code == sf::Keyboard::Enter) {
                        menu.voltarDoRanking();
                    }
                }
                // navegação do Menu
                else if (estado == ESTADO_MENU) {
                    if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
                        menu.subirOpcao();
                    }
                    else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
                        menu.descerOpcao();
                    }
                    else if (evento.key.code == sf::Keyboard::Enter) {
                        if (menu.emTelaFases()) {
                            int fase = menu.getOpcaoFaseSelecionada();
                            if (fase == 0 || fase == 1) {
                                // Fase selecionada, agora pedir nome
                                faseSelecionada = fase;
                                menu.entrarTelaNome();
                            } else if (fase == 2) {
                                // Voltar
                                menu.sairSubmenu();
                            }
                        } else {
                            menu.entrarSubmenu();
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
                    telaMorte.tocarGameOver();
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