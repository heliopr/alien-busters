#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Fases/Fase_Lua.h"
#include "Fases/Fase_Marte.h"
#include "Menu.h"

class Jogo {
private:
    Gerenciadores::Gerenciador_Grafico GG;
    Fases::Fase* faseAtual;
    Entidades::Personagens::Jogador* pJog1;
    Menu menu; 
    bool noMenu;

public:
    Jogo();
    ~Jogo();
    void executar();
};

#endif