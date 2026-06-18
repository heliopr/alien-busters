#ifndef EXPLOSAO_H
#define EXPLOSAO_H

#include "Entidades/Entidade.h"
#include <SFML/Audio.hpp>

namespace AlienBusters {
namespace Entidades {

class Explosao : public Entidade {
private:
    sf::Texture textura;
    sf::SoundBuffer bufferExplosao;
    sf::Sound somExplosao;
    int frameAtual;
    float tempoAnimacao;
    int larguraFrame;
    int alturaFrame;
    bool terminada;

    static const int NUM_FRAMES;
    static const float TEMPO_FRAME;

public:
    Explosao(float x, float y);
    ~Explosao();

    void executar(float dt);
    void salvar();
    sf::FloatRect getHitbox() const;

    bool finalizada() const { return terminada; }
};

}
}

#endif
