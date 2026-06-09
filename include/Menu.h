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
    int opcaoFaseSelecionada;
    bool emSubmenu;
    std::vector<sf::Text> opcoes;
    std::vector<sf::Text> opcoesFases;
    sf::Font fonte;

    void criarTextos(std::vector<sf::Text>& lista, std::string nomes[], int total, float yInicio);

public:
    Menu(Jogo* pJ = 0);
    virtual ~Menu();

    void subirOpcao();
    void descerOpcao();
    void entrarSubmenu();
    void sairSubmenu();

    bool getEmSubmenu() const { return emSubmenu; }
    int getOpcaoSelecionada() const { return opcaoSelecionada; }
    int getOpcaoFaseSelecionada() const { return opcaoFaseSelecionada; }

    void executar(float dt = 0.f);
    void desenhar();
};

#endif
