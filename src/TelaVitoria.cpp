#include "TelaVitoria.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include <iostream>

TelaVitoria::TelaVitoria() : Ente(), opcaoSelecionada(0) {
    if (!fonte.loadFromFile("assets/fonts/PixelifySans-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte Pixelify Sans!" << std::endl;
    }

    titulo.setFont(fonte);
    titulo.setString("VOCE VENCEU!");
    titulo.setCharacterSize(70);
    titulo.setFillColor(sf::Color(80, 220, 120));

    sf::FloatRect limitesTitulo = titulo.getLocalBounds();
    titulo.setOrigin(limitesTitulo.left + limitesTitulo.width / 2.0f, limitesTitulo.top + limitesTitulo.height / 2.0f);
    titulo.setPosition(sf::Vector2f(400.f, 220.f));

    std::string nomesOpcoes[] = { "JOGAR NOVAMENTE", "MENU" };
    const int totalOpcoes = 2;

    for (int i = 0; i < totalOpcoes; ++i) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(nomesOpcoes[i]);
        texto.setCharacterSize(50);
        texto.setFillColor(i == 0 ? sf::Color(80, 220, 120) : sf::Color::White);

        sf::FloatRect limites = texto.getLocalBounds();
        texto.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
        texto.setPosition(sf::Vector2f(400.f, 400.f + (i * 120.f)));

        opcoes.push_back(texto);
    }

    if (bufferVitoria.loadFromFile("assets/sounds/win.wav")) {
        somVitoria.setBuffer(bufferVitoria);
    } else {
        std::cerr << "Erro ao carregar som assets/sounds/win.wav!" << std::endl;
    }
}

TelaVitoria::~TelaVitoria() {
    opcoes.clear();
}

void TelaVitoria::subirOpcao() {
    if (opcaoSelecionada - 1 >= 0) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada--;
        opcoes[opcaoSelecionada].setFillColor(sf::Color(80, 220, 120));
    }
}

void TelaVitoria::descerOpcao() {
    if (opcaoSelecionada + 1 < (int)opcoes.size()) {
        opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
        opcaoSelecionada++;
        opcoes[opcaoSelecionada].setFillColor(sf::Color(80, 220, 120));
    }
}

void TelaVitoria::resetar() {
    opcoes[opcaoSelecionada].setFillColor(sf::Color::White);
    opcaoSelecionada = 0;
    opcoes[opcaoSelecionada].setFillColor(sf::Color(80, 220, 120));
}

void TelaVitoria::executar(float /*dt*/) {
    desenhar();
}

void TelaVitoria::desenhar() {
    if (pGG == 0) return;

    pGG->desenharTelaEscura();

    pGG->desenharTextoTela(&titulo);
    for (size_t i = 0; i < opcoes.size(); ++i) {
        pGG->desenharTextoTela(&opcoes[i]);
    }
}

void TelaVitoria::tocarVitoria() {
    somVitoria.play();
}
