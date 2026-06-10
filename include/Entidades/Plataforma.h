#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "Entidades/Obstaculo.h"

namespace Entidades {
namespace Obstaculos {

class Plataforma : public Obstaculo {
private:
    static const float LARGURA;
    static const float ALTURA;

    sf::Color cor;
    bool pisada;
    bool caindo;
    float tempoPisada;
    float posXOriginal;
    float posYOriginal;
    float tempoRespawn;
    bool surgindo;
    float tempoSurgindo;

public:
    Plataforma(float x, float y, sf::Color cor = sf::Color(145, 60, 25));
    ~Plataforma();

    void executar(float dt);
    void obstaculizar(Personagens::Jogador* p);
    void salvar();
    sf::FloatRect getHitbox() const;
    void jogadorPisou();
};

}
}

#endif
