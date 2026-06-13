#ifndef PROJETIL_H
#define PROJETIL_H

#include "Entidades/Entidade.h"

namespace Entidades {

namespace Personagens { class Jogador; }

class Projetil : public Entidade {
protected:
    bool ativo;
    float vx;
    Personagens::Jogador* dono;
    bool sofreGravidade;
    bool inimigo;

public:
    Projetil(float x = 0.f, float y = 0.f, float vx = 0.f, float vy = 0.f,
             Personagens::Jogador* dono = 0, bool inimigo = false);
    ~Projetil();

    void executar(float dt);
    void salvar();

    bool getAtivo() const { return ativo; }
    void setAtivo(bool b) { ativo = b; }
    float getVx() const { return vx; }
    Personagens::Jogador* getDono() const { return dono; }
    bool getInimigo() const { return inimigo; }
};

}

#endif