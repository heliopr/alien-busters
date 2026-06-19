#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"

namespace AlienBusters {

Gerenciadores::Gerenciador_Grafico *Ente::pGG = 0;
int Ente::proximoId = 1;

Ente::Ente() : id(proximoId++), pFig(0) {}

Ente::~Ente() {
    if (pFig) {
        delete pFig;
        pFig = 0;
    }
}

void Ente::desenhar() {
    if (pGG) {
        pGG->desenharEnte(this);
    }
}

int Ente::getId() const {
    return id;
}

void Ente::setId(int novoId) {
    id = novoId;
}

int Ente::getProximoId() {
    return proximoId;
}

void Ente::setProximoId(int id) {
    proximoId = id;
}

sf::RectangleShape *Ente::getFigura() const {
    return pFig;
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico *pG) {
    pGG = pG;
}

}