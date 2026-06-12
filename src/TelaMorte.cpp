#include "TelaMorte.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include <iostream>

TelaMorte::TelaMorte() : Ente(), opcaoSelecionada(0) {
    if (!fonte.loadFromFile("assets/fonts/PixelifySans-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte Pixelify Sans!" << std::endl;
    }

    titulo.setFont(fonte);
    titulo.setString("VOCE PERDEU");
    titulo.setCharacterSize(70);
    titulo.setFillColor(sf::Color::Red);

    sf::FloatRect limitesTitulo = titulo.getLocalBounds();
    titulo.setOrigin(limitesTitulo.left + limitesTitulo.width / 2.0f, limitesTitulo.top + limitesTitulo.height / 2.0f);
    titulo.setPosition(sf::Vector2f(400.f, 220.f));

    std::string nomesOpcoes[] = { "REINICIAR", "MENU" };
    const int totalOpcoes = 2;

    for (int i = 0; i < totalOpcoes; ++i) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(nomesOpcoes[i]);
        texto.setCharacterSize(50);
        texto.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

        sf::FloatRect limites = texto.getLocalBounds();
        texto.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        texto.setPosition(sf::Vector2f(400.f, 400.f + (i * 120.f)));

        opcoes.push_back(texto);
    }

    if (bufferGameOver.loadFromFile("assets/sounds/gameover.mp3")) {
        somGameOver.setBuffer(bufferGameOver);
    } else {
        std::cerr << "Erro ao carregar som assets/sounds/gameover.mp3!" << std::endl;
    }
}

TelaMorte::~TelaMorte() {
    opcoes.clear();
}

void TelaMorte::subirOpcao() {
    if (opcaoSelecionada - 1 >= 0) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada--;
        opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void TelaMorte::descerOpcao() {
    if (opcaoSelecionada + 1 < (int)opcoes.size()) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada++;
        opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
    }
}

void TelaMorte::resetar() {
    opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
    opcaoSelecionada = 0;
    opcoes[opcaoSelecionada].setFillColor(sf::Color::Red);
}

void TelaMorte::executar(float /*dt*/) {
    desenhar();
}

void TelaMorte::desenhar() {
    if (pGG == 0) return;

    pGG->desenharTextoTela(&titulo);
    for (size_t i = 0; i < opcoes.size(); ++i) {
        pGG->desenharTextoTela(&opcoes[i]);
    }
}

void TelaMorte::tocarGameOver() {
    somGameOver.play();
}