#include "Entidades/Inimigo.h"
#include "Entidades/Jogador.h"
#include "Configuracao.h"
#include <cstddef>

namespace Entidades {
namespace Personagens {

Inimigo::Inimigo() : Personagem(), nivel_maldade(0), velocidadeX(-50.f) {
}

Inimigo::~Inimigo() {
}

void Inimigo::moverComGravidade(float dt) {
    x += velocidadeX * dt;
    sofrerGravidade(dt);

    if (y > Config::ALTURA_LIMITE_QUEDA) {
        y = Config::POSICAO_INICIAL_Y;
        vy = 0.f;
    }
}

void Inimigo::danificar(Jogador* p) {
    if (p != NULL && !p->estaInvulneravel()) {
        p->perderVida();
        p->ativarInvulnerabilidade();
    }
}

}
}