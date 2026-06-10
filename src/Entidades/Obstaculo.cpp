#include "Entidades/Obstaculo.h"
#include "Entidades/Jogador.h"
#include <cstddef>

namespace Entidades {
namespace Obstaculos {

Obstaculo::Obstaculo() : danoso(false) {}

Obstaculo::~Obstaculo() {}

void Obstaculo::salvarDataBuffer() {}

bool Obstaculo::colidiuComJogador(Personagens::Jogador *p) const {
    return p != NULL && p->getHitbox().intersects(getHitbox());
}

}
}