#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Entidade.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"
#include "Entidades/Chao.h"
#include <cstddef>

namespace Gerenciadores {

Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(NULL) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    LOs.clear();
    LChaos.clear();
}

void Gerenciador_Colisoes::setJogador(Entidades::Jogador* pJ) {
    pJog1 = pJ;
}

void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculo* po) {
    if (po != NULL) {
        LOs.push_back(po);
    }
}

void Gerenciador_Colisoes::incluirChao(Entidades::Chao* pc) {
    if (pc != NULL) {
        LChaos.push_back(pc);
    }
}

const bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
    if (pe1 == NULL || pe2 == NULL) return false;

    sf::FloatRect box1 = pe1->getLimitesColisao();
    sf::FloatRect box2 = pe2->getLimitesColisao();

    return box1.intersects(box2);
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
    if (pJog1 == NULL) return;
    
    sf::FloatRect boxPlayer = pJog1->getLimitesColisao();

    for (std::list<Entidades::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Entidades::Obstaculo* obs = *it;
        if (obs == NULL) continue;

        sf::FloatRect boxObs = obs->getLimitesColisao();
        sf::FloatRect interseccao;

        if (boxPlayer.intersects(boxObs, interseccao)) {
            if (interseccao.width < interseccao.height) {
                // colisão lateral
                if (boxPlayer.left + boxPlayer.width / 2.f < boxObs.left + boxObs.width / 2.f) {
                    pJog1->setX(boxObs.left - 20.f); 
                } else {
                    pJog1->setX(boxObs.left + boxObs.width + 20.f); 
                }
            } else {
                // colisão vertical
                if (boxPlayer.top + boxPlayer.height / 2.f < boxObs.top + boxObs.width / 2.f) {
                    pJog1->setY(boxObs.top + 25.f);
                    pJog1->setVy(0.f);
                    pJog1->setNoChao(true);
                } else {
                    pJog1->setY(boxObs.top + boxObs.height + 90.f);
                    if (pJog1->getVy() < 0.f) {
                        pJog1->setVy(0.f);
                    }
                }
            }
            boxPlayer = pJog1->getLimitesColisao();
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsChao() {
    if (pJog1 == NULL) return;

    sf::FloatRect boxPlayer = pJog1->getLimitesColisao();

    for (std::list<Entidades::Chao*>::iterator it = LChaos.begin(); it != LChaos.end(); ++it) {
        Entidades::Chao* chao = *it;
        if (chao == NULL) continue;

        sf::FloatRect boxChao = chao->getLimitesColisao();
        sf::FloatRect interseccao;

        if (boxPlayer.intersects(boxChao, interseccao)) {
            if (interseccao.width < interseccao.height) {
                // colisão lateral
                if (boxPlayer.left + boxPlayer.width / 2.f < boxChao.left + boxChao.width / 2.f) {
                    pJog1->setX(boxChao.left - 20.f); 
                } else {
                    pJog1->setX(boxChao.left + boxChao.width + 20.f); 
                }
            } else {
                // colisão vertical
                if (boxPlayer.top + boxPlayer.height / 2.f < boxChao.top + boxChao.width / 2.f) {
                    pJog1->setY(boxChao.top + 25.f);
                    pJog1->setVy(0.f);
                    pJog1->setNoChao(true);
                } else {
                    pJog1->setY(boxChao.top + boxChao.height + 90.f);
                    if (pJog1->getVy() < 0.f) {
                        pJog1->setVy(0.f);
                    }
                }
            }
            boxPlayer = pJog1->getLimitesColisao();
        }
    }
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsChao();
    tratarColisoesJogsObstacs();
}

}