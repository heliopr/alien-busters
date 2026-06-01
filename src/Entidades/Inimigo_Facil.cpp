#include "Entidades/Inimigo_Facil.h"
#include "Entidades/Jogador.h"
#include "Configuracao.h"

namespace Entidades {

Inimigo_Facil::Inimigo_Facil(float x_ini, float y_ini) : Inimigo(), raio(20.0f) {
    x = x_ini;
    y = y_ini; 
    
    pFig = new sf::RectangleShape(sf::Vector2f(40.0f, 40.0f));
    if (pFig != NULL) {
        pFig->setFillColor(sf::Color::Red);
        pFig->setOrigin(20.0f, 20.0f);
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

Inimigo_Facil::~Inimigo_Facil() {
}

void Inimigo_Facil::executar(float dt) {
    vy += Config::GRAVIDADE * dt;
    
    x += velocidadeX * dt;
    y += vy * dt;

    if (y > Config::ALTURA_LIMITE_QUEDA) {
        y = Config::POSICAO_INICIAL_Y;
        vy = 0.f;
    }

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Inimigo_Facil::salvar() {
}

void Inimigo_Facil::danificar(Jogador* p) {
    if (p != NULL) {

    }
}

sf::FloatRect Inimigo_Facil::getLimitesColisao() const {
    if (pFig != NULL) {
        return pFig->getGlobalBounds();
    }
    return sf::FloatRect(x - 20.0f, y - 20.0f, 40.0f, 40.0f);
}

}
