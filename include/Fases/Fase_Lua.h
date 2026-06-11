#ifndef FASE_LUA_H
#define FASE_LUA_H

#include "Fases/Fase.h"

namespace Fases {

class Fase_Lua : public Fase {
public:
    Fase_Lua(Entidades::Personagens::Jogador* pJogador);
    ~Fase_Lua();

protected:
    void criarCenario();
    void criarInimigos();
    void criarObstaculos();
    void criarAliens();
    void criarGosmas();
    void criarSlimes();
};

}

#endif
