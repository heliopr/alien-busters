#ifndef MINAEXTRATERRESTRE_H
#define MINAEXTRATERRESTRE_H

#include "Entidades/Obstaculo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {

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
    void obstaculizar(Jogador* p);
    void aplicarDano(Jogador* p);

    sf::FloatRect getHitbox() const;

    bool getDestruido() const { return destruido; }
    void destruir() { destruido = true; }
};

}

#endif
