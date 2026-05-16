#include "../include/Jogo.h"

Jogo::Jogo() : GG() {
    executar();
}

Jogo::~Jogo() {}

void Jogo::executar() {
    while (GG.estaAberto()) {
        GG.processarEventos();
        GG.renderizar();
        GG.mostrar();
    }
}