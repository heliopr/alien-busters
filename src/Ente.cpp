#include "../include/Ente.h"

Gerenciador_Grafico *Ente::pGG = NULL;

Ente::Ente() {}

Ente::~Ente() {}

// TODO: implementar desenhar (pFig)
void Ente::desenhar() {
}

void Ente::setGG(Gerenciador_Grafico *pG) {
    pGG = pG;
}