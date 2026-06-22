#include "Entidades/Projetil.h"
#include "Entidades/Jogador.h"
#include "Configuracao.h"

namespace AlienBusters {
namespace Entidades {
namespace Projeteis {

Projetil::Projetil(float x, float y, float vx, float vy, Personagens::Jogador* dono, bool inimigo)
    : Entidade(), ativo(true), vx(vx), dono(dono), donoId(dono ? dono->getId() : -1),
      sofreGravidade(false), inimigo(inimigo), quicavel(false) {
    this->x = x;
    this->y = y;
    this->vy = vy;
}

Projetil::~Projetil() {}

void Projetil::salvar() {
    buffer.str("");
    buffer.clear();
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

bool Projetil::getAtivo() const {
    return ativo;
}

void Projetil::setAtivo(bool b) {
    ativo = b;
}

float Projetil::getVx() const {
    return vx;
}

void Projetil::setVx(float v) {
    vx = v;
}

Personagens::Jogador* Projetil::getDono() const {
    return dono;
}

void Projetil::setDono(Personagens::Jogador* d) {
    dono = d;
}

int Projetil::getDonoId() const {
    return donoId;
}

void Projetil::setDonoId(int id) {
    donoId = id;
}

bool Projetil::getInimigo() const {
    return inimigo;
}

bool Projetil::getQuicavel() const {
    return quicavel;
}

void Projetil::quicar() {
}

}
}
}