#ifndef INIMIGO_H
#define INIMIGO_H

#include "Entidades/Personagem.h"

#include <SFML/Audio.hpp>

namespace AlienBusters {
namespace Entidades {

namespace Personagens {

class Jogador;

class Inimigo : public Personagem {
protected:
    int nivel_maldade;
    float velocidadeX;
    float tempoFlashDano;

    bool decidiuBorda;
    bool vaiCairDaBorda;

    static sf::SoundBuffer bufferDano;
    static sf::Sound somDano;
    static bool somCarregado;

    void atualizarFlashDano(float dt);
    bool podeDanificar(Jogador* p) const;

public:
    Inimigo();
    virtual ~Inimigo();

    virtual void executar(float dt = 0.f) = 0;
    virtual void salvar() = 0;
    void mover(float dt = 0);
    virtual void danificar(Jogador* p) = 0;
    virtual sf::FloatRect getHitbox() const = 0;

    virtual void atirar(Jogador*, float);
    virtual int pontosAoMorrer() const;

    float getVelocidadeX() const;
    void setVelocidadeX(float v);

    int getNivelMaldade() const;
    void setNivelMaldade(int n);

    bool deveCairDaBorda();
    void resetarDecisaoBorda();

    void levarDano();
    bool estaFlashando() const;
    int getNumVidas() const;
    void setNumVidas(int n);
    bool morreu() const;
};

}
}
}

#endif
