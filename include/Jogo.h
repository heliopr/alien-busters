#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Fases/Fase_Primeira.h"
#include "Menu.h"

class Jogo {
private:
    Gerenciadores::Gerenciador_Grafico GG;
    Fases::Fase* faseAtual;
    Entidades::Jogador* pJog1;
    Menu menu; 
    bool noMenu;

public:
    Jogo();
    ~Jogo();
    void executar();
};

#endif