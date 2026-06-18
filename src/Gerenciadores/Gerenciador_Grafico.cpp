#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"
#include <iostream>
#include <sstream>

namespace AlienBusters {
namespace Gerenciadores {

Gerenciador_Grafico* Gerenciador_Grafico::instancia = 0;

Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() {
    if (instancia == 0) {
        instancia = new Gerenciador_Grafico();
    }
    return instancia;
}

Gerenciador_Grafico::Gerenciador_Grafico() :
    janela(sf::VideoMode(1280, 720), "Alien Busters", sf::Style::Titlebar | sf::Style::Close),
    camera(sf::FloatRect(0.f, 0.f, 1422.222f, 800.f)),
    mostrarHitboxes(false) {
    janela.setFramerateLimit(60);
    janela.setView(camera);

    if (!texturaFundo.loadFromFile("assets/textures/lua.png")) {
        std::cout << "Erro: Nao foi possivel carregar assets/textures/lua.png" << std::endl;
    } else {
        spriteFundo.setTexture(texturaFundo);

        float scaleX = 1422.222f / texturaFundo.getSize().x;
        float scaleY = 800.f / texturaFundo.getSize().y;
        spriteFundo.setScale(scaleX, scaleY);
    }

    if (!fontHUD.loadFromFile("assets/fonts/PixelifySans-Regular.ttf")) {
        std::cerr << "Erro: Nao foi possivel carregar a fonte HUD" << std::endl;
    }
    textoHUD.setFont(fontHUD);
    textoHUD.setCharacterSize(32);
    textoHUD.setFillColor(sf::Color::White);
    textoHUD.setString("Pontos: 0");
    textoHUD.setPosition(20.f, 16.f);

    textoDebug.setFont(fontHUD);
    textoDebug.setCharacterSize(26);
    textoDebug.setFillColor(sf::Color::White);
    textoDebug.setString("X: 0  Y: 0");
    textoDebug.setPosition(20.f, 56.f);

    if (!texturaCoracao.loadFromFile("assets/textures/heart.png")) {
        std::cerr << "Erro: Nao foi possivel carregar a textura do coracao" << std::endl;
    } else {
        spriteCoracao.setTexture(texturaCoracao);
        float escala = 54.f / texturaCoracao.getSize().x;
        spriteCoracao.setScale(escala, escala);
    }
}

Gerenciador_Grafico::~Gerenciador_Grafico() {}

void Gerenciador_Grafico::desenharEnte(Ente *pE) {
    if (pE) {
        sf::RectangleShape *fig = pE->getFigura();
        if (fig) {
            janela.draw(*fig);
        }
    }
}

void Gerenciador_Grafico::desenharTexto(sf::Text *pT) {
    if (pT != 0) {
        janela.draw(*pT);
    }
}

void Gerenciador_Grafico::desenharTextoTela(sf::Text *pT) {
    if (pT != 0) {
        sf::View viewAnterior = janela.getView();
        sf::View viewTela(sf::FloatRect(0.f, 0.f, 1422.222f, 800.f));

        janela.setView(viewTela);
        janela.draw(*pT);
        janela.setView(viewAnterior);
    }
}

void Gerenciador_Grafico::desenharSpriteTela(sf::Sprite *pS) {
    if (pS != 0) {
        sf::View viewAnterior = janela.getView();
        sf::View viewTela(sf::FloatRect(0.f, 0.f, 1422.222f, 800.f));

        janela.setView(viewTela);
        janela.draw(*pS);
        janela.setView(viewAnterior);
    }
}

void Gerenciador_Grafico::desenharTelaEscura() {
    sf::View viewAnterior = janela.getView();
    sf::View viewTela(sf::FloatRect(0.f, 0.f, 1422.222f, 800.f));

    sf::RectangleShape shape(sf::Vector2f(1422.222f, 800.f));
    shape.setPosition(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(sf::Color(0, 0, 0, 180));

    janela.setView(viewTela);
    janela.draw(shape);
    janela.setView(viewAnterior);
}

void Gerenciador_Grafico::desenharRetangulo(sf::FloatRect rect, sf::Color corContorno, float espessuraContorno) {
    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(corContorno);
    shape.setOutlineThickness(espessuraContorno);
    janela.draw(shape);
}

void Gerenciador_Grafico::desenharHUD(int pontos, float posX, float posY, int vidas, bool ladoDireito, bool mostrarDebug) {
    const float larguraTela = 1422.222f;
    const float margem = 20.f;

    std::ostringstream ss;
    ss << "Pontos: " << pontos;
    textoHUD.setString(ss.str());

    sf::View viewHUD(sf::FloatRect(0.f, 0.f, larguraTela, 800.f));
    janela.setView(viewHUD);

    if (!ladoDireito) {
        textoHUD.setPosition(margem, 16.f);
    } else {
        float largura = textoHUD.getLocalBounds().width;
        textoHUD.setPosition(larguraTela - margem - largura, 16.f);
    }
    janela.draw(textoHUD);

    if (mostrarDebug) {
        std::ostringstream ssDebug;
        ssDebug << "X: " << static_cast<int>(posX) << "  Y: " << static_cast<int>(posY);
        textoDebug.setString(ssDebug.str());
        textoDebug.setPosition(margem, 56.f);
        janela.draw(textoDebug);
    }

    if (texturaCoracao.getSize().x > 0) {
        const float tamanhoCoracao = 54.f;
        const float espacamento = 8.f;
        float baseY = 800.f - margem - tamanhoCoracao;

        for (int i = 0; i < vidas; ++i) {
            float posXCoracao;
            if (!ladoDireito) {
                posXCoracao = margem + i * (tamanhoCoracao + espacamento);
            } else {
                posXCoracao = larguraTela - margem - tamanhoCoracao - i * (tamanhoCoracao + espacamento);
            }
            spriteCoracao.setPosition(posXCoracao, baseY);
            janela.draw(spriteCoracao);
        }
    }

    janela.setView(camera);
}

bool Gerenciador_Grafico::estaAberto() {
    return janela.isOpen();
}

bool Gerenciador_Grafico::coletarEventos(sf::Event &evento) {
    return janela.pollEvent(evento);
}

void Gerenciador_Grafico::fecharJanela() {
    janela.close();
}
void Gerenciador_Grafico::processarEventos() {
    sf::Event evento;
    while (janela.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            janela.close();
        }
    }
}

void Gerenciador_Grafico::renderizar() {
    janela.clear(sf::Color::Black);
    
    if (texturaFundo.getSize().x > 0) {
        sf::View viewFundo = camera;
        viewFundo.setCenter(711.111f, 400.f);
        
        janela.setView(viewFundo);
        janela.draw(spriteFundo); 
    } 
    else {
        janela.setView(camera);
        sf::RectangleShape areaInterna(sf::Vector2f(1422.222f, 800.f));
        areaInterna.setFillColor(sf::Color(40, 40, 40));
        janela.draw(areaInterna);
    }

    janela.setView(camera);
}

void Gerenciador_Grafico::mostrar() {
    janela.display();
}

void Gerenciador_Grafico::atualizarCamera(sf::Vector2f posicaoJogador) {
    float posX = posicaoJogador.x;
    float metadeLargura = camera.getSize().x / 2.f;
    // impede que a camera exiba áreas a esquerda do mapa
    if (posX < metadeLargura) {
        posX = metadeLargura;
    }
    camera.setCenter(posX, 400.f);
    janela.setView(camera);
}

}
}