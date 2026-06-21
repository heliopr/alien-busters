#include "Fases/Fase.h"
#include "Entidades/Chao.h"
#include "Entidades/Foguete.h"
#include "Entidades/Inimigo.h"
#include "Entidades/Plataforma.h"
#include "Entidades/Gosma.h"
#include "Entidades/MinaExtraterrestre.h"
#include "Entidades/Alien.h"
#include "Entidades/Slime.h"
#include "Entidades/Golem.h"
#include "Entidades/Projetil.h"
#include "Entidades/Laser.h"
#include "Entidades/Pedra.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Configuracao.h"
#include "Utilidades.h"
#include <cmath>
#include <map>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>

using AlienBusters::Utilidades;

namespace AlienBusters {
namespace Fases {

Fase::Fase(Entidades::Personagens::Jogador* pJogador, Entidades::Personagens::Jogador* pJogador2,
           const std::string& nome1, const std::string& nome2, bool gerarConteudo)
    : Ente(), lista_ents(), pGC(Gerenciadores::Gerenciador_Colisoes::getInstancia()),
      pJogador(pJogador), pJogador2(pJogador2), pFoguete(0), concluida(false),
      nomeJogador(nome1), nomeJogador2(nome2), gerarConteudo(gerarConteudo) {
    pGC->setJogador(pJogador);
    pGC->setJogador2(pJogador2);
    pGC->setListaEntidades(&lista_ents);

    if (pJogador) {
        pJogador->resetar();
    }
    if (pJogador2) {
        pJogador2->resetar();
    }
}

Fase::~Fase() {
    pGC->limpar();
    lista_ents.limpar();
}

void Fase::processarJogador(Entidades::Personagens::Jogador* pJog, float dt) {
    if (pJog == 0 || pJog->estaMorto()) {
        return;
    }

    if (pJog->getY() > Config::ALTURA_LIMITE_QUEDA) {
        pJog->morrer();
        return;
    }

    pJog->atirar();
    pJog->executar(dt);
}

Entidades::Personagens::Jogador* Fase::jogadorMaisProximo(float x, float y) const {
    Entidades::Personagens::Jogador* maisProximo = 0;
    float menorDist = 0.f;

    Entidades::Personagens::Jogador* candidatos[2] = { pJogador, pJogador2 };
    for (int i = 0; i < 2; ++i) {
        Entidades::Personagens::Jogador* jog = candidatos[i];
        if (jog == 0 || jog->estaMorto()) {
            continue;
        }
        float dx = jog->getX() - x;
        float dy = jog->getY() - y;
        float dist = dx * dx + dy * dy;
        if (maisProximo == 0 || dist < menorDist) {
            menorDist = dist;
            maisProximo = jog;
        }
    }

    return maisProximo;
}

void Fase::processarInimigos(float dt) {
    const std::vector<Entidades::Personagens::Inimigo*>& inimigos = pGC->getInimigos();

    for (std::size_t i = 0; i < inimigos.size(); ++i) {
        Entidades::Personagens::Inimigo* ini = inimigos[i];
        if (ini == 0) {
            continue;
        }

        Entidades::Personagens::Jogador* alvo = jogadorMaisProximo(ini->getX(), ini->getY());
        if (alvo == 0) {
            continue;
        }

        ini->atirar(alvo, dt);
    }
}

std::vector<sf::Vector2f> Fase::sortearPosicoes(const float posicoes[][2], int total, int minimo, int maximo) const {
    int teto = (maximo < total) ? maximo : total;
    if (teto < minimo) {
        teto = minimo;
    }

    std::vector<int> indices(total);
    for (int i = 0; i < total; ++i) {
        indices[i] = i;
    }
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i+1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    int quantidade = minimo + std::rand() % (teto-minimo+1);

    std::vector<sf::Vector2f> escolhidas;
    for (int i = 0; i < quantidade; ++i) {
        escolhidas.push_back(sf::Vector2f(posicoes[indices[i]][0], posicoes[indices[i]][1]));
    }
    return escolhidas;
}

void Fase::atualizarCamera() {
    if (pGG == 0) {
        return;
    }

    float somaX = 0.f, somaY = 0.f;
    int n = 0;
    if (pJogador != 0 && !pJogador->estaMorto()) {
        somaX += pJogador->getX();
        somaY += pJogador->getY();
        ++n;
    }
    if (pJogador2 != 0 && !pJogador2->estaMorto()) {
        somaX += pJogador2->getX();
        somaY += pJogador2->getY();
        ++n;
    }

    if (n > 0) {
        pGG->atualizarCamera(sf::Vector2f(somaX / n, somaY / n));
    }
}

void Fase::executar(float dt) {
    processarJogador(pJogador, dt);
    processarJogador(pJogador2, dt);
    processarInimigos(dt);

    if (jogadorPerdeu()) {
        desenhar();
        return;
    }

    lista_ents.percorrer(dt);
    pGC->executar();

    verificarFoguete();

    atualizarCamera();
    desenhar();
}

void Fase::verificarFoguete() {
    if (pFoguete == 0 || concluida) {
        return;
    }

    sf::FloatRect hitboxFoguete = pFoguete->getHitbox();

    bool p1Encostou = (pJogador != 0) && !pJogador->estaMorto() && pJogador->getHitbox().intersects(hitboxFoguete);
    bool p2Encostou = (pJogador2 != 0) && !pJogador2->estaMorto() && pJogador2->getHitbox().intersects(hitboxFoguete);

    if (p1Encostou || p2Encostou)
        concluida = true;
}

void Fase::criarFoguete() {
}

void Fase::desenhar() {
    lista_ents.desenhar();

    if (!jogadorPerdeu()) {
        if (pJogador != 0 && !pJogador->estaMorto()) {
            pJogador->desenhar();
        }
        if (pJogador2 != 0 && !pJogador2->estaMorto()) {
            pJogador2->desenhar();
        }
    }

    if (pGG != 0) {
        if (pJogador != 0) {
            pGG->desenharHUD(pJogador->getPontos(), pJogador->getX(), pJogador->getY(), pJogador->getNumVidas(), false, false);
            
            if (!nomeJogador.empty()) {
                sf::Text nomeText;
                nomeText.setFont(pGG->getFont());
                nomeText.setString(nomeJogador);
                nomeText.setCharacterSize(20);
                nomeText.setFillColor(sf::Color::White);
                nomeText.setPosition(sf::Vector2f(50.f, 115.f));
                pGG->desenharTextoTela(&nomeText);
            }
        }
        if (pJogador2 != 0) {
            pGG->desenharHUD(pJogador2->getPontos(), pJogador2->getX(), pJogador2->getY(), pJogador2->getNumVidas(), true, false);
            
            if (!nomeJogador2.empty()) {
                sf::Text nomeText;
                nomeText.setFont(pGG->getFont());
                nomeText.setString(nomeJogador2);
                nomeText.setCharacterSize(20);
                nomeText.setFillColor(sf::Color(120, 170, 255));
                nomeText.setPosition(sf::Vector2f(1220.f, 115.f));
                pGG->desenharTextoTela(&nomeText);
            }
        }
    }
}

void Fase::criarCenario() {
    criarCenario(sf::Color(145, 60, 25));
}

void Fase::criarCenario(const sf::Color& cor) {
    Entidades::Chao* chao1 = new Entidades::Chao(0.f, 700.f, 800.f, 100.f, cor);
    Entidades::Chao* chao2 = new Entidades::Chao(920.f, 700.f, 780.f, 100.f, cor);
    Entidades::Chao* chao3 = new Entidades::Chao(1850.f, 700.f, 800.f, 100.f, cor);

    pGC->incluirChao(chao1);
    pGC->incluirChao(chao2);
    pGC->incluirChao(chao3);

    lista_ents += chao1;
    lista_ents += chao2;
    lista_ents += chao3;
}

bool Fase::jogadorPerdeu() const {
    bool p1Morto = (pJogador == 0) || pJogador->estaMorto();
    bool p2Morto = (pJogador2 == 0) || pJogador2->estaMorto();
    return p1Morto && p2Morto;
}

void Fase::reiniciar() {
    pGC->limpar();
    lista_ents.limpar();

    pFoguete = 0;
    concluida = false;

    if (pJogador) {
        pJogador->resetar();
    }
    if (pJogador2) {
        pJogador2->resetar();
    }

    criarCenario();
    criarObstaculos();
    criarInimigos();
    criarFoguete();
}

void Fase::salvar(std::vector<std::string>& linhas) const {
    lista_ents.salvar(linhas);
}

Entidades::Entidade* Fase::criarEntidadeDeLinha(const std::string& linha, int& categoria) const {
    std::size_t espaco = linha.find(' ');
    if (espaco == std::string::npos) {
        categoria = CAT_OUTRO;
        return 0;
    }

    std::string tipo = linha.substr(0, espaco);
    std::map<std::string, std::string> c = Utilidades::lerCampos(linha.substr(espaco + 1));
    int idSalvo = Utilidades::campoInt(c, "id", -1);
    float x = Utilidades::campoFloat(c, "x");
    float y = Utilidades::campoFloat(c, "y");
    categoria = CAT_OUTRO;

    if (tipo == "CHAO") {
        categoria = CAT_CHAO;
        Entidades::Chao* chao = new Entidades::Chao(x, y,
            Utilidades::campoFloat(c, "largura"), Utilidades::campoFloat(c, "altura"),
            sf::Color(static_cast<sf::Uint8>(Utilidades::campoInt(c, "r")),
                      static_cast<sf::Uint8>(Utilidades::campoInt(c, "g")),
                      static_cast<sf::Uint8>(Utilidades::campoInt(c, "b"))));
        if (idSalvo >= 0) chao->setId(idSalvo);
        return chao;
    } else if (tipo == "PLATAFORMA") {
        categoria = CAT_OBSTACULO;
        Entidades::Obstaculos::Plataforma* plat = new Entidades::Obstaculos::Plataforma(x, y,
            sf::Color(static_cast<sf::Uint8>(Utilidades::campoInt(c, "r")),
                      static_cast<sf::Uint8>(Utilidades::campoInt(c, "g")),
                      static_cast<sf::Uint8>(Utilidades::campoInt(c, "b"))));
        if (idSalvo >= 0) plat->setId(idSalvo);
        return plat;
    } else if (tipo == "GOSMA") {
        categoria = CAT_OBSTACULO;
        Entidades::Obstaculos::Gosma* gosma = new Entidades::Obstaculos::Gosma(x, y);
        if (idSalvo >= 0) gosma->setId(idSalvo);
        return gosma;
    } else if (tipo == "MINA") {
        categoria = CAT_OBSTACULO;
        Entidades::Obstaculos::MinaExtraterrestre* mina = new Entidades::Obstaculos::MinaExtraterrestre(x, y);
        if (idSalvo >= 0) mina->setId(idSalvo);
        return mina;
    } else if (tipo == "ALIEN") {
        categoria = CAT_INIMIGO;
        Entidades::Personagens::Alien* alien = new Entidades::Personagens::Alien(x, y);
        if (idSalvo >= 0) alien->setId(idSalvo);
        alien->setVelocidade(Utilidades::campoFloat(c, "vel"));
        alien->setNivelMaldade(Utilidades::campoInt(c, "maldade"));
        alien->setNumVidas(Utilidades::campoInt(c, "vidas", 1));
        return alien;
    } else if (tipo == "SLIME") {
        categoria = CAT_INIMIGO;
        Entidades::Personagens::Slime* slime = new Entidades::Personagens::Slime(x, y);
        if (idSalvo >= 0) slime->setId(idSalvo);
        slime->setNivel(Utilidades::campoFloat(c, "nivel"));
        slime->setNivelMaldade(Utilidades::campoInt(c, "maldade"));
        slime->setNumVidas(Utilidades::campoInt(c, "vidas", 1));
        return slime;
    } else if (tipo == "GOLEM") {
        categoria = CAT_INIMIGO;
        Entidades::Personagens::Golem* golem = new Entidades::Personagens::Golem(x, y);
        if (idSalvo >= 0) golem->setId(idSalvo);
        golem->setTempoRecarga(Utilidades::campoFloat(c, "recarga", 5.f));
        golem->setNivelMaldade(Utilidades::campoInt(c, "maldade"));
        golem->setNumVidas(Utilidades::campoInt(c, "vidas", 5));
        return golem;
    } else if (tipo == "FOGUETE") {
        categoria = CAT_FOGUETE;
        Entidades::Foguete* fog = new Entidades::Foguete(x, y);
        if (idSalvo >= 0) fog->setId(idSalvo);
        return fog;
    } else if (tipo == "LASER" || tipo == "PEDRA") {
        categoria = CAT_PROJETIL;
        float vx = Utilidades::campoFloat(c, "vx");
        float vy = Utilidades::campoFloat(c, "vy");
        bool inimigo = Utilidades::campoInt(c, "inimigo") != 0;
        Entidades::Projeteis::Projetil* proj;
        if (tipo == "LASER") {
            proj = new Entidades::Projeteis::Laser(x, y, vx, vy, 0, inimigo);
        } else {
            proj = new Entidades::Projeteis::Pedra(x, y, vx, vy, 0, inimigo);
        }
        if (idSalvo >= 0) proj->setId(idSalvo);
        proj->setDonoId(Utilidades::campoInt(c, "dono", -1));
        return proj;
    }

    return 0;
}

void Fase::carregar(const std::vector<std::string>& linhas) {
    pGC->limpar();
    lista_ents.limpar();
    pFoguete = 0;
    concluida = false;

    int maiorId = Ente::getProximoId();
    std::vector<Entidades::Projeteis::Projetil*> projeteis;

    for (std::size_t i = 0; i < linhas.size(); ++i) {
        int categoria = CAT_OUTRO;
        Entidades::Entidade* ent = criarEntidadeDeLinha(linhas[i], categoria);
        if (ent == 0) {
            continue;
        }

        if (ent->getId() >= maiorId) {
            maiorId = ent->getId() + 1;
        }

        switch (categoria) {
            case CAT_CHAO: {
                Entidades::Chao* chao = static_cast<Entidades::Chao*>(ent);
                pGC->incluirChao(chao);
                lista_ents += chao;
                break;
            }
            case CAT_OBSTACULO: {
                Entidades::Obstaculos::Obstaculo* obs = static_cast<Entidades::Obstaculos::Obstaculo*>(ent);
                pGC->incluirObstaculo(obs);
                lista_ents.incluir(obs);
                break;
            }
            case CAT_INIMIGO: {
                Entidades::Personagens::Inimigo* ini = static_cast<Entidades::Personagens::Inimigo*>(ent);
                lista_ents.incluir(ini);
                pGC->incluirInimigo(ini);
                break;
            }
            case CAT_FOGUETE: {
                Entidades::Foguete* fog = static_cast<Entidades::Foguete*>(ent);
                pFoguete = fog;
                lista_ents += fog;
                break;
            }
            case CAT_PROJETIL: {
                Entidades::Projeteis::Projetil* proj = static_cast<Entidades::Projeteis::Projetil*>(ent);
                projeteis.push_back(proj);
                pGC->incluirProjetil(proj);
                break;
            }
            default:
                delete ent;
                break;
        }
    }

    for (std::size_t i = 0; i < projeteis.size(); ++i) {
        int donoId = projeteis[i]->getDonoId();
        if (donoId >= 0) {
            if (pJogador && pJogador->getId() == donoId) {
                projeteis[i]->setDono(pJogador);
            } else if (pJogador2 && pJogador2->getId() == donoId) {
                projeteis[i]->setDono(pJogador2);
            }
        }
    }

    Ente::setProximoId(maiorId);
}

}
}
