#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "Ente.h"

namespace Entidades {

class Entidade : public Ente {
protected:
    float x;
    float y;
    // TODO: buffer

    void salvarDataBuffer();

public:
    Entidade();
    virtual ~Entidade();

public:
    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;

    float getX() const;
    float getY() const;
};

}

#endif