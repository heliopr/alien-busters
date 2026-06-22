#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Entidades/Entidade.h"
#include "Entidades/AnimacaoSprite.h"

namespace AlienBusters {
namespace Entidades {
namespace Personagens {

class Personagem : public Entidade {
protected:
    int num_vidas;
    bool noChao;
    AnimacaoSprite animacao;

public:
    Personagem();
    Personagem(int num_vidas);
    virtual ~Personagem();

    virtual void executar(float dt = 0.f) = 0;
    virtual void salvar() = 0;
    virtual void mover(float dt = 0) = 0;

    Personagem& operator--();

    bool getNoChao() const;
    void setNoChao(bool b);
};

}
}
}

#endif
