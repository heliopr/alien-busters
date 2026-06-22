#include "Entidades/Obstaculo.h"
#include "Entidades/Jogador.h"
#include <cstddef>

namespace AlienBusters {
namespace Entidades {
namespace Obstaculos {

Obstaculo::Obstaculo() : danoso(false) {}

Obstaculo::~Obstaculo() {}

bool Obstaculo::colidiuComJogador(Personagens::Jogador *p) const {
    return p != NULL && p->getHitbox().intersects(getHitbox());
}

bool Obstaculo::colide() const {
    return true;
}

void Obstaculo::destruir() {
}

bool Obstaculo::getDestruido() const {
    return false;
}

}
}
}