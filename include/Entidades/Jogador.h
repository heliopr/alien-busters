#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Personagem.h"

namespace Entidades {
class Inimigo;

class Jogador : public Personagem { 
protected:
    int pontos;
private:
    sf::Texture texturaJogador;
    int linhaAtual;
    int frameAtual;
    float tempoAnimacao;
    int larguraFrame;
    int alturaFrame;

    bool agachado;          
    bool olhandoEsquerda;   
    bool olhandoDireita; 
    bool puloPressionado;
    bool tiroPressionado;

    bool lento;
    float tempoLento;

public:
    Jogador();
    ~Jogador();

    void executar(float dt);
    void salvar();
    void mover();
    void colidir(Inimigo* pIn);

    sf::FloatRect getLimitesColisao() const;
    bool getAtirou();
    bool getOlhandoDireita() const { return olhandoDireita; }
    void ficarLento(float duracao);
};

}

#endif