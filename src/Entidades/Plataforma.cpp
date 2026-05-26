#include "Entidades/Plataforma.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"

namespace Entidades {

Plataforma::Plataforma() : altura(50.f) { // Um pouco mais espessa para parecer um solo firme
    sf::Vector2u tamJanela = ::Ente::pGrafico->getTamanhoJanela();
    x = 0.f; 
    y = 550.f;  
    pFig = new sf::RectangleShape(sf::Vector2f(static_cast<float>(tamJanela.x), altura)); 
    pFig->setFillColor(sf::Color(145, 60, 25));
    pFig->setPosition(sf::Vector2f(x, y));
}

Plataforma::~Plataforma() {}

void Plataforma::executar(float ) {
}

void Plataforma::obstaculizar(Entidades::Jogador*) {
}

void Plataforma::salvar() {   
}

}  