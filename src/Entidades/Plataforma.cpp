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

void Plataforma::obstaculizar(Jogador *p) {
    if (!p) return;

    float pEsq = p->getX() - 30.f;
    float pDir = p->getX() + 30.f;
    float pBaixo = p->getY() - 15.f;
    float pTopo = p->getY() - 100.f;

    float platEsq = x;
    float platDir = x + largura;
    float platTopo = y;
    float platBaixo = y + altura;

    if (pEsq < platDir && pDir > platEsq && pTopo < platBaixo && pBaixo > platTopo) {
        float overlapX = (p->getX() < x + largura / 2.f) ? (pDir - platEsq) : (platDir - pEsq);
        float overlapY = (p->getY() - 57.5f < y + altura / 2.f) ? (pBaixo - platTopo) : (platBaixo - pTopo);

        if (overlapX < overlapY) {
            if (p->getX() < x + largura / 2.f) {
                p->setX(platEsq - 30.f);
            } else {
                p->setX(platDir + 30.f);
            }
        } else {
            if (p->getY() - 57.5f < y + altura / 2.f) {
                p->setY(platTopo + 15.f);
                p->setVy(0.f);
                p->setNoChao(true);
            } else {
                p->setY(platBaixo + 100.f);
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