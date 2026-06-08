#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "Ente.h"
#include <sstream>

namespace Entidades {

class Entidade : public Ente {
protected:
    float x;
    float y;

    std::ostringstream buffer;
    void salvarDataBuffer();

public:
    Entidade();
    virtual ~Entidade();

public:
    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void desenhar();

    float getX() const;
    float getY() const;
    void setX(float novoX);
    void setY(float novoY);
    virtual sf::FloatRect getHitbox() const = 0;
};

}

#endif