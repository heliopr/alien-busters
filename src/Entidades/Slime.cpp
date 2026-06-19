#include "Entidades/Slime.h"
#include <sstream>
#include <cstdlib>
#include <cstddef>

namespace AlienBusters {
namespace Entidades {
namespace Personagens {

Slime::Slime(float x_ini, float y_ini)
    : Inimigo()
{
    x = x_ini;
    y = y_ini;
    num_vidas = 1;

    nivel = (std::rand() % 100);

    float v = 50.f;
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
    mover(dt);
    atualizarFlashDano(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        animacao.atualizar(dt, 0.1f, 8);
        animacao.aplicar(pFig, 0, velocidadeX < 0);

        if (estaFlashando()) {
            pFig->setTexture(animacao.getTexturaBranca());
        } else {
            pFig->setTexture(animacao.getTextura());
        }
    }
}

void Slime::salvar() {
    buffer.str("");
    buffer.clear();
    buffer << "SLIME ";
    salvarDataBuffer();
}

void Slime::danificar(Jogador* p) {
    Inimigo::danificar(p);
}

int Slime::pontosAoMorrer() const {
    int pontos = Inimigo::pontosAoMorrer();

    float sorteio = std::rand() % 100;
    if (sorteio < nivel) {
        pontos += 50;
    }

    return pontos;
}

sf::FloatRect Slime::getHitbox() const {
    return sf::FloatRect(x - 28.f, y - 28.f, 56.f, 56.f);
}

}
}
}
