#include "Entidades/Plataforma.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Ente.h"
#include "Entidades/Jogador.h"

namespace Entidades {

Plataforma::Plataforma(float x, float y, float largura, float altura) 
    : Obstaculo(), altura(altura), largura(largura) {
    this->x = x;
    this->y = y;

    pFig = new sf::RectangleShape(sf::Vector2f(largura, altura));
    pFig->setPosition(sf::Vector2f(x, y));
    pFig->setFillColor(sf::Color::Green);
}

Plataforma::~Plataforma() {}

void Plataforma::executar(float ) {
}

sf::FloatRect Plataforma::getLimitesColisao() const {
    return sf::FloatRect(x, y, largura, altura);
}

void Plataforma::obstaculizar(Jogador *p) {
    if (!p) return;

    sf::FloatRect boxPlat = getLimitesColisao();
    sf::FloatRect boxPlayer = p->getLimitesColisao();
    sf::FloatRect interseccao;

    if (boxPlayer.intersects(boxPlat, interseccao)) {
        if (interseccao.width < interseccao.height) {
            // colisão lateral
            if (boxPlayer.left + boxPlayer.width / 2.f < boxPlat.left + boxPlat.width / 2.f) {
                // empurra para a esquerda
                p->setX(boxPlat.left - 30.f); 
            } else {
                // empurra para a direita
                p->setX(boxPlat.left + boxPlat.width + 30.f); 
            }
        } else {
            // colisão vertical
            if (boxPlayer.top + boxPlayer.height / 2.f < boxPlat.top + boxPlat.height / 2.f) {
                // pousando em cima da plataforma
                p->setY(boxPlat.top + 15.f);
                p->setVy(0.f);
                p->setNoChao(true);
            } else {
                // batendo embaixo da plataforma
                p->setY(boxPlat.top + boxPlat.height + 100.f);
                if (p->getVy() < 0.f) {
                    p->setVy(0.f);
                }
            }
        }
    }
}

void Plataforma::salvar() {   
}

}  