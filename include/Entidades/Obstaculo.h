#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Entidades/Entidade.h"
#include "Entidades/Jogador.h"

namespace Entidades {

class Obstaculo : public Entidade {
protected:
    bool danoso;

public:
    Obstaculo();
    virtual ~Obstaculo();

    void salvarDataBuffer();

    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void obstaculizar(Jogador *p) = 0;
    virtual void jogadorPisou() {}
};

}

#endif