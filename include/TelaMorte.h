#ifndef TELA_MORTE_H
#define TELA_MORTE_H

#include "Ente.h"
#include <vector>
#include <string>

class TelaMorte : public Ente {
private:
    int opcaoSelecionada;
    sf::Text titulo;
    std::vector<sf::Text> opcoes;
    sf::Font fonte;

public:
    TelaMorte();
    virtual ~TelaMorte();

    void subirOpcao();
    void descerOpcao();
    void resetar();

    int getOpcaoSelecionada() const { return opcaoSelecionada; }

    void executar(float dt = 0.f);
    void desenhar();
};

#endif
