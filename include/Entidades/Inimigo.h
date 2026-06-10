#ifndef INIMIGO_H
#define INIMIGO_H

#include "Entidades/Personagem.h"

namespace Entidades {
namespace Personagens {

class Jogador;

class Inimigo : public Personagem {
protected:
    int nivel_maldade;
    float velocidadeX;

    void moverComGravidade(float dt);

public:
    Inimigo();
    virtual ~Inimigo();

    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void danificar(Jogador* p);
    virtual sf::FloatRect getHitbox() const = 0;

    float getVelocidadeX() const { return velocidadeX; }
    void setVelocidadeX(float v) { velocidadeX = v; }
};

}
}

#endif
