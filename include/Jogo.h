#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Listas/ListaEntidades.h"
#include "Entidades/Jogador.h"

class Jogo {
private:
    Gerenciadores::Gerenciador_Grafico GG;
    Gerenciadores::Gerenciador_Colisoes gerenciadorColisoes;
    Listas::ListaEntidades lista_entidades;
    Entidades::Jogador* pJogador;

public:
    Jogo();
    ~Jogo();
    void executar();
};

#endif