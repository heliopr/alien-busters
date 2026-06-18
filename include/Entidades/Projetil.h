#ifndef PROJETIL_H
#define PROJETIL_H

#include "Entidades/Entidade.h"

namespace AlienBusters {
namespace Entidades {

namespace Personagens { class Jogador; }

namespace Projeteis {

class Projetil : public Entidade {
protected:
    bool ativo;
    float vx;
    Personagens::Jogador* dono;
    bool sofreGravidade;
    bool inimigo;
    bool quicavel;

public:
    Projetil(float x = 0.f, float y = 0.f, float vx = 0.f, float vy = 0.f,
             Personagens::Jogador* dono = 0, bool inimigo = false);
    ~Projetil();

    void executar(float dt);
    void salvar();

    bool getAtivo() const { return ativo; }
    void setAtivo(bool b) { ativo = b; }
    float getVx() const { return vx; }
    void setVx(float v) { vx = v; }
    Personagens::Jogador* getDono() const { return dono; }
    bool getInimigo() const { return inimigo; }
    bool getQuicavel() const { return quicavel; }

    virtual void quicar() {}
};

}
}
}

#endif