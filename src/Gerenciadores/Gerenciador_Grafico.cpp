#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"

namespace Gerenciadores {

Gerenciador_Grafico::Gerenciador_Grafico() :
    janela(sf::VideoMode(800, 600), "Janela SFML") {
    janela.setFramerateLimit(60);
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
    janela.clear(sf::Color::White);
}

void Gerenciador_Grafico::mostrar() {
    janela.display();
}

}