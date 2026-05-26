#ifndef GERENCIADOR_GRAFICO_H
#define GERENCIADOR_GRAFICO_H

#include <SFML/Graphics.hpp>

class Ente;

namespace Gerenciadores {

class Gerenciador_Grafico {
private:
    sf::RenderWindow janela;
    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;

public:
    Gerenciador_Grafico();
    ~Gerenciador_Grafico();

    sf::Vector2u getTamanhoJanela() const { 
        return janela.getSize();
    }//descobrir o tam da janela fora da classe, pra plataforma e etc
    void desenharEnte(Ente *pE);
    bool estaAberto();
    void processarEventos();
    void renderizar();
    void mostrar();
};

}

#endif