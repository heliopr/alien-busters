#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "Entidades/Obstaculo.h"

namespace Entidades {

class Plataforma : public Obstaculo {
private:
    int altura;

public:
    Plataforma();
    ~Plataforma();

    void executar(float dt);
    void obstaculizar(Jogador *p);
    void salvar();
};

}

#endif