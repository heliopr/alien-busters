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
    MinaExtraterrestre(float x = 0.f, float y = 0.f);
    ~MinaExtraterrestre();

    void executar(float dt = 0.f);
    void salvar();
    void obstaculizar(Personagens::Jogador* p);
    void aplicarDano(Personagens::Jogador* p);

    sf::FloatRect getHitbox() const;

    bool colide() const;
    bool getDestruido() const;
    void destruir();
};

}
}
}

#endif
