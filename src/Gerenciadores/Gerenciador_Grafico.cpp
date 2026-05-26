#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"
#include <iostream> 

namespace Gerenciadores {

Gerenciador_Grafico::Gerenciador_Grafico() :
    janela(sf::VideoMode(1280, 720), "Janela SFML"),
    camera(sf::FloatRect(0.f, 0.f, 1422.222f, 800.f)) {
    janela.setFramerateLimit(60);
    janela.setView(camera);

    if (!texturaFundo.loadFromFile("assets/textures/marte.png")) {
        std::cout << "Erro: Nao foi possivel carregar assets/textures/marte.png" << std::endl;
    } else {
        spriteFundo.setTexture(texturaFundo);

        float scaleX = 1422.222f / texturaFundo.getSize().x;
        float scaleY = 800.f / texturaFundo.getSize().y;
        spriteFundo.setScale(scaleX, scaleY);
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

bool Gerenciador_Grafico::estaAberto() {
    return janela.isOpen();
}

void Gerenciador_Grafico::processarEventos() {
    sf::Event evento;
    while (janela.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            janela.close();
        }
        if (evento.type == sf::Event::Resized) {
            float windowWidth = static_cast<float>(evento.size.width);
            float windowHeight = static_cast<float>(evento.size.height);
            
            float targetRatio = 16.f / 9.f; // aspect ratio16:9
            float windowRatio = windowWidth / windowHeight;
            
            float viewportWidth = 1.f;
            float viewportHeight = 1.f;
            float viewportX = 0.f;
            float viewportY = 0.f;

            // serve para manter o aspect ratio da tela
            if (windowRatio > targetRatio) {
                // barras pretas nas laterais
                viewportWidth = targetRatio / windowRatio;
                viewportX = (1.f - viewportWidth) / 2.f;
            } else {
                // barras pretas no topo
                viewportHeight = windowRatio / targetRatio;
                viewportY = (1.f - viewportHeight) / 2.f;
            }
            
            camera.setViewport(sf::FloatRect(viewportX, viewportY, viewportWidth, viewportHeight));
            janela.setView(camera);
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