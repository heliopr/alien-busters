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
    int donoId;
    bool sofreGravidade;
    bool inimigo;
    bool quicavel;

public:
    Projetil(float x = 0.f, float y = 0.f, float vx = 0.f, float vy = 0.f,
             Personagens::Jogador* dono = 0, bool inimigo = false);
    ~Projetil();

    void executar(float dt = 0.f);
    void salvar();

    bool getAtivo() const;
    void setAtivo(bool b);
    float getVx() const;
    void setVx(float v);
    Personagens::Jogador* getDono() const;
    void setDono(Personagens::Jogador* d);
    int getDonoId() const;
    void setDonoId(int id);
    bool getInimigo() const;
    bool getQuicavel() const;

    virtual void quicar();
};

}
}
}

#endif