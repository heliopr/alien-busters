#include "Listas/ListaEntidades.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"

namespace Listas {

ListaEntidades::ListaEntidades() : LEs() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidades::Entidade *pE) {
    LEs.incluir(pE);
}

void ListaEntidades::remover(Entidades::Entidade *pE) {
    LEs.remover(pE);
}

void ListaEntidades::limpar() {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *ent = atual->getInfo();
        atual = atual->getProx();
        if (ent != 0) {
            delete ent;
        }
    }
    LEs.limpar();
}

void ListaEntidades::percorrer(float dt, Entidades::Personagens::Jogador *pJogador, Entidades::Personagens::Jogador *pJogador2) {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            entidade->executar(dt);
        }
        atual = atual->getProx();
    }

    Entidades::Personagens::Jogador *jogadores[2] = { pJogador, pJogador2 };
    atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Obstaculos::Obstaculo *obs = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(atual->getInfo());
        if (obs != 0) {
            for (int i = 0; i < 2; ++i) {
                if (jogadores[i] != 0) {
                    obs->obstaculizar(jogadores[i]);
                }
            }
        }
        atual = atual->getProx();
    }

    atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            entidade->desenhar();
        }
        atual = atual->getProx();
    }
}

}
