#ifndef PROJETIL_H
#define PROJETIL_H

#include "Entidades/Entidade.h"

namespace Entidades {

class Projetil : public Entidade {
protected:
    bool ativo;
    float vx;

public:
    Projetil(float x = 0.f, float y = 0.f, float vx = 0.f, float vy = 0.f);
    ~Projetil();

    void executar(float dt);
    void salvar();

    sf::FloatRect getHitbox() const;
    bool getAtivo() const { return ativo; }
    void setAtivo(bool b) { ativo = b; }
    float getVx() const { return vx; }
};

}

#endif