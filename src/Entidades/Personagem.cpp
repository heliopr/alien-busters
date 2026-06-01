#include "Entidades/Personagem.h"

namespace Entidades {

Personagem::Personagem() : Entidade(), num_vidas(1), vy(0.f), noChao(false) {
}

Personagem::~Personagem() {
}

void Personagem::salvarDataBuffer() {
    // TODO
}

}
