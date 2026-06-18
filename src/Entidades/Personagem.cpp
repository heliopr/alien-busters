#include "Entidades/Personagem.h"

namespace AlienBusters {
namespace Entidades {
namespace Personagens {

Personagem::Personagem() : Entidade(), num_vidas(1), noChao(false) {
}

Personagem::Personagem(int num_vidas) : Entidade(), num_vidas(num_vidas), noChao(false) {
}

Personagem::~Personagem() {
}

Personagem& Personagem::operator--() {
    num_vidas--;
    return *this;
}

void Personagem::salvarDataBuffer() {
    // TODO
}

}
}
}
