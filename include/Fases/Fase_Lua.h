#ifndef FASE_LUA_H
#define FASE_LUA_H

#include "Fases/Fase.h"
#include <string>

namespace Fases {

class Fase_Lua : public Fase {
private:
    const int maxAliens;
    const int maxSlimes;
    const int maxGosmas;

public:
    Fase_Lua(Entidades::Personagens::Jogador* pJogador,
             Entidades::Personagens::Jogador* pJogador2 = 0,
             const std::string& nome1 = "", const std::string& nome2 = "");
    ~Fase_Lua();

protected:
    void criarCenario();
    void criarInimigos();
    void criarObstaculos();
    void criarFoguete();
    void criarAliens();
    void criarGosmas();
    void criarSlimes();
};

}

#endif
