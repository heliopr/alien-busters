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
    float tempoExplosao;
    bool destruido;
    sf::Texture texturaMina;

public:
    MinaExtraterrestre(float x, float y, float tempoExplosao = 1.0f);
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
