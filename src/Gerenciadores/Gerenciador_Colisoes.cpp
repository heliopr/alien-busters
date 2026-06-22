#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Entidade.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"
#include "Entidades/Chao.h"
#include "Entidades/Inimigo.h"
#include "Entidades/Projetil.h"
#include "Listas/ListaEntidades.h"
#include "Configuracao.h"
#include <cstddef>
#include <cmath>

namespace AlienBusters {
namespace Gerenciadores {

Gerenciador_Colisoes* Gerenciador_Colisoes::instancia = 0;

Gerenciador_Colisoes* Gerenciador_Colisoes::getInstancia() {
    if (instancia == 0) {
        instancia = new Gerenciador_Colisoes();
    }
    return instancia;
}

Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(NULL), pJog2(NULL), pListaEntidades(NULL) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    limpar();
}

void Gerenciador_Colisoes::setJogador(Entidades::Personagens::Jogador* pJ) {
    pJog1 = pJ;
}

void Gerenciador_Colisoes::setJogador2(Entidades::Personagens::Jogador* pJ) {
    pJog2 = pJ;
}

void Gerenciador_Colisoes::setListaEntidades(Listas::ListaEntidades* pLE) {
    pListaEntidades = pLE;
}

const std::vector<Entidades::Personagens::Inimigo*>& Gerenciador_Colisoes::getInimigos() const {
    return LIs;
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

void Gerenciador_Colisoes::incluirChao(Entidades::Chao* pc) {
    if (pc != NULL) {
        LCs.push_back(pc);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Entidades::Projeteis::Projetil* pj) {
    if (pj != NULL) {
        LPs.insert(pj);
        if (pListaEntidades) {
            pListaEntidades->incluir(pj);
        }
    }
}

void Gerenciador_Colisoes::limpar() {
    LOs.clear();
    LCs.clear();
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

void Gerenciador_Colisoes::resolverColisaoJogador(Entidades::Personagens::Jogador* jog, const sf::FloatRect& boxObs) {
    switch (detectarColisaoObstaculo(jog->getHitbox(), boxObs)) {
        case COLISAO_ESQUERDA:
            jog->setX(boxObs.left - 20.f);
            break;
        case COLISAO_DIREITA:
            jog->setX(boxObs.left + boxObs.width + 20.f);
            break;
        case COLISAO_CIMA:
            jog->setY(boxObs.top + 25.f);
            jog->setVy(0.f);
            jog->setNoChao(true);
            break;
        case COLISAO_BAIXO:
            jog->setY(boxObs.top + boxObs.height + 75.f);
            if (jog->getVy() < 0.f) {
                jog->setVy(0.f);
            }
            break;
        default:
            break;
    }
}

void Gerenciador_Colisoes::tratarColisaoJogadorObstacs(Entidades::Personagens::Jogador* jog) {
    if (jog == NULL || jog->estaMorto()) return;

    for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Entidades::Obstaculos::Obstaculo* obs = *it;
        if (obs != NULL) {
            obs->obstaculizar(jog);
        }
    }

    jog->setNoChao(false);
    for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Entidades::Obstaculos::Obstaculo* obs = *it;
        if (obs != NULL && obs->colide()) {
            resolverColisaoJogador(jog, obs->getHitbox());
        }
    }
    for (std::list<Entidades::Chao*>::iterator it = LCs.begin(); it != LCs.end(); ++it) {
        if (*it != NULL) {
            resolverColisaoJogador(jog, (*it)->getHitbox());
        }
    }
}

bool Gerenciador_Colisoes::haPlataformaEm(float x, float y) const {
    for (std::list<Entidades::Obstaculos::Obstaculo*>::const_iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Entidades::Obstaculos::Obstaculo* obs = *it;
        if (obs != NULL && obs->colide() && obs->getHitbox().contains(x, y)) {
            return true;
        }
    }
    for (std::list<Entidades::Chao*>::const_iterator it = LCs.begin(); it != LCs.end(); ++it) {
        if (*it != NULL && (*it)->getHitbox().contains(x, y)) {
            return true;
        }
    }
    return false;
}

Gerenciador_Colisoes::ResultadoColisao Gerenciador_Colisoes::resolverColisaoInimigo(Entidades::Personagens::Inimigo* ini, const sf::FloatRect& boxObs) {
    sf::FloatRect boxIni = ini->getHitbox();
    ResultadoColisao resultado = detectarColisaoObstaculo(boxIni, boxObs);

    switch (resultado) {
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

    return resultado;
}

void Gerenciador_Colisoes::tratarColisoesInimigosObstacs() {
    for (std::vector<Entidades::Personagens::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Personagens::Inimigo* ini = *iti;
        if (ini == NULL) continue;

        bool noChao = false;
        bool sobreChao = false;

        for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator ito = LOs.begin(); ito != LOs.end(); ++ito) {
            Entidades::Obstaculos::Obstaculo* obs = *ito;
            if (obs == NULL || !obs->colide()) continue;

            if (resolverColisaoInimigo(ini, obs->getHitbox()) == COLISAO_CIMA) {
                noChao = true;
            }
        }
        for (std::list<Entidades::Chao*>::iterator ito = LCs.begin(); ito != LCs.end(); ++ito) {
            if (*ito == NULL) continue;

            if (resolverColisaoInimigo(ini, (*ito)->getHitbox()) == COLISAO_CIMA) {
                noChao = true;
                sobreChao = true;
            }
        }

        if (noChao && ini->getVelocidadeX() != 0.f) {
            sf::FloatRect boxIni = ini->getHitbox();
            float margem = 5.f;
            float frenteX = (ini->getVelocidadeX() > 0.f)
                                ? boxIni.left + boxIni.width + margem
                                : boxIni.left - margem;
            float peY = boxIni.top + boxIni.height + 2.f;

            if (!haPlataformaEm(frenteX, peY)) {
                if (sobreChao || !ini->deveCairDaBorda()) {
                    ini->setVelocidadeX(-ini->getVelocidadeX());
                }
            } else {
                ini->resetarDecisaoBorda();
            }
        }
    }
}

void Gerenciador_Colisoes::tratarColisaoJogadorInimigs(Entidades::Personagens::Jogador* jog) {
    if (jog == NULL || jog->estaMorto()) return;

    for (std::vector<Entidades::Personagens::Inimigo*>::iterator iti = LIs.begin(); iti != LIs.end(); ++iti) {
        Entidades::Personagens::Inimigo* ini = *iti;
        if (ini == NULL) continue;

        if (verificarColisao(jog, ini)) {
            jog->colidir(ini);
        }
    }
}

bool Gerenciador_Colisoes::projetilColidiu(Entidades::Projeteis::Projetil* p) const {
    for (std::list<Entidades::Obstaculos::Obstaculo*>::const_iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Entidades::Obstaculos::Obstaculo* obs = *it;
        if (obs != NULL && obs->colide() && verificarColisao(p, obs)) {
            return true;
        }
    }
    for (std::list<Entidades::Chao*>::const_iterator it = LCs.begin(); it != LCs.end(); ++it) {
        if (*it != NULL && verificarColisao(p, *it)) {
            return true;
        }
    }
    return false;
}

bool Gerenciador_Colisoes::tratarQuiqueProjetil(Entidades::Projeteis::Projetil* p) {
    if (p == NULL || !p->getQuicavel()) {
        return false;
    }

    const sf::FloatRect boxP = p->getHitbox();

    sf::FloatRect boxSup;
    bool achou = false;
    for (std::list<Entidades::Obstaculos::Obstaculo*>::const_iterator it = LOs.begin(); it != LOs.end() && !achou; ++it) {
        Entidades::Obstaculos::Obstaculo* obs = *it;
        if (obs != NULL && obs->colide() && boxP.intersects(obs->getHitbox())) {
            boxSup = obs->getHitbox();
            achou = true;
        }
    }
    for (std::list<Entidades::Chao*>::const_iterator it = LCs.begin(); it != LCs.end() && !achou; ++it) {
        if (*it != NULL && boxP.intersects((*it)->getHitbox())) {
            boxSup = (*it)->getHitbox();
            achou = true;
        }
    }
    if (!achou) {
        return false;
    }

    const float e = Config::RESTITUICAO_PEDRA;
    const float meiaLargura = boxP.width / 2.f;
    const float meiaAltura = boxP.height / 2.f;

    switch (detectarColisaoObstaculo(boxP, boxSup)) {
        case COLISAO_CIMA: {
            float vyRefletido = -e * p->getVy();
            if (std::fabs(vyRefletido) < Config::VELOCIDADE_MIN_QUIQUE) {
                return false;
            }
            p->setY(boxSup.top - meiaAltura);
            p->setVy(vyRefletido);
            p->setVx(p->getVx() * Config::ATRITO_QUIQUE);
            break;
        }
        case COLISAO_BAIXO:
            p->setY(boxSup.top + boxSup.height + meiaAltura);
            p->setVy(-e * p->getVy());
            break;
        case COLISAO_ESQUERDA:
            p->setX(boxSup.left - meiaLargura);
            p->setVx(-e * p->getVx());
            break;
        case COLISAO_DIREITA:
            p->setX(boxSup.left + boxSup.width + meiaLargura);
            p->setVx(-e * p->getVx());
            break;
        default:
            return false;
    }

    p->quicar();
    return true;
}

bool Gerenciador_Colisoes::projetilColidiuComInimigo(Entidades::Projeteis::Projetil* p) {
    for (std::vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); ++it) {
        Entidades::Personagens::Inimigo* ini = *it;
        if (ini != NULL && verificarColisao(p, ini)) {
            ini->levarDano();

            if (ini->morreu()) {
                float xi = ini->getX();
                float yi = ini->getY();
                int pontos = ini->pontosAoMorrer();

                LIs.erase(it);
                if (pListaEntidades) {
                    pListaEntidades->remover(ini);
                }
                delete ini;

                if (pListaEntidades) {
                    pListaEntidades->criarExplosao(xi, yi - 30.f);
                }
                Entidades::Personagens::Jogador* dono = p->getDono();
                if (dono == NULL) {
                    dono = pJog1;
                }
                if (dono) {
                    dono->adicionarPontos(pontos);
                }
            }
            return true;
        }
    }
    return false;
}

bool Gerenciador_Colisoes::projetilAtingiuJogador(Entidades::Projeteis::Projetil* p, Entidades::Personagens::Jogador* jog) {
    if (jog == NULL || jog->estaMorto()) return false;

    if (verificarColisao(p, jog)) {
        if (!jog->estaInvulneravel()) {
            jog->perderVida();
            jog->ativarInvulnerabilidade();
        }
        return true;
    }
    return false;
}

bool Gerenciador_Colisoes::projetilColidiuComJogador(Entidades::Projeteis::Projetil* p) {
    bool atingiu = projetilAtingiuJogador(p, pJog1);
    atingiu = projetilAtingiuJogador(p, pJog2) || atingiu;
    return atingiu;
}

void Gerenciador_Colisoes::removerProjetil(std::set<Entidades::Projeteis::Projetil*>::iterator it) {
    Entidades::Projeteis::Projetil* p = *it;
    LPs.erase(it);
    if (pListaEntidades) {
        pListaEntidades->remover(p);
    }
    delete p;
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
    std::set<Entidades::Projeteis::Projetil*>::iterator it = LPs.begin();
    while (it != LPs.end()) {
        Entidades::Projeteis::Projetil* p = *it;

        if (!p->getAtivo()) {
            std::set<Entidades::Projeteis::Projetil*>::iterator atual = it;
            ++it;
            removerProjetil(atual);
            continue;
        }

        bool atingiuAlvo = p->getInimigo() ? projetilColidiuComJogador(p) : projetilColidiuComInimigo(p);

        bool destruir;
        if (atingiuAlvo) {
            destruir = true;
        } else if (projetilColidiu(p)) {
            destruir = !tratarQuiqueProjetil(p);
        } else {
            destruir = false;
        }

        if (destruir) {
            p->setAtivo(false);
            std::set<Entidades::Projeteis::Projetil*>::iterator atual = it;
            ++it;
            removerProjetil(atual);
        } else {
            ++it;
        }
    }
}

void Gerenciador_Colisoes::removerObstaculosDestruidos() {
    for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ) {
        Entidades::Obstaculos::Obstaculo* obs = *it;
        if (obs == NULL) {
            it = LOs.erase(it);
            continue;
        }

        if (obs->getDestruido()) {
            if (pListaEntidades) {
                sf::FloatRect box = obs->getHitbox();
                float xExp = box.left + box.width / 2.f;
                float yExp = box.top + box.height / 2.f;
                pListaEntidades->criarExplosao(xExp, yExp - 50.f);
                pListaEntidades->remover(obs);
            }
            delete obs;
            it = LOs.erase(it);
        } else {
            ++it;
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsObtacs() {
    tratarColisaoJogadorObstacs(pJog1);
    tratarColisaoJogadorObstacs(pJog2);
}

void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
    tratarColisaoJogadorInimigs(pJog1);
    tratarColisaoJogadorInimigs(pJog2);
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsObtacs();
    removerObstaculosDestruidos();
    tratarColisoesInimigosObstacs();
    tratarColisoesJogsInimgs();
    tratarColisoesJogsProjeteis();
}

}
}
