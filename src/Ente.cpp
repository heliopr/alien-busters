#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"

Gerenciadores::Gerenciador_Grafico *Ente::pGG = 0;

Ente::Ente() {}

Ente::~Ente() {}

void Ente::desenhar() {
    if (pGG) {
        pGG->desenharEnte(this);
    }
}

sf::RectangleShape *Ente::getFigura() const {
    return pFig;
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico *pG) {
    pGG = pG;
}