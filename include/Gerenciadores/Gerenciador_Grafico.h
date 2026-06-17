#ifndef GERENCIADOR_GRAFICO_H
#define GERENCIADOR_GRAFICO_H

#include <SFML/Graphics.hpp>

class Ente;

namespace Gerenciadores {

class Gerenciador_Grafico {
private:
    static Gerenciador_Grafico* instancia;

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

    Gerenciador_Grafico();

public:
    ~Gerenciador_Grafico();

    static Gerenciador_Grafico* getInstancia();

    // descobrir o tam da janela fora da classe, pra plataforma e etc
    sf::Vector2u getTamanhoJanela() const { 
        return janela.getSize();
    }
    bool getMostrarHitboxes() const { return mostrarHitboxes; }
    void setMostrarHitboxes(bool b) { mostrarHitboxes = b; }
    const sf::Font& getFont() const { return fontHUD; }
    void desenharEnte(Ente *pE);
    void desenharTexto(sf::Text *pT);
    void desenharTextoTela(sf::Text *pT);
    void desenharSpriteTela(sf::Sprite *pS);
    void desenharRetangulo(sf::FloatRect rect, sf::Color corContorno, float espessuraContorno);
    void desenharTelaEscura();
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