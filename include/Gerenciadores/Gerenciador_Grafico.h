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
    sf::View camera;

public:
    Gerenciador_Grafico();
    ~Gerenciador_Grafico();

    // descobrir o tam da janela fora da classe, pra plataforma e etc
    sf::Vector2u getTamanhoJanela() const { 
        return janela.getSize();
    }
    void desenharEnte(Ente *pE);
    bool estaAberto();
    void processarEventos();
    void renderizar();
    void mostrar();
    void atualizarCamera(sf::Vector2f posicaoJogador);
};

}

#endif