#ifndef INIMIGO_FACIL_H
#define INIMIGO_FACIL_H

#include "Entidades/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace Entidades {

class Jogador;

class Inimigo_Facil : public Inimigo {
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
    Inimigo_Facil(float x = 400.f, float y = 300.f);
    ~Inimigo_Facil();

    void executar(float dt);
    void salvar();
    void mover();
    void danificar(Jogador* p);
    sf::FloatRect getLimitesColisao() const;
};

}

#endif
