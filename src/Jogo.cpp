#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Plataforma.h"
#include "Configuracao.h"

namespace AlienBusters {

Jogo* Jogo::instancia = 0;

Jogo* Jogo::getInstancia() {
    if (instancia == 0) {
        instancia = new Jogo();
    }
    return instancia;
}

Jogo::Jogo() : faseAtual(0), pJog1(0), pJog2(0),
               menu(this), telaMorte(), telaVitoria(), estado(ESTADO_MENU), nomeJogadorAtual(""),
               nomeJogador2Atual(""), faseSelecionada(-1), faseEmAndamento(-1),
               doisJogadoresAtual(false), pontuacaoSalva(false) {
    Ente::setGG(Gerenciadores::Gerenciador_Grafico::getInstancia());

    pJog1 = new Entidades::Personagens::Jogador(
        Config::POSICAO_INICIAL_X, Config::POSICAO_INICIAL_Y, true);

    pJog2 = new Entidades::Personagens::Jogador(
        Config::POSICAO_INICIAL_X + 70.f, Config::POSICAO_INICIAL_Y, false, "assets/textures/player2.png");
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
}

void Jogo::executar() {
    Gerenciadores::Gerenciador_Grafico* GG = Gerenciadores::Gerenciador_Grafico::getInstancia();
    sf::Clock clock;

    while (GG->estaAberto()) {
        float dt = clock.restart().asSeconds();
        processarEventos();
        atualizarEDesenhar(dt);
    }
}

void Jogo::processarEventos() {
    Gerenciadores::Gerenciador_Grafico* GG = Gerenciadores::Gerenciador_Grafico::getInstancia();

    sf::Event evento;
    while (GG->coletarEventos(evento)) {
        if (evento.type == sf::Event::Closed) {
            GG->fecharJanela();
        }

        if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::F1) {
            GG->setMostrarHitboxes(!GG->getMostrarHitboxes());
        }

        if (evento.type == sf::Event::TextEntered) {
            if (menu.emTelaEntradaNome() || menu.emTelaEntradaNomeJ2()) {
                menu.adicionarLetraAoNome(evento.text.unicode);
            }
        }

        if (evento.type != sf::Event::KeyPressed) {
            continue;
        }

        if (estado == ESTADO_TELA_MORTE) {
            tratarEventoTelaMorte(evento);
        } else if (estado == ESTADO_TELA_VITORIA) {
            tratarEventoTelaVitoria(evento);
        } else if (menu.emTelaEntradaNome()) {
            tratarEventoEntradaNome(evento);
        } else if (menu.emTelaEntradaNomeJ2()) {
            tratarEventoEntradaNomeJ2(evento);
        } else if (menu.emTelaRanking()) {
            if (evento.key.code == sf::Keyboard::Enter) {
                menu.voltarDoRanking();
            }
        } else if (estado == ESTADO_MENU) {
            tratarEventoMenu(evento);
        }
    }
}

void Jogo::atualizarEDesenhar(float dt) {
    Gerenciadores::Gerenciador_Grafico* GG = Gerenciadores::Gerenciador_Grafico::getInstancia();

    GG->renderizar();

    if (estado == ESTADO_MENU) {
        menu.desenhar();
    } else if (estado == ESTADO_JOGANDO) {
        if (faseAtual) {
            faseAtual->executar(dt);
            if (faseAtual->jogadorPerdeu()) {
                telaMorte.tocarGameOver();
                estado = ESTADO_TELA_MORTE;
            } else if (faseAtual->faseConcluida()) {
                avancarFase();
            }
        }
    } else if (estado == ESTADO_TELA_VITORIA) {
        if (faseAtual) {
            faseAtual->desenhar();
        }
        telaVitoria.desenhar();
    } else {
        if (faseAtual) {
            faseAtual->desenhar();
        }
        telaMorte.desenhar();
    }

    GG->mostrar();
}

void Jogo::tratarEventoTelaMorte(const sf::Event& evento) {
    if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
        telaMorte.subirOpcao();
    } else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
        telaMorte.descerOpcao();
    } else if (evento.key.code == sf::Keyboard::Enter) {
        if (telaMorte.getOpcaoSelecionada() == 0) {
            if (faseAtual) {
                faseAtual->reiniciar();
            }
            telaMorte.resetar();
            estado = ESTADO_JOGANDO;
        } else {
            voltarAoMenu();
        }
    }
}

void Jogo::tratarEventoTelaVitoria(const sf::Event& evento) {
    if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
        telaVitoria.subirOpcao();
    } else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
        telaVitoria.descerOpcao();
    } else if (evento.key.code == sf::Keyboard::Enter) {
        if (telaVitoria.getOpcaoSelecionada() == 0) {
            iniciarFase(FASE_LUA, doisJogadoresAtual);
        } else {
            voltarAoMenu();
        }
    }
}

