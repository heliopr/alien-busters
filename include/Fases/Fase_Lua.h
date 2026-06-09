#ifndef FASE_LUA_H
#define FASE_LUA_H

#include "Fases/Fase.h"

namespace Fases {

class Fase_Lua : public Fase {
public:
    Fase_Lua();
    ~Fase_Lua();

protected:
    void criarInimigos();
    void criarObstaculos();
};

}

#endif
