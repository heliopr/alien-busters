#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "Ente.h"
#include "Configuracao.h"
#include <sstream>

namespace Entidades {

class Entidade : public Ente {
protected:
    float x;
    float y;
    float vy;

    std::ostringstream buffer;
    void salvarDataBuffer();

    void aplicarGravidade(float dt, float gravidade = Config::GRAVIDADE);
    void contrariarGravidade(float dt);

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
    float getVy() const;
    void setVy(float v);
    virtual sf::FloatRect getHitbox() const = 0;
};

}

#endif