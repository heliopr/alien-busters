#include "Entidades/Projetil.h"
#include "Configuracao.h"

namespace Entidades {

Projetil::Projetil(float x, float y, float vx, float vy, Personagens::Jogador* dono, bool inimigo)
    : Entidade(), ativo(true), vx(vx), dono(dono), sofreGravidade(false), inimigo(inimigo), quicavel(false) {
    this->x = x;
    this->y = y;
    this->vy = vy;
}

Projetil::~Projetil() {}

void Projetil::salvar() {
    // TODO
}

void Projetil::executar(float dt) {
    if (!ativo) return;

    x += vx * dt;

    aplicarGravidade(dt, Config::GRAVIDADE_PROJETIL);

    if (!sofreGravidade) {
        contrariarGravidade(dt);
    }

    if (pFig != NULL) {
        pFig->setPosition(sf::Vector2f(x, y));
    }

    if (x < -1000.f || x > 5000.f || y > 3000.f || y < -1000.f) {
        ativo = false;
    }
}

}