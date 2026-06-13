#ifndef FASE_LUA_H
#define FASE_LUA_H

#include "Fases/Fase.h"

namespace Fases {

class Fase_Lua : public Fase {
public:
    Fase_Lua(Entidades::Personagens::Jogador* pJogador,
             Entidades::Personagens::Jogador* pJogador2 = 0);
    ~Fase_Lua();

protected:
    void criarCenario();
    void criarInimigos();
    void criarObstaculos();
    void criarAliens();
    void criarGosmas();
    void criarSlimes();
    void criarFoguete();
};

}

#endif
