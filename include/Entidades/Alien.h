#ifndef ALIEN_H
#define ALIEN_H

#include "Entidades/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {

class Jogador;

class Alien : public Inimigo {
private:
    float raio;
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
    sf::FloatRect getLimitesColisao() const;
};

}

#endif
