#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Entidades/Entidade.h"

namespace Entidades {
namespace Personagens { class Jogador; }
namespace Obstaculos {

class Obstaculo : public Entidade {
protected:
    bool danoso;

    bool colidiuComJogador(Personagens::Jogador *p) const;

public:
    Obstaculo();
    virtual ~Obstaculo();

    void salvarDataBuffer();

    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void obstaculizar(Personagens::Jogador *p) = 0;

    virtual bool colide() const { return true; }

    virtual void destruir() {}
    virtual bool getDestruido() const { return false; }
};

}
}

#endif
