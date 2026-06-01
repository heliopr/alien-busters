#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Entidades/Entidade.h"

namespace Entidades {

class Personagem : public Entidade {
protected:
    int num_vidas;
    float vy;
    bool noChao;

public:
    Personagem();
    virtual ~Personagem();

    void salvarDataBuffer();
    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void mover() = 0;

    float getVy() const { return vy; }
    void setVy(float v) { vy = v; }
    bool getNoChao() const { return noChao; }
    void setNoChao(bool b) { noChao = b; }
};

}

#endif
