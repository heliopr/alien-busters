#ifndef FASE_MARTE_H
#define FASE_MARTE_H

#include "Fases/Fase.h"

namespace Fases {

class Fase_Marte : public Fase {
public:
    Fase_Marte();
    ~Fase_Marte();

protected:
    void criarInimigos();
    void criarObstaculos();
    void criarAliens();
    void criarSlimes();
    void criarGosmas();
};

}

#endif
