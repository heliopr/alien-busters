#ifndef MINAEXTRATERRESTRE_H
#define MINAEXTRATERRESTRE_H

#include "Entidades/Obstaculo.h"
#include <SFML/Graphics.hpp>

namespace AlienBusters {
namespace Entidades {
namespace Obstaculos {

class MinaExtraterrestre : public Obstaculo {
private:
    static const float INTERVALO_PISCAR;
    static const float RAIO_EXPLOSAO;

    float largura;
    float altura;
    float tempoExplosao;
    float tempoRestante;
    bool ativada;
    bool destruido;
    sf::Texture texturaMina;

    bool jogadorDentroDoRaio(Personagens::Jogador* p) const;

public:
    MinaExtraterrestre(float x, float y);
    ~MinaExtraterrestre();

    void executar(float dt);
    void salvar();
    void obstaculizar(Personagens::Jogador* p);
    void aplicarDano(Personagens::Jogador* p);

    sf::FloatRect getHitbox() const;

    bool colide() const { return false; }
    bool getDestruido() const { return destruido; }
    void destruir() { destruido = true; }
};

}
}
}

#endif
