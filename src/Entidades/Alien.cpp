#include "Entidades/Alien.h"
#include <cstdlib>
#include <cstddef>

namespace Entidades {
namespace Personagens {

Alien::Alien(float x_ini, float y_ini) : Inimigo(), velocidade(0.f),
    olhandoEsquerda(true), olhandoDireita(false)
{
    x = x_ini;
    y = y_ini;

    float v = 50.f + std::rand() % 50;
    velocidade = (std::rand() % 2 == 0) ? v : -v;
    velocidadeX = velocidade;

    pFig = new sf::RectangleShape(sf::Vector2f(72.0f, 72.0f));
    if (pFig != NULL) {
        pFig->setOrigin(36.0f, 48.0f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (animacao.carregar("assets/textures/alien.png", 4, 5, "Erro ao carregar a textura do inimigo facil!")) {
            pFig->setTexture(animacao.getTextura());
            animacao.aplicar(pFig, 1, false);
        }
    }
}

Alien::~Alien() {
}

void Alien::executar(float dt) {
    moverComGravidade(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        animacao.atualizar(dt, 0.15f, 4);

        if (velocidadeX < 0) {
            olhandoEsquerda = true;
            olhandoDireita = false;
        } else if (velocidadeX > 0) {
            olhandoEsquerda = false;
            olhandoDireita = true;
        }

        animacao.aplicar(pFig, 2, olhandoEsquerda);
    }
}

void Alien::salvar() {
}

sf::FloatRect Alien::getHitbox() const {
    return sf::FloatRect(x - 24.0f, y - 24.0f, 48.0f, 48.0f);
}

void Alien::mover() {
}

}
}