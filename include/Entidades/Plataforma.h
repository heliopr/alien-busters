#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "Entidades/Obstaculo.h"

namespace Entidades {

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
    void obstaculizar(Jogador* p);
    void salvar();
    sf::FloatRect getLimitesColisao() const;
    void jogadorPisou();
};

}

#endif