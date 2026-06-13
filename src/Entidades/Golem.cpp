#include "Entidades/Golem.h"
#include "Configuracao.h"
#include <cstdlib>
#include <cstddef>

namespace Entidades {
namespace Personagens {

Golem::Golem(float x_ini, float y_ini)
    : Inimigo(), tempoRecarga(0.f)
{
    x = x_ini;
    y = y_ini;
    num_vidas = 5;

    tempoRecarga = 1.5f + ((std::rand() % 100) / 100.f * 0.5f);

    float v = 20.f + std::rand() % 20;
    velocidadeX = (std::rand() % 2 == 0) ? v : -v;

    pFig = new sf::RectangleShape(sf::Vector2f(202.5f, 144.f));
    if (pFig != NULL) {
        pFig->setOrigin(101.25f, 96.f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (animacao.carregar("assets/textures/golem.png", 10, 1, "Erro ao carregar textura do golem!")) {
            pFig->setTexture(animacao.getTextura());
            animacao.aplicar(pFig, 0, false);
        } else {
            pFig->setFillColor(sf::Color::Red);
        }
    }
}

Golem::~Golem() {
}

void Golem::executar(float dt) {
    moverComGravidade(dt);
    atualizarFlashDano(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        animacao.atualizar(dt, 0.1f, 10);
        animacao.aplicar(pFig, 0, velocidadeX < 0);

        if (estaFlashando()) {
            pFig->setTexture(animacao.getTexturaBranca());
        } else {
            pFig->setTexture(animacao.getTextura());
        }
    }
}

void Golem::salvar() {
}

void Golem::mover() {
}

sf::FloatRect Golem::getHitbox() const {
    return sf::FloatRect(x - 52.5f, y - 48, 105.f, 96.f);
}

bool Golem::querAtirar(float dt) {
    tempoRecarga -= dt;
    if (tempoRecarga <= 0.f) {
        tempoRecarga = tempoRecarga = 1.5f + ((std::rand() % 100) / 100.f * 0.5f);
        return true;
    }
    return false;
}

}
}
