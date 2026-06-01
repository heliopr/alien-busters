#ifndef INIMIGO_H
#define INIMIGO_H

#include "Entidades/Entidade.h"

namespace Entidades {

class Jogador;

class Inimigo : public Entidade {
protected:
    int nivel_maldade;
    float vy;
    float velocidadeX;
    bool noChao;

public:
    Inimigo();
    virtual ~Inimigo();

    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void danificar(Jogador* p) = 0;
    virtual sf::FloatRect getLimitesColisao() const = 0;

    float getVy() const { return vy; }
    void setVy(float v) { vy = v; }
    float getVelocidadeX() const { return velocidadeX; }
    void setVelocidadeX(float v) { velocidadeX = v; }
    bool getNoChao() const { return noChao; }
    void setNoChao(bool b) { noChao = b; }
};

}

#endif
