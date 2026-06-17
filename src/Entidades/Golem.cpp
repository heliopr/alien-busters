#include "Entidades/Golem.h"
#include "Entidades/Jogador.h"
#include "Entidades/Pedra.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Configuracao.h"
#include <cstdlib>
#include <cstddef>
#include <cmath>

namespace Entidades {
namespace Personagens {

Golem::Golem(float x_ini, float y_ini)
    : Inimigo(), Atirador(), tempoRecarga(3.f + ((std::rand() % 100) / 100.f * 2.f))
{
    x = x_ini;
    y = y_ini;
    num_vidas = 5;

    float v = 20.f + std::rand() % 20;
    velocidadeX = (std::rand() % 2 == 0) ? v : -v;

    pFig = new sf::RectangleShape(sf::Vector2f(202.5f, 144.f));
    if (pFig != NULL) {
        pFig->setOrigin(101.25f, 96.f);
        pFig->setPosition(sf::Vector2f(x, y));

        if (animacao.carregar("assets/textures/golem.png", 10, 1, "Erro ao carregar textura do golem!")) {
            pFig->setTexture(animacao.getTextura());
            animacao.aplicar(pFig, 0, false);
        } else {
            pFig->setFillColor(sf::Color::Red);
        }
    }
}

Golem::~Golem() {
}

void Golem::executar(float dt) {
    mover(dt);
    atualizarFlashDano(dt);

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));

        animacao.atualizar(dt, 0.1f, 10);
        animacao.aplicar(pFig, 0, velocidadeX < 0);

        if (estaFlashando()) {
            pFig->setTexture(animacao.getTexturaBranca());
        } else {
            pFig->setTexture(animacao.getTextura());
        }
    }
}

void Golem::salvar() {
}

void Golem::danificar(Jogador* p) {
    Inimigo::danificar(p);
}

sf::FloatRect Golem::getHitbox() const {
    return sf::FloatRect(x - 52.5f, y - 48, 105.f, 96.f);
}

void Golem::atirar(Jogador* alvo, float dt) {
    if (alvo == NULL) {
        return;
    }

    float dx = alvo->getX() - x;
    float dy = (alvo->getY() - 50.f) - y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist > Config::ALCANCE_TIRO_GOLEM) {
        return;
    }

    atualizarRecarga(dt);
    if (!podeAtirar()) {
        return;
    }

    reiniciarRecarga(tempoRecarga);

    float vx, vy;
    if (std::fabs(dx) < 1.f) {
        vx = 0.f;
        vy = -Config::VELOCIDADE_PEDRA;
    } else {
        vx = (dx > 0.f) ? Config::VELOCIDADE_PEDRA : -Config::VELOCIDADE_PEDRA;
        float t = dx / vx;
        vy = (dy - 0.5f * Config::GRAVIDADE_PROJETIL * t * t) / t;
    }

    Projeteis::Projetil* pedra = new Projeteis::Pedra(x, y, vx, vy, 0, true);
    Gerenciadores::Gerenciador_Colisoes::getInstancia()->incluirProjetil(pedra);
}

}
}
