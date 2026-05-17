#include "Ente.h"

Gerenciadores::Gerenciador_Grafico *Ente::pGG = 0;

Ente::Ente() {}

Ente::~Ente() {}

// TODO: implementar desenhar (pFig)
void Ente::desenhar() {
    if (pGG) {
        pGG->desenharEnte(this);
    }
}

sf::RectangleShape *Ente::getFig() const {
    return pFig;
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico *pG) {
    pGG = pG;
}