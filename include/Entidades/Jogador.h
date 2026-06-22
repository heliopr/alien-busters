#ifndef JOGADOR_H
#define JOGADOR_H

#include "Entidades/Personagem.h"
#include "Entidades/Atirador.h"
#include <SFML/Audio.hpp>
#include <string>

namespace AlienBusters {
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
    float knockbackVx;

    sf::SoundBuffer bufferDano;
    sf::Sound somDano;

    sf::SoundBuffer bufferMorte;
    sf::Sound somMorte;

    float processarMovimento(float dt);
    void atualizarSprite(float dt, float dx);

public:
    Jogador(float xInicial = 0.f, float yInicial = 0.f, bool eJogadorUm = true,
            const std::string& texturaSprite = "assets/textures/player.png");
    ~Jogador();

    void resetar();
    void restaurarEstado(int novosPontos, int novasVidas);
    void executar(float dt = 0.f);
    void salvar();
    void mover(float dt = 0);
    void colidir(Inimigo* pIn);

    sf::FloatRect getHitbox() const;
    void atirar();
    bool getOlhandoDireita() const;
    int getPontos() const;
    void adicionarPontos(int valor);
    void ficarLento(float duracao);
    void perderVida();
    void morrer();
    bool estaInvulneravel() const;
    void ativarInvulnerabilidade();
    void aplicarKnockback(float vx);
    int getNumVidas() const;
    bool estaMorto() const;
};

}
}
}

#endif
