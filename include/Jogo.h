#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Pontuacoes.h"
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

    static Jogo* instancia;

    Fases::Fase* faseAtual;
    Entidades::Personagens::Jogador* pJog1;
    Entidades::Personagens::Jogador* pJog2;
    Menu menu;
    TelaMorte telaMorte;
    Estado estado;
    std::string nomeJogadorAtual;
    std::string nomeJogador2Atual;
    int faseSelecionada;

    Jogo();

public:
    ~Jogo();

    static Jogo* getInstancia();

    void executar();
    void setNomeJogador(const std::string& nome) { nomeJogadorAtual = nome; }
};

#endif