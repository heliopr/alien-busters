#ifndef MENU_H
#define MENU_H

#include "Ente.h"
#include <vector>
#include <string>

class Jogo; 

class Menu : public Ente {
private:
    Jogo* pJog;
    int opcaoSelecionada;
    std::vector<sf::Text> opcoes;
    sf::Font fonte;

public:
    Menu(Jogo* pJ = 0);
    virtual ~Menu();

    void subirOpcao();
    void descerOpcao();
    int getOpcaoSelecionada() const { return opcaoSelecionada; }

    void executar(float dt = 0.f);
    void desenhar();
};

#endif