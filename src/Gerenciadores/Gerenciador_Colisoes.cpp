#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Entidade.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"
#include "Entidades/Chao.h"
#include "Entidades/Inimigo.h"
#include "Entidades/Projetil.h"
#include "Listas/ListaEntidades.h"
#include <cstddef>

namespace Gerenciadores {

Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(NULL), pListaEntidades(NULL), precisaResetar(false) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    LOs.clear();
    LChaos.clear();
    LIs.clear();
    LPs.clear();
}

void Gerenciador_Colisoes::setJogador(Entidades::Jogador* pJ) {
    pJog1 = pJ;
}

void Gerenciador_Colisoes::setListaEntidades(Listas::ListaEntidades* pLE) {
    pListaEntidades = pLE;
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

void Gerenciador_Colisoes::incluirInimigo(Entidades::Inimigo* pi) {
    if (pi != NULL) {
        LIs.push_back(pi);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pP) {
    if (pP != NULL) {
        LPs.push_back(pP);
    }
}

bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
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
                if (boxPlayer.top + boxPlayer.height / 2.f < boxObs.top + boxObs.height / 2.f) {
                    pJog1->setY(boxObs.top + 25.f);
                    pJog1->setVy(0.f);
                    pJog1->setNoChao(true);
                } else {
                    pJog1->setY(boxObs.top + boxObs.height + 75.f);
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
                if (boxPlayer.top + boxPlayer.height / 2.f < boxChao.top + boxChao.height / 2.f) {
                    pJog1->setY(boxChao.top + 25.f);
                    pJog1->setVy(0.f);
                    pJog1->setNoChao(true);
                } else {
                    pJog1->setY(boxChao.top + boxChao.height + 75.f);
                    if (pJog1->getVy() < 0.f) {
                        pJog1->setVy(0.f);
                    }
                }
            }
            boxPlayer = pJog1->getLimitesColisao();
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesInimigsObstacs() {
    for (std::list<Entidades::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Inimigo* ini = *iti;
        if (ini == NULL) continue;
        
        sf::FloatRect boxIni = ini->getLimitesColisao();

        for (std::list<Entidades::Obstaculo*>::iterator ito = LOs.begin(); ito != LOs.end(); ++ito) {
            Entidades::Obstaculo* obs = *ito;
            if (obs == NULL) continue;

            sf::FloatRect boxObs = obs->getLimitesColisao();
            sf::FloatRect interseccao;

            if (boxIni.intersects(boxObs, interseccao)) {
                if (interseccao.width < interseccao.height) {
                    // colisão lateral
                    if (boxIni.left + boxIni.width / 2.f < boxObs.left + boxObs.width / 2.f) {
                        ini->setX(boxObs.left - boxIni.width/2.f); 
                    } else {
                        ini->setX(boxObs.left + boxObs.width + boxIni.width/2.f); 
                    }
                    ini->setVelocidadeX(-ini->getVelocidadeX());
                } else {
                    // colisão vertical
                    if (boxIni.top + boxIni.height / 2.f < boxObs.top + boxObs.height / 2.f) {
                        ini->setY(boxObs.top - boxIni.height/2.f);
                        ini->setVy(0.f);
                        ini->setNoChao(true);
                    } else {
                        ini->setY(boxObs.top + boxObs.height + boxIni.height/2.f);
                        if (ini->getVy() < 0.f) {
                            ini->setVy(0.f);
                        }
                    }
                }
                boxIni = ini->getLimitesColisao();
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesInimigsChao() {
    for (std::list<Entidades::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Inimigo* ini = *iti;
        if (ini == NULL) continue;
        
        sf::FloatRect boxIni = ini->getLimitesColisao();

        for (std::list<Entidades::Chao*>::iterator itc = LChaos.begin(); itc != LChaos.end(); ++itc) {
            Entidades::Chao* chao = *itc;
            if (chao == NULL) continue;

            sf::FloatRect boxChao = chao->getLimitesColisao();
            sf::FloatRect interseccao;

            if (boxIni.intersects(boxChao, interseccao)) {
                if (interseccao.width < interseccao.height) {
                    // colisão lateral
                    if (boxIni.left + boxIni.width / 2.f < boxChao.left + boxChao.width / 2.f) {
                        ini->setX(boxChao.left - boxIni.width/2.f); 
                    } else {
                        ini->setX(boxChao.left + boxChao.width + boxIni.width/2.f); 
                    }
                    ini->setVelocidadeX(-ini->getVelocidadeX());
                } else {
                    // colisão vertical
                    if (boxIni.top + boxIni.height / 2.f < boxChao.top + boxChao.height / 2.f) {
                        ini->setY(boxChao.top - boxIni.height/2.f);
                        ini->setVy(0.f);
                        ini->setNoChao(true);
                    } else {
                        ini->setY(boxChao.top + boxChao.height + boxIni.height/2.f);
                        if (ini->getVy() < 0.f) {
                            ini->setVy(0.f);
                        }
                    }
                }
                boxIni = ini->getLimitesColisao();
            }
        }
    }
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsChao();
    tratarColisoesJogsObstacs();
    tratarColisoesInimigsChao();
    tratarColisoesInimigsObstacs();
    tratarColisoesJogsInimigs();
    tratarColisoesProjetil();
}

void Gerenciador_Colisoes::tratarColisoesJogsInimigs() {
    if (pJog1 == NULL) return;

    sf::FloatRect boxPlayer = pJog1->getLimitesColisao();

    for (std::list<Entidades::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Inimigo* ini = *iti;
        if (ini == NULL) continue;

        sf::FloatRect boxIni = ini->getLimitesColisao();

        if (boxPlayer.intersects(boxIni)) {
            precisaResetar = true;
            break;
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesProjetil() {
    std::list<Entidades::Projetil*>::iterator it;
    for (it = LPs.begin(); it != LPs.end(); ) {
        Entidades::Projetil* p = *it;
        if (!p->getAtivo()) {
            it = LPs.erase(it);
            if (pListaEntidades) {
                pListaEntidades->remover(p);
            }
            delete p;
            continue;
        }

        sf::FloatRect boxProj = p->getLimitesColisao();
        bool colidiu = false;

        for (std::list<Entidades::Chao*>::iterator itc = LChaos.begin(); itc != LChaos.end(); ++itc) {
            Entidades::Chao* chao = *itc;
            if (boxProj.intersects(chao->getLimitesColisao())) {
                colidiu = true;
                break;
            }
        }

        if (!colidiu) {
            for (std::list<Entidades::Obstaculo*>::iterator ito = LOs.begin(); ito != LOs.end(); ++ito) {
                Entidades::Obstaculo* obs = *ito;
                if (boxProj.intersects(obs->getLimitesColisao())) {
                    colidiu = true;
                    break;
                }
            }
        }

        if (colidiu) {
            it = LPs.erase(it);
            if (pListaEntidades) {
                pListaEntidades->remover(p);
            }
            delete p;
        } else {
            ++it;
        }
    }
}

}