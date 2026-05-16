#include "Ente.h"

Gerenciadores::Gerenciador_Grafico *Ente::pGG = NULL;

Ente::Ente() {}

Ente::~Ente() {}

// TODO: implementar desenhar (pFig)
void Ente::desenhar() {
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico *pG) {
    pGG = pG;
}