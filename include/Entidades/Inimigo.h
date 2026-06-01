#ifndef INIMIGO_H
#define INIMIGO_H

#include "Entidades/Personagem.h"

namespace Entidades {

class Jogador;

class Inimigo : public Personagem {
protected:
    int nivel_maldade;
    float velocidadeX;

public:
    Inimigo();
    virtual ~Inimigo();

    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void danificar(Jogador* p) = 0;
    virtual sf::FloatRect getLimitesColisao() const = 0;

    float getVelocidadeX() const { return velocidadeX; }
    void setVelocidadeX(float v) { velocidadeX = v; }
};

}

#endif
