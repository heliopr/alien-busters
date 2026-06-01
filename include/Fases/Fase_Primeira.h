#ifndef FASE_PRIMEIRA_H
#define FASE_PRIMEIRA_H

#include "Fases/Fase.h"

namespace Fases {

class Fase_Primeira : public Fase {
public:
    Fase_Primeira();
    ~Fase_Primeira();

protected:
    void criarInimigos();
    void criarObstaculos();
};

}

#endif
