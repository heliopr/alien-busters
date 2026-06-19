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
               menu(this), telaMorte(), telaVitoria(), telaPause(), estado(ESTADO_MENU), nomeJogadorAtual(""),
               nomeJogador2Atual(""), faseSelecionada(-1), faseEmAndamento(-1),
               doisJogadoresAtual(false), pontuacaoSalva(false) {
    Ente::setGG(Gerenciadores::Gerenciador_Grafico::getInstancia());

    pJog1 = new Entidades::Personagens::Jogador(
        Config::POSICAO_INICIAL_X, Config::POSICAO_INICIAL_Y, true);

    pJog2 = new Entidades::Personagens::Jogador(
        Config::POSICAO_INICIAL_X + 70.f, Config::POSICAO_INICIAL_Y, false, "assets/textures/player2.png");

    // Inscreve o Jogo como observador dos eventos de entrada (padrao Observer).
    Gerenciadores::Gerenciador_Eventos::getInstancia()->inscrever(this);
}

Jogo::~Jogo() {
    Gerenciadores::Gerenciador_Eventos::getInstancia()->desinscrever(this);

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
    // Delega a coleta dos eventos ao Subject (Gerenciador_Eventos), que os
    // repassa a este Jogo (e a quaisquer outros observadores inscritos).
    Gerenciadores::Gerenciador_Eventos::getInstancia()->processar();
}

