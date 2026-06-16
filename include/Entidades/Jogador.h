#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Personagem.h"
#include "Entidades/AnimacaoSprite.h"
#include <SFML/Audio.hpp>

namespace Entidades {
namespace Personagens {

class Inimigo;

struct ControlesJogador {
    sf::Keyboard::Key esquerda;
    sf::Keyboard::Key direita;
    sf::Keyboard::Key pulo;
    sf::Keyboard::Key tiro;

    ControlesJogador(sf::Keyboard::Key esq, sf::Keyboard::Key dir,
                     sf::Keyboard::Key pul, sf::Keyboard::Key tir)
        : esquerda(esq), direita(dir), pulo(pul), tiro(tir) {}
};

class Jogador : public Personagem {
protected:
    int pontos;
private:
    AnimacaoSprite animacao;

    ControlesJogador controles;
    float xInicial;
    float yInicial;
    sf::Color cor;

    float ultimoDx;
    bool olhandoDireita;
    bool puloPressionado;
    bool tiroPressionado;
    float tempoRecargaTiro;

    bool lento;
    float tempoLento;

    bool invulneravel;
    float tempoInvulneravel;
    float tempoFlashDano;

    sf::SoundBuffer bufferDano;
    sf::Sound somDano;

    float processarMovimento(float dt);
    void atualizarSprite(float dt, float dx);

public:
    Jogador(float xInicial, float yInicial, const ControlesJogador& controles,
            const sf::Color& cor = sf::Color::White);
    ~Jogador();

    void resetar();
    void executar(float dt);
    void salvar();
    void mover(float dt = 0);
    void colidir(Inimigo* pIn);

    sf::FloatRect getHitbox() const;
    bool getAtirou();
    bool getOlhandoDireita() const { return olhandoDireita; }
    int getPontos() const { return pontos; }
    void adicionarPontos(int valor) { pontos += valor; }
    void ficarLento(float duracao);
    void perderVida();
    void morrer();
    bool estaInvulneravel() const { return invulneravel; }
    void ativarInvulnerabilidade();
    int getNumVidas() const { return num_vidas; }
    bool estaMorto() const { return num_vidas <= 0; }
};

}
}

#endif
