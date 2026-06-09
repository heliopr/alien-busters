#ifndef MINAEXTRATERRESTRE_H
#define MINAEXTRATERRESTRE_H

#include "Entidades/Obstaculo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Obstaculos {

class MinaExtraterrestre : public Obstaculo {
private:
    float largura;
    float altura;
    short int danoVidas;
    bool destruido;
    sf::Texture texturaMina;

public:
    MinaExtraterrestre(float x, float y, float largura = 45.f, float altura = 45.f, short int dano = 1);
    ~MinaExtraterrestre();

    void executar(float dt);
    void salvar();
    void obstaculizar(Personagens::Jogador* p);
    void aplicarDano(Personagens::Jogador* p);

    sf::FloatRect getHitbox() const;

    bool getDestruido() const { return destruido; }
    void destruir() { destruido = true; }
};

}
}

#endif
