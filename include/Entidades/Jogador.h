#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Personagem.h"
#include "Entidades/Atirador.h"
#include <SFML/Audio.hpp>
#include <string>

namespace Entidades {

namespace Personagens {

class Inimigo;

class Jogador : public Personagem, public Atirador {
protected:
    int pontos;
private:
    bool eJogadorUm;
    float xInicial;
    float yInicial;

    float ultimoDx;
    bool olhandoDireita;
    bool puloPressionado;
    bool tiroPressionado;

    float tempoLento;
    float tempoInvulneravel;
    float tempoFlashDano;

    sf::SoundBuffer bufferDano;
    sf::Sound somDano;

    sf::SoundBuffer bufferMorte;
    sf::Sound somMorte;

    float processarMovimento(float dt);
    void atualizarSprite(float dt, float dx);

public:
    Jogador(float xInicial, float yInicial, bool eJogadorUm,
            const std::string& texturaSprite = "assets/textures/player.png");
    ~Jogador();

    void resetar();
    void executar(float dt);
    void salvar();
    void mover(float dt = 0);
    void colidir(Inimigo* pIn);

    sf::FloatRect getHitbox() const;
    void atirar();
    bool getOlhandoDireita() const { return olhandoDireita; }
    int getPontos() const { return pontos; }
    void adicionarPontos(int valor) { pontos += valor; }
    void ficarLento(float duracao);
    void perderVida();
    void morrer();
    bool estaInvulneravel() const { return tempoInvulneravel > 0.f; }
    void ativarInvulnerabilidade();
    int getNumVidas() const { return num_vidas; }
    bool estaMorto() const { return num_vidas <= 0; }
};

}
}

#endif
