#include "Entidades/Atirador.h"

namespace AlienBusters {
namespace Entidades {

Atirador::Atirador() : tempoRestante(0.f) {
}

Atirador::~Atirador() {
}

void Atirador::atualizarRecarga(float dt) {
    if (tempoRestante > 0.0f) {
        tempoRestante -= dt;
        if (tempoRestante < 0.0f) {
            tempoRestante = 0.0f;
        }
    }
}

bool Atirador::podeAtirar() const {
    return tempoRestante <= 0.0f;
}

void Atirador::reiniciarRecarga(float tempo) {
    tempoRestante = tempo;
}

}
}