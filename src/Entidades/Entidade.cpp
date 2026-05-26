#include "Entidades/Entidade.h"

namespace Entidades {

Entidade::Entidade() : Ente(), x(0.0f), y(0.0f) {
    pFig = NULL; 
}

Entidade::~Entidade() {
    if (pFig) {
        delete pFig;
        pFig = NULL;
    }
}
void Entidade::salvarDataBuffer() {
    
}

float Entidade::getX() const {
    return x;
}

float Entidade::getY() const {
    return y;
}

}