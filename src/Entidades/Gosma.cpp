#include "Entidades/Gosma.h"
#include "Entidades/Jogador.h"
#include <sstream>
#include <cstddef>
#include <cstdlib>
#include <iostream>

namespace AlienBusters {
namespace Entidades {
namespace Obstaculos {

Gosma::Gosma(float x, float y)
    : Obstaculo(), largura(60.f), altura(60.f), tempoLentidao(0) {
    this->x = x;
    this->y = y;
    danoso = false;

    tempoLentidao = 1.f + (std::rand() % 51) / 100.f;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        if (!textura.loadFromFile("assets/textures/gosma.png")) {
            std::cerr << "Erro ao carregar textura da gosma!" << std::endl;
            pFig->setFillColor(sf::Color(50, 50, 200, 160));
        } else {
            pFig->setTexture(&textura);
            pFig->setOrigin(sf::Vector2f(0.0f, -30.0f));
        }
    }
}

Gosma::~Gosma() {
}

void Gosma::executar(float dt) {
    aplicarGravidade(dt);
    contrariarGravidade(dt);
}

void Gosma::salvar() {
}

std::string Gosma::serializar() const {
    std::ostringstream ss;
    ss << "GOSMA " << x << " " << y;
    return ss.str();
}

void Gosma::obstaculizar(Personagens::Jogador* p) {
    if (colidiuComJogador(p) && p->getNoChao()) {
        p->ficarLento(tempoLentidao);
    }
}

sf::FloatRect Gosma::getHitbox() const {
    return sf::FloatRect(x, y, largura, altura);
}

}
}
}
