#ifndef SLIME_H
#define SLIME_H

#include "Entidades/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Personagens {

class Slime : public Inimigo {
private:
    sf::Texture textura;
    int frameAtual;
    float tempoAnimacao;
    int larguraFrame;
    int alturaFrame;

public:
    Slime(float x = 400.f, float y = 300.f);
    ~Slime();

    void executar(float dt);
    void salvar();
    void mover();
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;
};

}
}

#endif
