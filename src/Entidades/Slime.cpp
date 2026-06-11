#include "Entidades/Slime.h"
#include <cstdlib>
#include <cstddef>

namespace Entidades {
namespace Personagens {

Slime::Slime(float x_ini, float y_ini)
    : Inimigo()
{
    x = x_ini;
    y = y_ini;
    num_vidas = 1;

    float v = 40.f + std::rand() % 40;
    velocidadeX = (std::rand() % 2 == 0) ? v : -v;

    pFig = new sf::RectangleShape(sf::Vector2f(128.f, 128.f));
    if (pFig != NULL) {
        pFig->setOrigin(64.f, 50.f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (animacao.carregar("assets/textures/slime.png", 8, 4, "Erro ao carregar textura do slime!")) {
            pFig->setTexture(animacao.getTextura());
            animacao.aplicar(pFig, 0, false);
        } else {
            pFig->setFillColor(sf::Color(0, 200, 80));
        }
    }
}

Slime::~Slime() {
}

void Slime::executar(float dt) {
    moverComGravidade(dt);
    atualizarFlashDano(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        animacao.atualizar(dt, 0.2f, 8);
        animacao.aplicar(pFig, 0, velocidadeX < 0);

        if (estaFlashando()) {
            pFig->setTexture(animacao.getTexturaBranca());
        } else {
            pFig->setTexture(animacao.getTextura());
        }
    }
}

void Slime::salvar() {
}

void Slime::mover() {
}

sf::FloatRect Slime::getHitbox() const {
    return sf::FloatRect(x - 28.f, y - 28.f, 56.f, 56.f);
}

}
}
