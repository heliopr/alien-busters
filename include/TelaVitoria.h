#ifndef TELA_VITORIA_H
#define TELA_VITORIA_H

#include "Ente.h"
#include <vector>
#include <string>
#include <SFML/Audio.hpp>

namespace AlienBusters {

class TelaVitoria : public Ente {
private:
    int opcaoSelecionada;
    sf::Text titulo;
    std::vector<sf::Text> opcoes;
    sf::Font fonte;

    sf::SoundBuffer bufferVitoria;
    sf::Sound somVitoria;

public:
    TelaVitoria();
    virtual ~TelaVitoria();

    void subirOpcao();
    void descerOpcao();
    void resetar();

    int getOpcaoSelecionada() const { return opcaoSelecionada; }

    void executar(float dt = 0.f);
    void desenhar();

    void tocarVitoria();
};

}

#endif
