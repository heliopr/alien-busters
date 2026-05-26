#include "Gerenciador_Colisoes.h"
#include "Entidade.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"
#include "Projetil.h"
#include <cstddef>

namespace Gerenciadores {

Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(NULL) {
}

Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    Lis.clear();
    LOs.clear();
    LPs.clear();
}

void Gerenciador_Colisoes::setJogador(Jogador* pJ) {
    pJog1 = pJ;
}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pi) {
    if (pi != NULL) {
        Lis.push_back(pi);
    }
}

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* po) {
    if (po != NULL) {
        LOs.push_back(po);
    }
}

void Gerenciador_Colisoes::incluirProjetil(Projetil* pj) {
    if (pj != NULL) {
        LPs.insert(pj);
    }
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const {
    
    return false;
}

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
    if (pJog1 == NULL) return;
    
    for (std::list<Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it) {
        Obstaculo* obs = *it;
        if (verificarColisao(pJog1, obs)) {
            // ..
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsInimigs() {
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
}

void Gerenciador_Colisoes::executar() {
    tratarColisoesJogsObstacs();
    tratarColisoesJogsInimigs();
    tratarColisoesJogsProjeteis();
}

}