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
    int numJogadores;
    bool emSubmenu;
    std::vector<sf::Text> opcoes;
    std::vector<sf::Text> opcoesFases;
    sf::Font fonte;
    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;

    void criarTextos(std::vector<sf::Text>& lista, std::string nomes[], int total, float yInicio);
    void atualizarTextoJogadores();

public:
    Menu(Jogo* pJ = 0);
    virtual ~Menu();

    void subirOpcao();
    void descerOpcao();
    void entrarSubmenu();
    void sairSubmenu();
    void alternarJogadores();

    bool getEmSubmenu() const { return emSubmenu; }
    int getOpcaoSelecionada() const { return opcaoSelecionada; }
    int getOpcaoFaseSelecionada() const { return opcaoFaseSelecionada; }
    int getNumJogadores() const { return numJogadores; }

    void executar(float dt = 0.f);
    void desenhar();
};

#endif
