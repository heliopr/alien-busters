#include "Menu.h"
#include "Jogo.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include <iostream>

void Menu::criarTextos(std::vector<sf::Text>& lista, std::string nomes[], int total, float yInicio) {
    for (int i = 0; i < total; ++i) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(nomes[i]);
        texto.setCharacterSize(50);
        texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

        sf::FloatRect limites = texto.getLocalBounds();
        texto.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        texto.setPosition(sf::Vector2f(400.f, yInicio + (i * 120.f)));

        lista.push_back(texto);
    }
}

void Menu::gerarTextoRanking() {
    textoRanking.clear();

    sf::Text titulo;
    titulo.setFont(fonte);
    titulo.setString("RANKING TOP 10");
    titulo.setCharacterSize(60);
    titulo.setFillColor(sf::Color::Yellow);
    sf::FloatRect limites = titulo.getLocalBounds();
    titulo.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
    titulo.setPosition(sf::Vector2f(400.f, 50.f));
    textoRanking.push_back(titulo);

    {
        std::vector<Gerenciadores::EntradaPontuacao> top =
            Gerenciadores::Gerenciador_Pontuacoes::getInstancia()->getRankingTop(10);

        for (size_t i = 0; i < top.size(); ++i) {
            sf::Text entrada;
            entrada.setFont(fonte);

            std::stringstream ss;
            ss << (i + 1) << ". " << top[i].nome << " - " << top[i].pontos << " pts";
            entrada.setString(ss.str());
            entrada.setCharacterSize(40);
            entrada.setFillColor(sf::Color::White);

            sf::FloatRect limites = entrada.getLocalBounds();
            entrada.setOrigin(limites.left, limites.top);
            entrada.setPosition(sf::Vector2f(100.f, 150.f + (i * 60.f)));

            textoRanking.push_back(entrada);
        }
    }

    sf::Text opcao;
    opcao.setFont(fonte);
    opcao.setString("Pressione ENTER para voltar");
    opcao.setCharacterSize(30);
    opcao.setFillColor(sf::Color::Cyan);
    sf::FloatRect limites_opcao = opcao.getLocalBounds();
    opcao.setOrigin(limites_opcao.left + limites_opcao.width / 2.0f, limites_opcao.top);
    opcao.setPosition(sf::Vector2f(400.f, 750.f));
    textoRanking.push_back(opcao);
}

Menu::Menu(Jogo* pJ) :
    Ente(),
    pJog(pJ),
    opcaoSelecionada(0),
    opcaoFaseSelecionada(0),
    numJogadores(1),
    emSubmenu(false),
    telaAtual(TELA_PRINCIPAL),
    nomeJogador(""),
    nomeJogador2("")
{
    if (!fonte.loadFromFile("assets/fonts/PixelifySans-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte Pixelify Sans!" << std::endl;
    }

    if (!texturaFundo.loadFromFile("assets/textures/menu.png")) {
        std::cerr << "Erro ao carregar assets/textures/menu.png!" << std::endl;
    } else {
        spriteFundo.setTexture(texturaFundo);
        spriteFundo.setScale(1422.222f / texturaFundo.getSize().x, 800.f / texturaFundo.getSize().y);
    }

    std::string nomesOpcoes[] = { "1 JOGADOR", "FASES", "RANKING", "SAIR" };
    criarTextos(opcoes, nomesOpcoes, 4, 180.f);

    std::string nomesFases[] = { "FASE LUA", "FASE MARTE", "VOLTAR" };
    criarTextos(opcoesFases, nomesFases, 3, 190.f);

    textoCursor.setFont(fonte);
    textoCursor.setCharacterSize(50);
    textoCursor.setFillColor(sf::Color::White);
    textoCursor.setPosition(sf::Vector2f(400.f, 300.f));
}

Menu::~Menu() {
    pJog = 0;
    opcoes.clear();
    opcoesFases.clear();
    textoRanking.clear();
}

void Menu::subirOpcao() {
    if (telaAtual == TELA_FASES) {
        if (opcaoFaseSelecionada - 1 >= 0) {
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::White);
            opcaoFaseSelecionada--;
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::Red);
        }
    } else if (telaAtual == TELA_PRINCIPAL) {
        if (opcaoSelecionada - 1 >= 0) {
            opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
            opcaoSelecionada--;
            opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
        }
    }
}

