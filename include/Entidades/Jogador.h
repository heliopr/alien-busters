#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Entidade.h"

namespace Entidades {

class Jogador : public Entidade { 
private:
    sf::Texture texturaJogador;
    int linhaAtual;
    int frameAtual;
    float tempoAnimacao;
    int larguraFrame;
    int alturaFrame;

    float vy;               
    bool noChao;            
    bool agachado;          
    bool olhandoEsquerda;   
    bool olhandoDireita; 

public:
    Jogador();
    ~Jogador();

    void executar(float dt);
    void salvar();

    float getVy() const { return vy; }
    void setVy(float v) { vy = v; }
    bool getNoChao() const { return noChao; }
    void setNoChao(bool b) { noChao = b; }
};

}

#endif
