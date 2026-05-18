#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "Ente.h"

namespace Entidades {

class Entidade : public Ente {
protected:
    int x;
    int y;

    void salvarDataBuffer();

public:
    Entidade();
    virtual ~Entidade();

public:
    virtual void executar() = 0;
    virtual void salvar() = 0;

    int getX() const;
    int getY() const;
};

}

#endif