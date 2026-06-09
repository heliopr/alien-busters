#ifndef ALIEN_H
#define ALIEN_H

#include "Entidades/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {
namespace Personagens {

class Alien : public Inimigo {
private:
    float velocidade;
    sf::Texture texturaInimigo;
    int linhaAtual;
    int frameAtual;
    float tempoAnimacao;
    int larguraFrame;
    int alturaFrame;
    bool olhandoEsquerda;
    bool olhandoDireita;

public:
    Alien(float x = 400.f, float y = 300.f);
    ~Alien();

    void executar(float dt);
    void salvar();
    void mover();
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;
};

} // namespace Personagens
} // namespace Entidades

#endif
