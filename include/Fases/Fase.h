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
    Entidades::Personagens::Jogador* pJogador;
    Entidades::Personagens::Jogador* pJogador2;

public:
    Fase(Entidades::Personagens::Jogador* pJogador,
         Entidades::Personagens::Jogador* pJogador2 = 0);
    virtual ~Fase();

    virtual void executar(float dt);
    virtual void desenhar();
    virtual void reiniciar();
    bool jogadorPerdeu() const;

protected:
    void processarJogador(Entidades::Personagens::Jogador* pJog, float dt);
    void atualizarCamera();
    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;
    virtual void criarCenario();
    void criarCenario(const sf::Color& cor);
    virtual void criarSlimes() = 0;
};

}

#endif
