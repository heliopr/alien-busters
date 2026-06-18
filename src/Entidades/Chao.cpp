#include "Entidades/Chao.h"
#include <cstddef>
#include <sstream>

namespace AlienBusters {
namespace Entidades {

Chao::Chao(float x, float y, float largura, float altura, sf::Color cor) :
    Entidade(), altura(altura), largura(largura), cor(cor)
{
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
        pFig->setFillColor(cor);
    }
}

Chao::~Chao() {
}

void Chao::executar(float dt) {
    aplicarGravidade(dt);
    contrariarGravidade(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }
}

void Chao::salvar() {
    // TODO
}

std::string Chao::serializar() const {
    std::ostringstream ss;
    ss << "CHAO " << x << " " << y << " " << largura << " " << altura << " "
       << static_cast<int>(cor.r) << " " << static_cast<int>(cor.g) << " "
       << static_cast<int>(cor.b);
    return ss.str();
}

sf::FloatRect Chao::getHitbox() const {
    return sf::FloatRect(x, y, largura, altura);
}

}
}
