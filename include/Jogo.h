#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Listas/ListaEntidades.h"
#include "Entidades/Jogador.h"

class Jogo {
private:
    Gerenciadores::Gerenciador_Grafico GG;
    Listas::ListaEntidades lista_entidades;
    Entidades::Jogador* pJogador;

public:
    Jogo();
    ~Jogo();

    void executar();
};

#endif