#include "Entidades/Entidade.h"

namespace Entidades {

Entidade::Entidade() : Ente(), x(0), y(0) {}

Entidade::~Entidade() {}

void Entidade::salvarDataBuffer() {
    
}

int Entidade::getX() const {
    return x;
}

int Entidade::getY() const {
    return y;
}

}