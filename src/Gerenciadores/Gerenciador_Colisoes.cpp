#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Entidade.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"
#include <cstddef>

namespace Gerenciadores {

Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(NULL) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    LOs.clear();
}

void Gerenciador_Colisoes::setJogador(Entidades::Jogador* pJ) {
    pJog1 = pJ;
}


void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculo* po) {
    if (po != NULL) {
        LOs.push_back(po);
    }
}

const bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
    
    return false;
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
    if (pJog1 == NULL) return;
    
    for (std::list<Entidades::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Entidades::Obstaculo* obs = *it;
        if (verificarColisao(pJog1, obs)) {
            // ..
        }
    }
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsObstacs();
}

}