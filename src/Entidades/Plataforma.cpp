#include "Entidades/Plataforma.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"

namespace Entidades {

Plataforma::Plataforma() : altura(60.f) { //mudei para 30 pra entidade nao passar reto, e .f pq praticamento tudo do sfml é em float
    
    sf::Vector2u tamJanela = ::Ente::pGrafico->getTamanhoJanela();//otimizei para que se quisermos mudar dps o tamanho da janela, a plataforma se ajusta automaticamente
    x = 0.f; 
    y = static_cast<float>(tamJanela.y) - altura; 
    pFig = new sf::RectangleShape(sf::Vector2f(static_cast<float>(tamJanela.x), altura)); 
    
    pFig->setFillColor(sf::Color(50, 50, 50));
    pFig->setPosition(sf::Vector2f(x, y));
}

Plataforma::~Plataforma() {}

void Plataforma::executar(float dt) {
}

void Plataforma::obstaculizar(Jogador *p) {
    // TODO
}

void Plataforma::salvar() {   
}

}