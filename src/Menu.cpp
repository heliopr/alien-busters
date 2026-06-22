#include "Menu.h"
#include "Jogo.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include <iostream>

namespace AlienBusters {

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
    opcaoNovoJogoSelecionada(0),
    opcaoContinuarSelecionada(0),
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

    std::string nomesOpcoes[] = { "NOVO JOGO", "CONTINUAR", "RANKING", "SAIR" };
    criarTextos(opcoes, nomesOpcoes, 4, 180.f);

    std::string nomesNovoJogo[] = { "1 JOGADOR", "JOGAR", "VOLTAR" };
    criarTextos(opcoesNovoJogo, nomesNovoJogo, 3, 150.f);

    textoCursor.setFont(fonte);
    textoCursor.setCharacterSize(50);
    textoCursor.setFillColor(sf::Color::White);
    textoCursor.setPosition(sf::Vector2f(400.f, 300.f));
}

Menu::~Menu() {
    pJog = 0;
    opcoes.clear();
    opcoesNovoJogo.clear();
    textoRanking.clear();
    opcoesContinuar.clear();
    saves.clear();
}

void Menu::subirOpcao() {
    if (telaAtual == TELA_NOVO_JOGO) {
        if (opcaoNovoJogoSelecionada - 1 >= 0) {
            opcoesNovoJogo[opcaoNovoJogoSelecionada].setFillColor(sf::Color::White);
            opcaoNovoJogoSelecionada--;
            opcoesNovoJogo[opcaoNovoJogoSelecionada].setFillColor(sf::Color::Red);
        }
    } else if (telaAtual == TELA_CONTINUAR) {
        if (opcaoContinuarSelecionada - 1 >= 0) {
            opcaoContinuarSelecionada--;
            atualizarCoresContinuar();
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
    if (telaAtual == TELA_NOVO_JOGO) {
        if (opcaoNovoJogoSelecionada + 1 < (int)opcoesNovoJogo.size()) {
            opcoesNovoJogo[opcaoNovoJogoSelecionada].setFillColor(sf::Color::White);
            opcaoNovoJogoSelecionada++;
            opcoesNovoJogo[opcaoNovoJogoSelecionada].setFillColor(sf::Color::Red);
        }
    } else if (telaAtual == TELA_CONTINUAR) {
        if (opcaoContinuarSelecionada + 1 < (int)opcoesContinuar.size()) {
            opcaoContinuarSelecionada++;
            atualizarCoresContinuar();
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
            // Novo jogo: escolher jogadores e fase inicial
            telaAtual = TELA_NOVO_JOGO;
            opcaoNovoJogoSelecionada = 0;
            for (int i = 0; i < (int)opcoesNovoJogo.size(); ++i) {
                opcoesNovoJogo[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
            }
        } else if (opcaoSelecionada == 1) {
            // Continuar jogo salvo
            entrarTelaContinuar();
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

void Menu::entrarTelaContinuar() {
    telaAtual = TELA_CONTINUAR;
    opcaoContinuarSelecionada = 0;

    saves = Gerenciadores::Gerenciador_Salvamento::getInstancia()->getSaves();
    opcoesContinuar.clear();

    const char* nomesFases[] = { "LUA", "MARTE" };

    for (size_t i = 0; i < saves.size(); ++i) {
        sf::Text entrada;
        entrada.setFont(fonte);

        std::string nomeFase = (saves[i].fase >= 0 && saves[i].fase <= 1)
            ? nomesFases[saves[i].fase] : "?";

        std::stringstream ss;
        ss << saves[i].nome1;
        if (saves[i].numJogadores == 2 && !saves[i].nome2.empty()) {
            ss << " & " << saves[i].nome2;
        }
        ss << "  -  Fase " << nomeFase << "  -  " << saves[i].pontos1 << " pts";

        entrada.setString(ss.str());
        entrada.setCharacterSize(34);
        entrada.setFillColor(sf::Color::White);

        sf::FloatRect limites = entrada.getLocalBounds();
        entrada.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        entrada.setPosition(sf::Vector2f(400.f, 200.f + (i * 70.f)));

        opcoesContinuar.push_back(entrada);
    }

    // Entrada final "VOLTAR" (sempre presente)
    sf::Text voltar;
    voltar.setFont(fonte);
    voltar.setString("VOLTAR");
    voltar.setCharacterSize(40);
    voltar.setFillColor(sf::Color::White);
    sf::FloatRect limitesVoltar = voltar.getLocalBounds();
    voltar.setOrigin(limitesVoltar.left + limitesVoltar.width / 2.0f,
                     limitesVoltar.top + limitesVoltar.height / 2.0f);
    voltar.setPosition(sf::Vector2f(400.f, 200.f + (saves.size() * 70.f) + 40.f));
    opcoesContinuar.push_back(voltar);

    atualizarCoresContinuar();
}

void Menu::atualizarCoresContinuar() {
    for (size_t i = 0; i < opcoesContinuar.size(); ++i) {
        opcoesContinuar[i].setFillColor(
            (int)i == opcaoContinuarSelecionada ? sf::Color::Red : sf::Color::White);
    }
}

void Menu::resetarMenu() {
    telaAtual = TELA_PRINCIPAL;
    opcaoSelecionada = 0;
    opcaoNovoJogoSelecionada = 0;
    opcaoContinuarSelecionada = 0;
    numJogadores = 1;
    emSubmenu = false;
    nomeJogador = "";
    nomeJogador2 = "";

    atualizarTextoJogadores();

    // Resetar cores das opções
    for (size_t i = 0; i < opcoes.size(); ++i) {
        opcoes[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
    }
    for (size_t i = 0; i < opcoesNovoJogo.size(); ++i) {
        opcoesNovoJogo[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
    }
}

void Menu::atualizarTextoJogadores() {
    if (opcoesNovoJogo.empty()) return;

    std::string texto = (numJogadores == 1) ? "1 JOGADOR" : "2 JOGADORES";
    opcoesNovoJogo[0].setString(texto);

    sf::FloatRect limites = opcoesNovoJogo[0].getLocalBounds();
    opcoesNovoJogo[0].setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
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
    } else if (telaAtual == TELA_NOVO_JOGO) {
        std::vector<sf::Text>& lista = opcoesNovoJogo;
        for (size_t i = 0; i < lista.size(); ++i) {
            pGG->desenharTextoTela(&lista[i]);
        }
    } else if (telaAtual == TELA_CONTINUAR) {
        sf::Text titulo;
        titulo.setFont(fonte);
        titulo.setString("JOGOS SALVOS");
        titulo.setCharacterSize(60);
        titulo.setFillColor(sf::Color::Yellow);
        sf::FloatRect limites = titulo.getLocalBounds();
        titulo.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        titulo.setPosition(sf::Vector2f(400.f, 80.f));
        pGG->desenharTextoTela(&titulo);

        if (saves.empty()) {
            sf::Text vazio;
            vazio.setFont(fonte);
            vazio.setString("Nenhum jogo salvo");
            vazio.setCharacterSize(36);
            vazio.setFillColor(sf::Color(180, 180, 180));
            sf::FloatRect lim = vazio.getLocalBounds();
            vazio.setOrigin(lim.left + lim.width / 2.0f, lim.top + lim.height / 2.0f);
            vazio.setPosition(sf::Vector2f(400.f, 300.f));
            pGG->desenharTextoTela(&vazio);
        }

        for (size_t i = 0; i < opcoesContinuar.size(); ++i) {
            pGG->desenharTextoTela(&opcoesContinuar[i]);
        }
    }
}

bool Menu::getEmSubmenu() const {
    return emSubmenu;
}

bool Menu::emTelaEntradaNome() const {
    return telaAtual == TELA_ENTRADA_NOME;
}

bool Menu::emTelaEntradaNomeJ2() const {
    return telaAtual == TELA_ENTRADA_NOME_J2;
}

bool Menu::emTelaRanking() const {
    return telaAtual == TELA_RANKING;
}

bool Menu::emTelaNovoJogo() const {
    return telaAtual == TELA_NOVO_JOGO;
}

bool Menu::emTelaContinuar() const {
    return telaAtual == TELA_CONTINUAR;
}

int Menu::getOpcaoSelecionada() const {
    return opcaoSelecionada;
}

int Menu::getOpcaoNovoJogoSelecionada() const {
    return opcaoNovoJogoSelecionada;
}

int Menu::getOpcaoContinuarSelecionada() const {
    return opcaoContinuarSelecionada;
}

int Menu::getNumSaves() const {
    return (int)saves.size();
}

const Gerenciadores::DadosSalvos& Menu::getSaveSelecionado() const {
    return saves[opcaoContinuarSelecionada];
}

int Menu::getNumJogadores() const {
    return numJogadores;
}

std::string Menu::getNomeJogador() const {
    return nomeJogador;
}

std::string Menu::getNomeJogador2() const {
    return nomeJogador2;
}

}
