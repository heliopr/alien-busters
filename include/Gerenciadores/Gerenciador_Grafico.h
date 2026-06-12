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
    sf::Texture texturaCoracao;
    sf::Sprite spriteCoracao;
    sf::View camera;
    bool mostrarHitboxes;
    sf::Font fontHUD;
    sf::Text textoHUD;
    sf::Text textoDebug;

public:
    Gerenciador_Grafico();
    ~Gerenciador_Grafico();

    // descobrir o tam da janela fora da classe, pra plataforma e etc
    sf::Vector2u getTamanhoJanela() const { 
        return janela.getSize();
    }
    bool getMostrarHitboxes() const { return mostrarHitboxes; }
    void setMostrarHitboxes(bool b) { mostrarHitboxes = b; }
    void desenharEnte(Ente *pE);
    void desenharTexto(sf::Text *pT);
    void desenharTextoTela(sf::Text *pT);
    void desenharRetangulo(sf::FloatRect rect, sf::Color corContorno, float espessuraContorno);
    bool estaAberto();
    bool coletarEventos(sf::Event &evento);
    void fecharJanela();
    void processarEventos();
    void renderizar();
    void mostrar();
    void atualizarCamera(sf::Vector2f posicaoJogador);
    void desenharHUD(int pontos, float posX, float posY, int vidas, bool ladoDireito = false, bool mostrarDebug = true);
};

}

#endif