void Menu::descerOpcao() {
    if (telaAtual == TELA_FASES) {
        if (opcaoFaseSelecionada + 1 < (int)opcoesFases.size()) {
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::White);
            opcaoFaseSelecionada++;
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::Red);
        }
    } else if (telaAtual == TELA_PRINCIPAL) {
        if (opcaoSelecionada + 1 < (int)opcoes.size()) {
            opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
            opcaoSelecionada++;
            opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
        }
    }
}

void Menu::entrarSubmenu() {
    if (telaAtual == TELA_PRINCIPAL) {
        if (opcaoSelecionada == 0) {
            // Alternar entre 1 e 2 jogadores
            alternarJogadores();
        } else if (opcaoSelecionada == 1) {
            // Entrar em fases
            telaAtual = TELA_FASES;
            opcaoFaseSelecionada = 0;
            for (int i = 0; i < (int)opcoesFases.size(); ++i) {
                opcoesFases[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
            }
        } else if (opcaoSelecionada == 2) {
            // Entrar em ranking
            telaAtual = TELA_RANKING;
            gerarTextoRanking();
        }
    }
}

void Menu::sairSubmenu() {
    emSubmenu = false;
    telaAtual = TELA_PRINCIPAL;
}

void Menu::alternarJogadores() {
    numJogadores = (numJogadores == 1) ? 2 : 1;
    atualizarTextoJogadores();
}

void Menu::entrarTelaNome() {
    telaAtual = TELA_ENTRADA_NOME;
    nomeJogador = "";
}

void Menu::irParaNomeJogador2() {
    telaAtual = TELA_ENTRADA_NOME_J2;
    nomeJogador2 = "";
}

void Menu::adicionarLetraAoNome(sf::Uint32 unicode) {
    // Permite letras, números e espaço
    if ((unicode >= 32 && unicode <= 126) && 
        ((telaAtual == TELA_ENTRADA_NOME && nomeJogador.length() < 20) ||
         (telaAtual == TELA_ENTRADA_NOME_J2 && nomeJogador2.length() < 20))) {
        
        if (telaAtual == TELA_ENTRADA_NOME) {
            nomeJogador += static_cast<char>(unicode);
        } else if (telaAtual == TELA_ENTRADA_NOME_J2) {
            nomeJogador2 += static_cast<char>(unicode);
        }
    }
}

void Menu::removerLetraDoNome() {
    if (telaAtual == TELA_ENTRADA_NOME) {
        if (!nomeJogador.empty()) {
            nomeJogador.erase(nomeJogador.length() - 1);
        }
    } else if (telaAtual == TELA_ENTRADA_NOME_J2) {
        if (!nomeJogador2.empty()) {
            nomeJogador2.erase(nomeJogador2.length() - 1);
        }
    }
}

void Menu::confirmarNome() {
    // Apenas limpa o nome após confirmar (sem mudar tela)
    nomeJogador = "";
}

void Menu::confirmarNomeJ2() {
    // Apenas limpa o nome após confirmar
    nomeJogador2 = "";
}

void Menu::voltarDaTelaNome() {
    telaAtual = TELA_PRINCIPAL;
    nomeJogador = "";
    nomeJogador2 = "";
}

void Menu::voltarDoRanking() {
    telaAtual = TELA_PRINCIPAL;
}

void Menu::resetarMenu() {
    telaAtual = TELA_PRINCIPAL;
    opcaoSelecionada = 0;
    opcaoFaseSelecionada = 0;
    numJogadores = 1;
    emSubmenu = false;
    nomeJogador = "";
    nomeJogador2 = "";
    
    // Resetar cores das opções
    for (size_t i = 0; i < opcoes.size(); ++i) {
        opcoes[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
    }
    for (size_t i = 0; i < opcoesFases.size(); ++i) {
        opcoesFases[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
    }
}

void Menu::atualizarTextoJogadores() {
    if (opcoes.empty()) return;

    std::string texto = (numJogadores == 1) ? "1 JOGADOR" : "2 JOGADORES";
    if (!nomeJogador.empty()) {
        texto = "JOGADOR: " + nomeJogador;
    }
    opcoes[0].setString(texto);

    sf::FloatRect limites = opcoes[0].getLocalBounds();
    opcoes[0].setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
}

void Menu::executar(float /*dt*/) {
    desenhar();
}

void Menu::desenhar() {
    if (pGG == 0) return;

    pGG->desenharSpriteTela(&spriteFundo);

    if (telaAtual == TELA_PRINCIPAL) {
        std::vector<sf::Text>& lista = opcoes;
        for (size_t i = 0; i < lista.size(); ++i) {
            pGG->desenharTextoTela(&lista[i]);
        }
    } else if (telaAtual == TELA_ENTRADA_NOME) {
        sf::Text titulo;
        titulo.setFont(fonte);
        std::string textoTitulo = (numJogadores == 1) ? "NOME:" : "NOME (player 1):";
        titulo.setString(textoTitulo);
        titulo.setCharacterSize(60);
        titulo.setFillColor(sf::Color::Yellow);
        sf::FloatRect limites = titulo.getLocalBounds();
        titulo.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        titulo.setPosition(sf::Vector2f(400.f, 150.f));
        pGG->desenharTextoTela(&titulo);

        sf::Text nomeTexto;
        nomeTexto.setFont(fonte);
        nomeTexto.setString(nomeJogador + "_");
        nomeTexto.setCharacterSize(50);
        nomeTexto.setFillColor(sf::Color::Cyan);
        sf::FloatRect limites2 = nomeTexto.getLocalBounds();
        nomeTexto.setOrigin(limites2.left + limites2.width / 2.0f, limites2.top);
        nomeTexto.setPosition(sf::Vector2f(400.f, 300.f));
        pGG->desenharTextoTela(&nomeTexto);

        sf::Text instrucao;
        instrucao.setFont(fonte);
        instrucao.setString("ENTER: Confirmar | BACKSPACE: Apagar");
        instrucao.setCharacterSize(25);
        instrucao.setFillColor(sf::Color::White);
        sf::FloatRect limites3 = instrucao.getLocalBounds();
        instrucao.setOrigin(limites3.left + limites3.width / 2.0f, limites3.top);
        instrucao.setPosition(sf::Vector2f(400.f, 450.f));
        pGG->desenharTextoTela(&instrucao);

        sf::Text esc;
        esc.setFont(fonte);
        esc.setString("ESC: Cancelar");
        esc.setCharacterSize(25);
        esc.setFillColor(sf::Color::Red);
        sf::FloatRect limites4 = esc.getLocalBounds();
        esc.setOrigin(limites4.left + limites4.width / 2.0f, limites4.top);
        esc.setPosition(sf::Vector2f(400.f, 500.f));
        pGG->desenharTextoTela(&esc);
    } else if (telaAtual == TELA_ENTRADA_NOME_J2) {
        sf::Text titulo;
        titulo.setFont(fonte);
        titulo.setString("NOME (player 2) :");
        titulo.setCharacterSize(60);
        titulo.setFillColor(sf::Color::Yellow);
        sf::FloatRect limites = titulo.getLocalBounds();
        titulo.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        titulo.setPosition(sf::Vector2f(400.f, 150.f));
        pGG->desenharTextoTela(&titulo);

        sf::Text nomeTexto;
        nomeTexto.setFont(fonte);
        nomeTexto.setString(nomeJogador2 + "_");
        nomeTexto.setCharacterSize(50);
        nomeTexto.setFillColor(sf::Color::Cyan);
        sf::FloatRect limites2 = nomeTexto.getLocalBounds();
        nomeTexto.setOrigin(limites2.left + limites2.width / 2.0f, limites2.top);
        nomeTexto.setPosition(sf::Vector2f(400.f, 300.f));
        pGG->desenharTextoTela(&nomeTexto);

        sf::Text instrucao;
        instrucao.setFont(fonte);
        instrucao.setString("ENTER: Confirmar | BACKSPACE: Apagar");
        instrucao.setCharacterSize(25);
        instrucao.setFillColor(sf::Color::White);
        sf::FloatRect limites3 = instrucao.getLocalBounds();
        instrucao.setOrigin(limites3.left + limites3.width / 2.0f, limites3.top);
        instrucao.setPosition(sf::Vector2f(400.f, 450.f));
        pGG->desenharTextoTela(&instrucao);

        sf::Text esc;
        esc.setFont(fonte);
        esc.setString("ESC: Voltar");
        esc.setCharacterSize(25);
        esc.setFillColor(sf::Color::Red);
        sf::FloatRect limites4 = esc.getLocalBounds();
        esc.setOrigin(limites4.left + limites4.width / 2.0f, limites4.top);
        esc.setPosition(sf::Vector2f(400.f, 500.f));
        pGG->desenharTextoTela(&esc);
    } else if (telaAtual == TELA_RANKING) {
        for (size_t i = 0; i < textoRanking.size(); ++i) {
            pGG->desenharTextoTela(&textoRanking[i]);
        }
    } else if (telaAtual == TELA_FASES) {
        std::vector<sf::Text>& lista = opcoesFases;
        for (size_t i = 0; i < lista.size(); ++i) {
            pGG->desenharTextoTela(&lista[i]);
        }
    }
}
