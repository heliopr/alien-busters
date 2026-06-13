#ifndef INIMIGO_H
#define INIMIGO_H

#include "Entidades/Personagem.h"

#include <SFML/Audio.hpp>

namespace Entidades {
namespace Personagens {

class Jogador;

class Inimigo : public Personagem {
protected:
    int nivel_maldade;
    float velocidadeX;
    float tempoFlashDano;

    static sf::SoundBuffer bufferDano;
    static sf::Sound somDano;
    static bool somCarregado;

    void moverComGravidade(float dt);
    void atualizarFlashDano(float dt);

public:
    Inimigo();
    virtual ~Inimigo();

    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void danificar(Jogador* p);
    virtual sf::FloatRect getHitbox() const = 0;

    float getVelocidadeX() const { return velocidadeX; }
    void setVelocidadeX(float v) { velocidadeX = v; }

    void levarDano();
    bool estaFlashando() const { return tempoFlashDano > 0.f; }
    int getNumVidas() const { return num_vidas; }
    bool morreu() const { return num_vidas <= 0; }
};

}
}

#endif