void Jogo::aoReceberEvento(const sf::Event& evento) {
    Gerenciadores::Gerenciador_Grafico* GG = Gerenciadores::Gerenciador_Grafico::getInstancia();

    if (evento.type == sf::Event::Closed) {
        // Ao fechar o jogo durante uma partida, salva o estado completo
        // da fase para permitir continuar exatamente de onde parou.
        if ((estado == ESTADO_JOGANDO || estado == ESTADO_PAUSE) &&
            faseAtual != 0 && !faseAtual->jogadorPerdeu()) {
            salvarEstadoCompleto();
        }
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
        return;
    }

    if (estado == ESTADO_TELA_MORTE) {
        tratarEventoTelaMorte(evento);
    } else if (estado == ESTADO_TELA_VITORIA) {
        tratarEventoTelaVitoria(evento);
    } else if (estado == ESTADO_PAUSE) {
        tratarEventoPause(evento);
    } else if (estado == ESTADO_JOGANDO) {
        if (evento.key.code == sf::Keyboard::Escape) {
            telaPause.resetar();
            estado = ESTADO_PAUSE;
        }
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
    } else if (estado == ESTADO_PAUSE) {
        if (faseAtual) {
            faseAtual->desenhar();
        }
        telaPause.desenhar();
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

void Jogo::tratarEventoPause(const sf::Event& evento) {
    if (evento.key.code == sf::Keyboard::Escape) {
        // Escape volta a jogar (alterna a pausa).
        estado = ESTADO_JOGANDO;
        return;
    }

    if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::W) {
        telaPause.subirOpcao();
    } else if (evento.key.code == sf::Keyboard::Down || evento.key.code == sf::Keyboard::S) {
        telaPause.descerOpcao();
    } else if (evento.key.code == sf::Keyboard::Enter) {
        int opcao = telaPause.getOpcaoSelecionada();
        if (opcao == TelaPause::OPCAO_CONTINUAR) {
            estado = ESTADO_JOGANDO;
        } else if (opcao == TelaPause::OPCAO_REINICIAR) {
            if (faseAtual) {
                faseAtual->reiniciar();
            }
            estado = ESTADO_JOGANDO;
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
        if (menu.emTelaNovoJogo()) {
            int sel = menu.getOpcaoNovoJogoSelecionada();
            if (sel == 0) {
                // Alternar entre 1 e 2 jogadores
                menu.alternarJogadores();
            } else if (sel == 1) {
                faseSelecionada = FASE_LUA;
                menu.entrarTelaNome();
            } else if (sel == 2) {
                faseSelecionada = FASE_MARTE;
                menu.entrarTelaNome();
            } else {
                menu.sairSubmenu();
            }
        } else if (menu.emTelaContinuar()) {
            if (menu.getOpcaoContinuarSelecionada() < menu.getNumSaves()) {
                continuarJogo(menu.getSaveSelecionado());
            } else {
                menu.sairSubmenu();
            }
        } else if (menu.getOpcaoSelecionada() == OPCAO_SAIR) {
            GG->fecharJanela();
        } else {
            menu.entrarSubmenu();
        }
    }
}

void Jogo::iniciarFase(int fase, bool doisJogadores,
                       int pontos1, int pontos2, int vidas1, int vidas2) {
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
        pJog1->restaurarEstado(pontos1, vidas1);
        if (doisJogadores) {
            pJog2->resetar();
            pJog2->restaurarEstado(pontos2, vidas2);
            menu.confirmarNomeJ2();
        } else {
            menu.confirmarNome();
        }
        estado = ESTADO_JOGANDO;
        faseSelecionada = -1;
        faseEmAndamento = fase;
        doisJogadoresAtual = doisJogadores;
        pontuacaoSalva = false;

        // Grava um checkpoint no inicio da fase, para poder continuar depois.
        salvarProgresso();
    }
}

void Jogo::avancarFase() {
    int proximaFase = faseEmAndamento + 1;

    if (proximaFase > FASE_MARTE) {
        salvarPontuacoes();
        // Jogo concluido: nao ha mais o que continuar, remove o save.
        Gerenciadores::Gerenciador_Salvamento::getInstancia()->removerJogo(nomeJogadorAtual);
        telaVitoria.resetar();
        telaVitoria.tocarVitoria();
        estado = ESTADO_TELA_VITORIA;
        return;
    }

    int pontos1 = pJog1->getPontos();
    int pontos2 = doisJogadoresAtual ? pJog2->getPontos() : 0;

    // Os pontos sao carregados para a proxima fase; as vidas voltam ao maximo.
    iniciarFase(proximaFase, doisJogadoresAtual, pontos1, pontos2);
}

void Jogo::salvarProgresso() {
    if (nomeJogadorAtual.empty()) {
        return;
    }

    Gerenciadores::DadosSalvos dados;
    dados.nome1 = nomeJogadorAtual;
    dados.nome2 = nomeJogador2Atual;
    dados.numJogadores = doisJogadoresAtual ? 2 : 1;
    dados.fase = faseEmAndamento;
    dados.pontos1 = pJog1->getPontos();
    dados.pontos2 = doisJogadoresAtual ? pJog2->getPontos() : 0;
    dados.vidas1 = pJog1->getNumVidas();
    dados.vidas2 = doisJogadoresAtual ? pJog2->getNumVidas() : 3;

    Gerenciadores::Gerenciador_Salvamento::getInstancia()->salvarJogo(dados);
}

void Jogo::salvarEstadoCompleto() {
    if (nomeJogadorAtual.empty() || faseAtual == 0) {
        return;
    }

    Gerenciadores::DadosSalvos dados;
    dados.nome1 = nomeJogadorAtual;
    dados.nome2 = nomeJogador2Atual;
    dados.numJogadores = doisJogadoresAtual ? 2 : 1;
    dados.fase = faseEmAndamento;
    dados.pontos1 = pJog1->getPontos();
    dados.pontos2 = doisJogadoresAtual ? pJog2->getPontos() : 0;
    dados.vidas1 = pJog1->getNumVidas();
    dados.vidas2 = doisJogadoresAtual ? pJog2->getNumVidas() : 3;

    dados.x1 = pJog1->getX();
    dados.y1 = pJog1->getY();
    dados.vy1 = pJog1->getVy();
    if (doisJogadoresAtual) {
        dados.x2 = pJog2->getX();
        dados.y2 = pJog2->getY();
        dados.vy2 = pJog2->getVy();
    }

    faseAtual->salvar(dados.entidades);

    Gerenciadores::Gerenciador_Salvamento::getInstancia()->salvarJogo(dados);
}

void Jogo::iniciarFaseSalva(const Gerenciadores::DadosSalvos& dados) {
    bool dois = (dados.numJogadores == 2);
    Entidades::Personagens::Jogador* p2 = dois ? pJog2 : 0;
    std::string nome2 = dois ? nomeJogador2Atual : "";

    delete faseAtual;
    faseAtual = 0;

    if (dados.fase == FASE_LUA) {
        faseAtual = new Fases::Fase_Lua(pJog1, p2, nomeJogadorAtual, nome2, false);
    } else if (dados.fase == FASE_MARTE) {
        faseAtual = new Fases::Fase_Marte(pJog1, p2, nomeJogadorAtual, nome2, false);
    }

    if (faseAtual == 0) {
        return;
    }

    pJog1->resetar();
    pJog1->restaurarEstado(dados.pontos1, dados.vidas1);
    pJog1->setX(dados.x1);
    pJog1->setY(dados.y1);
    pJog1->setVy(dados.vy1);

    if (dois) {
        pJog2->resetar();
        pJog2->restaurarEstado(dados.pontos2, dados.vidas2);
        pJog2->setX(dados.x2);
        pJog2->setY(dados.y2);
        pJog2->setVy(dados.vy2);
        menu.confirmarNomeJ2();
    } else {
        menu.confirmarNome();
    }

    faseAtual->carregar(dados.entidades);

    estado = ESTADO_JOGANDO;
    faseSelecionada = -1;
    faseEmAndamento = dados.fase;
    doisJogadoresAtual = dois;
    pontuacaoSalva = false;
}

void Jogo::continuarJogo(const Gerenciadores::DadosSalvos& dados) {
    bool dois = (dados.numJogadores == 2);

    nomeJogadorAtual = dados.nome1;
    nomeJogador2Atual = dois ? dados.nome2 : "";

    iniciarFaseSalva(dados);
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