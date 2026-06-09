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

Menu::Menu(Jogo* pJ) :
    Ente(),
    pJog(pJ),
    opcaoSelecionada(0),
    opcaoFaseSelecionada(0),
    emSubmenu(false)
{
    if (!fonte.loadFromFile("assets/fonts/PixelifySans-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte Pixelify Sans!" << std::endl;
    }

    std::string nomesOpcoes[] = { "FASES", "SAIR" };
    criarTextos(opcoes, nomesOpcoes, 2, 250.f);

    std::string nomesFases[] = { "FASE LUA", "FASE MARTE", "VOLTAR" };
    criarTextos(opcoesFases, nomesFases, 3, 190.f);
}

Menu::~Menu() {
    pJog = 0;
    opcoes.clear();
    opcoesFases.clear();
}

void Menu::subirOpcao() {
    if (emSubmenu) {
        if (opcaoFaseSelecionada - 1 >= 0) {
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::White);
            opcaoFaseSelecionada--;
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::Red);
        }
    } else {
        if (opcaoSelecionada - 1 >= 0) {
            opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
            opcaoSelecionada--;
            opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
        }
    }
}

void Menu::descerOpcao() {
    if (emSubmenu) {
        if (opcaoFaseSelecionada + 1 < (int)opcoesFases.size()) {
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::White);
            opcaoFaseSelecionada++;
            opcoesFases[opcaoFaseSelecionada].setFillColor(sf::Color::Red);
        }
    } else {
        if (opcaoSelecionada + 1 < (int)opcoes.size()) {
            opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
            opcaoSelecionada++;
            opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
        }
    }
}

void Menu::entrarSubmenu() {
    emSubmenu = true;
    opcaoFaseSelecionada = 0;
    for (int i = 0; i < (int)opcoesFases.size(); ++i) {
        opcoesFases[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
    }
}

void Menu::sairSubmenu() {
    emSubmenu = false;
}

void Menu::executar(float /*dt*/) {
    desenhar();
}

void Menu::desenhar() {
    if (pGG == 0) return;

    std::vector<sf::Text>& lista = emSubmenu ? opcoesFases : opcoes;
    for (size_t i = 0; i < lista.size(); ++i) {
        pGG->desenharTexto(&lista[i]);
    }
}
