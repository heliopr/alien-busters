#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Entidade.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"
#include "Entidades/Obst_Medio.h"
#include "Entidades/Inimigo.h"
#include "Entidades/Projetil.h"
#include "Listas/ListaEntidades.h"
#include <cstddef>

namespace Gerenciadores {

Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(NULL), pListaEntidades(NULL) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    LOs.clear();
    LOMs.clear();
    LIs.clear();
    LPs.clear();
}

void Gerenciador_Colisoes::incluirInimigo(Entidades::Inimigo* pi) {
    if (pi != NULL) {
        LIs.push_back(pi);
    }
}

void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculo* po) {
    if (po != NULL) {
        LOs.push_back(po);
    }
}

void Gerenciador_Colisoes::incluirObstaculoMedio(Entidades::Obst_Medio* pom) {
    if (pom != NULL) {
        LOMs.push_back(pom);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pj) {
    if (pj != NULL) {
        LPs.insert(pj);
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
                    obs->jogadorPisou();
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

void Gerenciador_Colisoes::tratarColisoesJogsInimigs() {
    if (pJog1 == NULL) return;

    for (std::vector<Entidades::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Inimigo* ini = *iti;
        if (ini == NULL) continue;

        if (verificarColisao(pJog1, ini)) {
            pJog1->colidir(ini);
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
    std::set<Entidades::Projetil*>::iterator it;
    for (it = LPs.begin(); it != LPs.end(); ) {
        Entidades::Projetil* p = *it;
        if (!p->getAtivo()) {
            std::set<Entidades::Projetil*>::iterator toErase = it;
            ++it;
            LPs.erase(toErase);
            if (pListaEntidades) {
                pListaEntidades->remover(p);
            }
            delete p;
            continue;
        }

        bool colidiu = false;

        for (std::list<Entidades::Obstaculo*>::iterator ito = LOs.begin(); ito != LOs.end(); ++ito) {
            Entidades::Obstaculo* obs = *ito;
            if (verificarColisao(p, obs)) {
                colidiu = true;
                break;
            }
        }

        if (!colidiu) {
            for (std::vector<Entidades::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ) {
                Entidades::Inimigo* ini = *iti;
                if (ini != NULL && verificarColisao(p, ini)) {
                    colidiu = true;
                    iti = LIs.erase(iti);
                    if (pListaEntidades) {
                        pListaEntidades->remover(ini);
                    }
                    delete ini;
                    break;
                } else {
                    ++iti;
                }
            }
        }

        if (colidiu) {
            p->setAtivo(false);
            std::set<Entidades::Projetil*>::iterator toErase = it;
            ++it;
            LPs.erase(toErase);
            if (pListaEntidades) {
                pListaEntidades->remover(p);
            }
            delete p;
        } else {
            ++it;
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacsMedios() {
    if (pJog1 == NULL) return;

    for (std::list<Entidades::Obst_Medio*>::iterator it = LOMs.begin(); it != LOMs.end(); ++it) {
        Entidades::Obst_Medio* om = *it;
        if (om == NULL) continue;

        if (verificarColisao(pJog1, om)) {
            pJog1->ficarLento(3.0f);
        }
    }
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsObstacs();
    tratarColisoesJogsObstacsMedios();

    for (std::vector<Entidades::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
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

    tratarColisoesJogsInimigs();
    tratarColisoesJogsProjeteis();
}

}