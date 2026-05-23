#include "Entidades/Plataforma.h"

namespace Entidades {

Plataforma::Plataforma() : altura(0) {
    x = 20;
    y = 200;
    pFig = new sf::RectangleShape(sf::Vector2f(300.f, 30.f));
    pFig->setFillColor(sf::Color(50, 50, 50));
    pFig->setPosition(sf::Vector2f(x, y));
}

Plataforma::~Plataforma() {}

void Plataforma::executar(float dt) {
    desenhar();
}

void Plataforma::obstaculizar(Jogador *p) {
    // TODO
}

void Plataforma::salvar() {
    
}

}