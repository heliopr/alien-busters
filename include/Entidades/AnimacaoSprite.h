#ifndef ANIMACAOSPRITE_H
#define ANIMACAOSPRITE_H

#include <SFML/Graphics.hpp>
#include <string>

namespace Entidades {

class AnimacaoSprite {
private:
    sf::Texture textura;
    int larguraFrame;
    int alturaFrame;
    int frameAtual;
    float tempoAnimacao;

public:
    AnimacaoSprite();

    bool carregar(const std::string &caminho, int colunas, int linhas, const std::string &mensagemErro);

    void atualizar(float dt, float tempoPorFrame, int numFrames);
    void aplicar(sf::RectangleShape *fig, int linha, bool espelhado) const;

    sf::Texture *getTextura();
    int getLarguraFrame() const;
    int getAlturaFrame() const;
    int getFrameAtual() const;
    void setFrameAtual(int frame);
};

}

#endif
