#include "Entidades/AnimacaoSprite.h"
#include <iostream>
#include <cstddef>

namespace Entidades {

AnimacaoSprite::AnimacaoSprite()
    : larguraFrame(0), alturaFrame(0), frameAtual(0), tempoAnimacao(0.f) {
}

bool AnimacaoSprite::carregar(const std::string &caminho, int colunas, int linhas, const std::string &mensagemErro) {
    if (!textura.loadFromFile(caminho)) {
        std::cerr << mensagemErro << std::endl;
        return false;
    }

    larguraFrame = static_cast<int>(textura.getSize().x) / colunas;
    alturaFrame = static_cast<int>(textura.getSize().y) / linhas;

    sf::Image imagemBranca = textura.copyToImage();
    sf::Vector2u tamanho = imagemBranca.getSize();
    for (unsigned int j = 0; j < tamanho.y; ++j) {
        for (unsigned int i = 0; i < tamanho.x; ++i) {
            sf::Color pixel = imagemBranca.getPixel(i, j);
            if (pixel.a > 0) {
                imagemBranca.setPixel(i, j, sf::Color(255, 255, 255, pixel.a));
            }
        }
    }
    texturaBranca.loadFromImage(imagemBranca);

    return true;
}

void AnimacaoSprite::atualizar(float dt, float tempoPorFrame, int numFrames) {
    tempoAnimacao += dt;
    if (tempoAnimacao >= tempoPorFrame) {
        tempoAnimacao = 0.f;
        frameAtual = (frameAtual + 1) % numFrames;
    }
}

void AnimacaoSprite::aplicar(sf::RectangleShape *fig, int linha, bool espelhado) const {
    if (fig == NULL) return;

    if (espelhado) {
        fig->setTextureRect(sf::IntRect((frameAtual + 1) * larguraFrame, linha * alturaFrame, -larguraFrame, alturaFrame));
    } else {
        fig->setTextureRect(sf::IntRect(frameAtual * larguraFrame, linha * alturaFrame, larguraFrame, alturaFrame));
    }
}

sf::Texture *AnimacaoSprite::getTextura() {
    return &textura;
}

sf::Texture *AnimacaoSprite::getTexturaBranca() {
    return &texturaBranca;
}

int AnimacaoSprite::getLarguraFrame() const {
    return larguraFrame;
}

int AnimacaoSprite::getAlturaFrame() const {
    return alturaFrame;
}

int AnimacaoSprite::getFrameAtual() const {
    return frameAtual;
}

void AnimacaoSprite::setFrameAtual(int frame) {
    frameAtual = frame;
}

}
