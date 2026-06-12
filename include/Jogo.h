#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Fases/Fase_Lua.h"
#include "Fases/Fase_Marte.h"
#include "Menu.h"
#include "TelaMorte.h"

class Jogo {
private:
    enum Estado {
        ESTADO_MENU,
        ESTADO_JOGANDO,
        ESTADO_TELA_MORTE
    };

    Gerenciadores::Gerenciador_Grafico GG;
    Fases::Fase* faseAtual;
    Entidades::Personagens::Jogador* pJog1;
    Entidades::Personagens::Jogador* pJog2;
    Menu menu;
    TelaMorte telaMorte;
    Estado estado;

public:
    Jogo();
    ~Jogo();
    void executar();
};

#endif