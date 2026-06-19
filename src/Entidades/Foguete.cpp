#include "Entidades/Foguete.h"
#include <cstddef>
#include <iostream>
#include <sstream>

namespace AlienBusters {
namespace Entidades {

const float Foguete::LARGURA = 160.f;
const float Foguete::ALTURA = 160.f;

Foguete::Foguete(float x, float y) : Entidade() {
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(LARGURA, ALTURA));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        if (!textura.loadFromFile("assets/textures/foguete.png")) {
            std::cerr << "Erro ao carregar textura do foguete!" << std::endl;
            pFig->setFillColor(sf::Color(200, 200, 200));
        } else {
            pFig->setTexture(&textura);
        }
    }
}

Foguete::~Foguete() {
}

void Foguete::executar(float dt) {
    (void)dt;
}

void Foguete::salvar() {
    buffer.str("");
    buffer.clear();
    buffer << "FOGUETE ";
    salvarDataBuffer();
}

sf::FloatRect Foguete::getHitbox() const {
    return sf::FloatRect(x, y, LARGURA, ALTURA);
}

}
}
