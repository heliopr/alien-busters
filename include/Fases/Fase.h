#ifndef FASE_H
#define FASE_H

#include "Ente.h"
#include "Listas/ListaEntidades.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Jogador.h"

namespace Fases {

class Fase : public Ente {
protected:
    Listas::ListaEntidades lista_ents;
    Gerenciadores::Gerenciador_Colisoes GC;
    Entidades::Jogador* pJogador;

public:
    Fase();
    virtual ~Fase();

    virtual void executar(float dt);
    virtual void desenhar();

protected:
    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;
    void criarCenario();
};

}

#endif
