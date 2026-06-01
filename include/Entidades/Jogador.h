#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Personagem.h"

namespace Entidades {

class Jogador : public Personagem { 
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

public:
    Jogador();
    ~Jogador();

    void executar(float dt);
    void salvar();
    void mover();

    sf::FloatRect getLimitesColisao() const;
};

}

#endif