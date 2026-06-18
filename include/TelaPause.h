#ifndef TELA_PAUSE_H
#define TELA_PAUSE_H

#include "Ente.h"
#include <vector>
#include <string>

namespace AlienBusters {

class TelaPause : public Ente {
private:
    int opcaoSelecionada;
    sf::Text titulo;
    std::vector<sf::Text> opcoes;
    sf::Font fonte;

public:
    enum Opcao {
        OPCAO_CONTINUAR = 0,
        OPCAO_REINICIAR,
        OPCAO_MENU
    };

    TelaPause();
    virtual ~TelaPause();

    void subirOpcao();
    void descerOpcao();
    void resetar();

    int getOpcaoSelecionada() const { return opcaoSelecionada; }

    void executar(float dt = 0.f);
    void desenhar();
};

}

#endif
