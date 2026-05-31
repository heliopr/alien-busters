#include "Menu.h"
#include "Jogo.h"
#include <iostream>

Menu::Menu(Jogo* pJ) : 
    Ente(), 
    pJog(pJ), 
    opcaoSelecionada(0) 
{
    if (!fonte.loadFromFile("arial.ttf")) {
        std::cerr << "Erro ao carregar a fonte arial.ttf!" << std::endl;
    }

    std::string nomesOpcoes[] = { "JOGAR", "SAIR" };
    int totalOpcoes = 2;

    for (int i = 0; i < totalOpcoes; ++i) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(nomesOpcoes[i]);
        texto.setCharacterSize(50);
        
        if (i == 0) {
            texto.setFillColor(sf::Color::Red);
        } else {
            texto.setFillColor(sf::Color::White);
        }

        sf::FloatRect limites = texto.getLocalBounds();
        texto.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        texto.setPosition(sf::Vector2f(400.f, 250.f + (i * 120.f)));

        opcoes.push_back(texto);
    }
}

Menu::~Menu() {
    pJog = 0;
    opcoes.clear();
}

void Menu::subirOpcao() {
    if (opcaoSelecionada - 1 >= 0) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada--;
        opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void Menu::descerOpcao() {
    if (opcaoSelecionada + 1 < (int)opcoes.size()) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada++;
        opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void Menu::executar(float /*dt*/) {
    desenhar();
}

void Menu::desenhar() {
    if (pGG != 0) {
        for (size_t i = 0; i < opcoes.size(); ++i) {
            pGG->getJanela()->draw(opcoes[i]);
        }
    }
}