void Jogo::tratarEventoEntradaNome(const sf::Event& evento) {
    if (evento.key.code == sf::Keyboard::Enter) {
        std::string nome = menu.getNomeJogador();
        if (!nome.empty() && faseSelecionada >= 0) {
            nomeJogadorAtual = nome;

            if (menu.getNumJogadores() == 2) {
                menu.irParaNomeJogador2();
            } else {
                iniciarFase(faseSelecionada, false);
            }
        }
    } else if (evento.key.code == sf::Keyboard::BackSpace) {
        menu.removerLetraDoNome();
    } else if (evento.key.code == sf::Keyboard::Escape) {
        faseSelecionada = -1;
        nomeJogadorAtual = "";
        nomeJogador2Atual = "";
        menu.voltarDaTelaNome();
    }
}

void Jogo::tratarEventoEntradaNomeJ2(const sf::Event& evento) {
    if (evento.key.code == sf::Keyboard::Enter) {
        std::string nome2 = menu.getNomeJogador2();
        if (!nome2.empty() && faseSelecionada >= 0) {
            nomeJogador2Atual = nome2;
            iniciarFase(faseSelecionada, true);
        }
    } else if (evento.key.code == sf::Keyboard::BackSpace) {
        menu.removerLetraDoNome();
    } else if (evento.key.code == sf::Keyboard::Escape) {
        // Volta para a tela de entrada do jogador 1
        nomeJogador2Atual = "";
        menu.entrarTelaNome();
    }
}

void Jogo::tratarEventoMenu(const sf::Event& evento) {
    Gerenciadores::Gerenciador_Grafico* GG = Gerenciadores::Gerenciador_Grafico::getInstancia();

    if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
        menu.subirOpcao();
    } else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
        menu.descerOpcao();
    } else if (evento.key.code == sf::Keyboard::Enter) {
        if (menu.emTelaFases()) {
            int fase = menu.getOpcaoFaseSelecionada();
            if (fase == FASE_LUA || fase == FASE_MARTE) {
                faseSelecionada = fase;
                menu.entrarTelaNome();
            } else if (fase == FASE_VOLTAR) {
                menu.sairSubmenu();
            }
        } else if (menu.getOpcaoSelecionada() == OPCAO_SAIR) {
            GG->fecharJanela();
        } else {
            menu.entrarSubmenu();
        }
    }
}

void Jogo::iniciarFase(int fase, bool doisJogadores) {
    Entidades::Personagens::Jogador* p2 = doisJogadores ? pJog2 : 0;
    std::string nome2 = doisJogadores ? nomeJogador2Atual : "";

    delete faseAtual;
    faseAtual = 0;

    if (fase == FASE_LUA) {
        faseAtual = new Fases::Fase_Lua(pJog1, p2, nomeJogadorAtual, nome2);
    } else if (fase == FASE_MARTE) {
        faseAtual = new Fases::Fase_Marte(pJog1, p2, nomeJogadorAtual, nome2);
    }

    if (faseAtual) {
        pJog1->resetar();
        if (doisJogadores) {
            pJog2->resetar();
            menu.confirmarNomeJ2();
        } else {
            menu.confirmarNome();
        }
        estado = ESTADO_JOGANDO;
        faseSelecionada = -1;
        faseEmAndamento = fase;
        doisJogadoresAtual = doisJogadores;
        pontuacaoSalva = false;
    }
}

void Jogo::avancarFase() {
    int proximaFase = faseEmAndamento + 1;

    if (proximaFase > FASE_MARTE) {
        salvarPontuacoes();
        telaVitoria.resetar();
        telaVitoria.tocarVitoria();
        estado = ESTADO_TELA_VITORIA;
        return;
    }

    int pontos1 = pJog1->getPontos();
    int pontos2 = pJog2->getPontos();

    iniciarFase(proximaFase, doisJogadoresAtual);

    pJog1->adicionarPontos(pontos1);
    if (doisJogadoresAtual) {
        pJog2->adicionarPontos(pontos2);
    }
}

void Jogo::voltarAoMenu() {
    salvarPontuacoes();

    // Recarrega o ranking do arquivo em segundo plano (thread) para que a tela
    // de ranking no menu ja apareca atualizada, sem precisar reiniciar o jogo.
    Gerenciadores::Gerenciador_Pontuacoes::getInstancia()->recarregarRankingAsync();

    delete faseAtual;
    faseAtual = 0;
    menu.resetarMenu();
    telaMorte.resetar();
    estado = ESTADO_MENU;
    nomeJogadorAtual = "";
    nomeJogador2Atual = "";
    faseSelecionada = -1;
    faseEmAndamento = -1;
    doisJogadoresAtual = false;
    pontuacaoSalva = false;
}

void Jogo::salvarPontuacoes() {
    if (pontuacaoSalva) {
        return;
    }

    Gerenciadores::Gerenciador_Pontuacoes* gp =
        Gerenciadores::Gerenciador_Pontuacoes::getInstancia();

    if (!nomeJogadorAtual.empty() && pJog1->getPontos() > 0) {
        gp->adicionarPontuacao(nomeJogadorAtual, pJog1->getPontos());
    }
    if (!nomeJogador2Atual.empty() && pJog2->getPontos() > 0) {
        gp->adicionarPontuacao(nomeJogador2Atual, pJog2->getPontos());
    }

    pontuacaoSalva = true;
}

}