#include "Entidades/Entidade.h"

namespace Entidades {

Entidade::Entidade() : Ente(), x(0.0f), y(0.0f) {}

Entidade::~Entidade() {}

void Entidade::salvarDataBuffer() {
    
}

float Entidade::getX() const {
    return x;
}

float Entidade::getY() const {
    return y;
}

}