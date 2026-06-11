#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Entidade.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"
#include "Entidades/MinaExtraterrestre.h"
#include "Entidades/Inimigo.h"
#include "Entidades/Projetil.h"
#include "Entidades/Explosao.h"
#include "Listas/ListaEntidades.h"
#include <cstddef>

namespace Gerenciadores {

Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(NULL), pListaEntidades(NULL) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    limpar();
}

void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi) {
    if (pi != NULL) {
        LIs.push_back(pi);
    }
}

void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* po) {
    if (po != NULL) {
        LOs.push_back(po);
    }
}

void Gerenciador_Colisoes::incluirObstaculoDificil(Entidades::Obstaculos::MinaExtraterrestre* pod) {
    if (pod != NULL) {
        LODs.push_back(pod);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pj) {
    if (pj != NULL) {
        LPs.insert(pj);
    }
}

void Gerenciador_Colisoes::limpar() {
    LOs.clear();
    LODs.clear();
    LExps.clear();
    LIs.clear();
    LPs.clear();
}

bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
    if (pe1 == NULL || pe2 == NULL) return false;

    sf::FloatRect box1 = pe1->getHitbox();
    sf::FloatRect box2 = pe2->getHitbox();

    return box1.intersects(box2);
}

Gerenciador_Colisoes::ResultadoColisao Gerenciador_Colisoes::detectarColisaoObstaculo(const sf::FloatRect& box, const sf::FloatRect& boxObs) const {
    sf::FloatRect interseccao;
    if (!box.intersects(boxObs, interseccao)) {
        return SEM_COLISAO;
    }

    if (interseccao.width < interseccao.height) {
        if (box.left + box.width / 2.f < boxObs.left + boxObs.width / 2.f) {
            return COLISAO_ESQUERDA;
        }
        return COLISAO_DIREITA;
    }

    if (box.top + box.height / 2.f < boxObs.top + boxObs.height / 2.f) {
        return COLISAO_CIMA;
    }
    return COLISAO_BAIXO;
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
    if (pJog1 == NULL) return;

    for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Entidades::Obstaculos::Obstaculo* obs = *it;
        if (obs == NULL) continue;

        sf::FloatRect boxObs = obs->getHitbox();

        switch (detectarColisaoObstaculo(pJog1->getHitbox(), boxObs)) {
            case COLISAO_ESQUERDA:
                pJog1->setX(boxObs.left - 20.f);
                break;
            case COLISAO_DIREITA:
                pJog1->setX(boxObs.left + boxObs.width + 20.f);
                break;
            case COLISAO_CIMA:
                pJog1->setY(boxObs.top + 25.f);
                pJog1->setVy(0.f);
                pJog1->setNoChao(true);
                break;
            case COLISAO_BAIXO:
                pJog1->setY(boxObs.top + boxObs.height + 75.f);
                if (pJog1->getVy() < 0.f) {
                    pJog1->setVy(0.f);
                }
                break;
            default:
                break;
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesInimigosObstacs() {
    for (std::vector<Entidades::Personagens::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Personagens::Inimigo* ini = *iti;
        if (ini == NULL) continue;

        for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator ito = LOs.begin(); ito != LOs.end(); ++ito) {
            Entidades::Obstaculos::Obstaculo* obs = *ito;
            if (obs == NULL) continue;

            sf::FloatRect boxIni = ini->getHitbox();
            sf::FloatRect boxObs = obs->getHitbox();

            switch (detectarColisaoObstaculo(boxIni, boxObs)) {
                case COLISAO_ESQUERDA:
                    ini->setX(boxObs.left - boxIni.width / 2.f);
                    ini->setVelocidadeX(-ini->getVelocidadeX());
                    break;
                case COLISAO_DIREITA:
                    ini->setX(boxObs.left + boxObs.width + boxIni.width / 2.f);
                    ini->setVelocidadeX(-ini->getVelocidadeX());
                    break;
                case COLISAO_CIMA:
                    ini->setY(boxObs.top - boxIni.height / 2.f);
                    ini->setVy(0.f);
                    ini->setNoChao(true);
                    break;
                case COLISAO_BAIXO:
                    ini->setY(boxObs.top + boxObs.height + boxIni.height / 2.f);
                    if (ini->getVy() < 0.f) {
                        ini->setVy(0.f);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsInimigs() {
    if (pJog1 == NULL) return;

    for (std::vector<Entidades::Personagens::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Personagens::Inimigo* ini = *iti;
        if (ini == NULL) continue;

        if (verificarColisao(pJog1, ini)) {
            pJog1->colidir(ini);
        }
    }
}

bool Gerenciador_Colisoes::projetilColidiuComObstaculo(Entidades::Projetil* p) const {
    for (std::list<Entidades::Obstaculos::Obstaculo*>::const_iterator it = LOs.begin(); it != LOs.end(); ++it) {
        if (verificarColisao(p, *it)) {
            return true;
        }
    }
    return false;
}

bool Gerenciador_Colisoes::projetilColidiuComInimigo(Entidades::Projetil* p) {
    for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); ++it) {
        Entidades::Personagens::Inimigo* ini = *it;
        if (ini != NULL && verificarColisao(p, ini)) {
            float xi = ini->getX();
            float yi = ini->getY();

            LIs.erase(it);
            if (pListaEntidades) {
                pListaEntidades->remover(ini);
            }
            delete ini;

            criarExplosao(xi, yi - 30.f);
            if (pJog1) {
                pJog1->adicionarPontos(100);
            }
            return true;
        }
    }
    return false;
}

void Gerenciador_Colisoes::removerProjetil(std::set<Entidades::Projetil*>::iterator it) {
    Entidades::Projetil* p = *it;
    LPs.erase(it);
    if (pListaEntidades) {
        pListaEntidades->remover(p);
    }
    delete p;
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
    std::set<Entidades::Projetil*>::iterator it = LPs.begin();
    while (it != LPs.end()) {
        Entidades::Projetil* p = *it;

        if (!p->getAtivo()) {
            std::set<Entidades::Projetil*>::iterator atual = it;
            ++it;
            removerProjetil(atual);
            continue;
        }

        bool colidiu = projetilColidiuComObstaculo(p) || projetilColidiuComInimigo(p);

        if (colidiu) {
            p->setAtivo(false);
            std::set<Entidades::Projetil*>::iterator atual = it;
            ++it;
            removerProjetil(atual);
        } else {
            ++it;
        }
    }
}

void Gerenciador_Colisoes::removerMinasDestruidas() {
    for (std::list<Entidades::Obstaculos::MinaExtraterrestre*>::iterator it = LODs.begin(); it != LODs.end(); ) {
        Entidades::Obstaculos::MinaExtraterrestre* od = *it;
        if (od == NULL) {
            it = LODs.erase(it);
            continue;
        }

        if (od->getDestruido()) {
            float xExp = od->getX() + 30.f;
            float yExp = od->getY() + 30.f;

            criarExplosao(xExp, yExp - 50.f);

            if (pListaEntidades) {
                pListaEntidades->remover(od);
            }
            delete od;
            it = LODs.erase(it);
        } else {
            ++it;
        }
    }
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsObstacs();
    removerMinasDestruidas();
    tratarColisoesInimigosObstacs();
    tratarColisoesJogsInimigs();
    tratarColisoesJogsProjeteis();
    limparExplosoes();
}

void Gerenciador_Colisoes::criarExplosao(float x, float y) {
    Entidades::Explosao* exp = new Entidades::Explosao(x, y);
    LExps.push_back(exp);
    if (pListaEntidades) {
        pListaEntidades->incluir(exp);
    }
}

void Gerenciador_Colisoes::limparExplosoes() {
    for (std::list<Entidades::Explosao*>::iterator it = LExps.begin(); it != LExps.end(); ) {
        Entidades::Explosao* exp = *it;
        if (exp != NULL && exp->getTerminada()) {
            if (pListaEntidades) {
                pListaEntidades->remover(exp);
            }
            delete exp;
            it = LExps.erase(it);
        } else {
            ++it;
        }
    }
}

}
