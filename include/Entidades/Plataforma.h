#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "Entidades/Obstaculo.h"

namespace Entidades {
namespace Obstaculos {

class Plataforma : public Obstaculo {
private:
    float altura;
    float largura;
    bool pisada;
    bool caindo;
    float tempoPisada;
    float vy;
    float posXOriginal;
    float posYOriginal;
    float tempoRespawn;
    bool surgindo;
    float tempoSurgindo;

public:
    Plataforma(float x, float y, float largura, float altura);
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
