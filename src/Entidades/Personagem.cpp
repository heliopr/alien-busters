#include "Entidades/Personagem.h"

namespace Entidades {
namespace Personagens {

Personagem::Personagem() : Entidade(), num_vidas(1), noChao(false) {
}

Personagem::~Personagem() {
}

void Personagem::salvarDataBuffer() {
    // TODO
}

}
}
