#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"
#include <iostream> 

namespace Gerenciadores {

Gerenciador_Grafico::Gerenciador_Grafico() :
    janela(sf::VideoMode(800, 600), "Janela SFML") {
    janela.setFramerateLimit(60);

    if (!texturaFundo.loadFromFile("assets/textures/marte.png")) {
        std::cout << "Erro: Nao foi possivel carregar assets/textures/marte.png" << std::endl;
    } else {
        spriteFundo.setTexture(texturaFundo);

        float scaleX = 800.f / texturaFundo.getSize().x;
        float scaleY = 600.f / texturaFundo.getSize().y;
        spriteFundo.setScale(scaleX, scaleY);
    }
}

Gerenciador_Grafico::~Gerenciador_Grafico() {}

void Gerenciador_Grafico::desenharEnte(Ente *pE) {
    if (pE) {
        sf::RectangleShape *fig = pE->getFigura();
        if (fig) {
            janela.draw(*fig);
        }
    }
}

bool Gerenciador_Grafico::estaAberto() {
    return janela.isOpen();
}

void Gerenciador_Grafico::processarEventos() {
    sf::Event evento;
    while (janela.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            janela.close();
        }
    }
}

void Gerenciador_Grafico::renderizar() {
    if (texturaFundo.getSize().x > 0) {
        janela.clear();
        janela.draw(spriteFundo); 
    } 
    else {
        janela.clear(sf::Color(40, 40, 40)); 
    }
}

void Gerenciador_Grafico::mostrar() {
    janela.display();
}

} 