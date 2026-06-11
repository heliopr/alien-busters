#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Personagem.h"
#include "Entidades/AnimacaoSprite.h"

namespace Entidades {
namespace Personagens {

class Inimigo;

class Jogador : public Personagem {
protected:
    int pontos;
private:
    AnimacaoSprite animacao;

    bool olhandoEsquerda;
    bool olhandoDireita;
    bool puloPressionado;
    bool tiroPressionado;

    bool lento;
    float tempoLento;

    bool invulneravel;
    float tempoInvulneravel;
    float tempoFlashDano;

public:
    Jogador();
    ~Jogador();

    void executar(float dt);
    void salvar();
    void mover();
    void colidir(Inimigo* pIn);

    sf::FloatRect getHitbox() const;
    bool getAtirou();
    bool getOlhandoDireita() const { return olhandoDireita; }
    int getPontos() const { return pontos; }
    void adicionarPontos(int valor) { pontos += valor; }
    void ficarLento(float duracao);
    void perderVida();
    bool estaInvulneravel() const { return invulneravel; }
    void ativarInvulnerabilidade();
    int getNumVidas() const { return num_vidas; }
};

}
}

#endif
