#include "../../include/Gerenciadores/Gerenciador_Grafico.h"

Gerenciador_Grafico::Gerenciador_Grafico() :
    janela(sf::VideoMode(800, 600), "Janela SFML") {
}

Gerenciador_Grafico::~Gerenciador_Grafico() {
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
    janela.clear(sf::Color::Black);
}

void Gerenciador_Grafico::mostrar() {
    janela.display();
}