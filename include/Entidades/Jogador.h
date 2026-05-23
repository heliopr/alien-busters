#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Entidade.h"

namespace Entidades {

class Jogador : public Entidade {
public:
    Jogador();
    ~Jogador();

    void executar();
    void salvar();
};

}

#endif
