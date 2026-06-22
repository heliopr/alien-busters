#ifndef TELA_MORTE_H
#define TELA_MORTE_H

#include "Ente.h"
#include <vector>
#include <string>
#include <SFML/Audio.hpp>

namespace AlienBusters {

class TelaMorte : public Ente {
private:
    int opcaoSelecionada;
    sf::Text titulo;
    std::vector<sf::Text> opcoes;
    sf::Font fonte;

    sf::SoundBuffer bufferGameOver;
    sf::Sound somGameOver;

public:
    TelaMorte();
    virtual ~TelaMorte();

    void subirOpcao();
    void descerOpcao();
    void resetar();

    int getOpcaoSelecionada() const;

    void executar(float dt = 0.f);
    void desenhar();
    
    void tocarGameOver();
};

}

#endif
