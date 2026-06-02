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

void ListaEntidades::percorrer(float dt, Entidades::Jogador *pJogador) {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            entidade->executar(dt);
        }
        atual = atual->getProximo();
    }

    if (pJogador != 0) {
        atual = LEs.getPrimeiro();
        while (atual != 0) {
            Entidades::Obstaculo *obs = dynamic_cast<Entidades::Obstaculo*>(atual->getInfo());
            if (obs != 0) {
                obs->obstaculizar(pJogador);
            }
            atual = atual->getProximo();
        }
    }

    atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            entidade->desenhar();
        }
        atual = atual->getProximo();
    }
}

}