#include "TelaPause.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include <iostream>

namespace AlienBusters {

TelaPause::TelaPause() : Ente(), opcaoSelecionada(0) {
    if (!fonte.loadFromFile("assets/fonts/PixelifySans-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte Pixelify Sans!" << std::endl;
    }

    titulo.setFont(fonte);
    titulo.setString("PAUSA");
    titulo.setCharacterSize(70);
    titulo.setFillColor(sf::Color::White);

    sf::FloatRect limitesTitulo = titulo.getLocalBounds();
    titulo.setOrigin(limitesTitulo.left + limitesTitulo.width / 2.0f, limitesTitulo.top + limitesTitulo.height / 2.0f);
    titulo.setPosition(sf::Vector2f(400.f, 180.f));

    std::string nomesOpcoes[] = { "CONTINUAR", "REINICIAR", "MENU" };
    const int totalOpcoes = 3;

    for (int i = 0; i < totalOpcoes; ++i) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(nomesOpcoes[i]);
        texto.setCharacterSize(50);
        texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

        sf::FloatRect limites = texto.getLocalBounds();
        texto.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        texto.setPosition(sf::Vector2f(400.f, 340.f + (i * 110.f)));

        opcoes.push_back(texto);
    }
}

TelaPause::~TelaPause() {
    opcoes.clear();
}

void TelaPause::subirOpcao() {
    if (opcaoSelecionada - 1 >= 0) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada--;
        opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void TelaPause::descerOpcao() {
    if (opcaoSelecionada + 1 < (int)opcoes.size()) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada++;
        opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void TelaPause::resetar() {
    opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
    opcaoSelecionada = 0;
    opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
}

void TelaPause::executar(float /*dt*/) {
    desenhar();
}

void TelaPause::desenhar() {
    if (pGG == 0) return;

    pGG->desenharTelaEscura();

    pGG->desenharTextoTela(&titulo);
    for (size_t i = 0; i < opcoes.size(); ++i) {
        pGG->desenharTextoTela(&opcoes[i]);
    }
}

}
