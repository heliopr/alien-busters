#include "../include/Jogo.h"

#include "../include/Ente.h"

Jogo::Jogo() : GG() {
    Ente::setGG(&GG);
}

Jogo::~Jogo() {}

void Jogo::executar() {
    while (GG.estaAberto()) {
        GG.processarEventos();
        GG.renderizar();
        GG.mostrar();
    }
}