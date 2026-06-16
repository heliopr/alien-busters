#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Entidades/Entidade.h"

namespace Entidades {
namespace Personagens {

class Personagem : public Entidade {
protected:
    int num_vidas;
    bool noChao;

public:
    Personagem();
    virtual ~Personagem();

    void salvarDataBuffer();
    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void mover(float dt = 0) = 0;

    bool getNoChao() const { return noChao; }
    void setNoChao(bool b) { noChao = b; }
};

}
}

#endif
