#include "Listas/ListaEntidades.h"
#include "Entidades/Jogador.h"
#include "Entidades/Obstaculo.h"

namespace Listas {

ListaEntidades::ListaEntidades() : LEs() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidades::Entidade *pE) {
    LEs.incluir(pE);
}

void ListaEntidades::percorrer(float dt) {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            entidade->executar(dt);
        }
        atual = atual->getProximo();
    }

    Entidades::Jogador *pJogador = 0;
    atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Jogador *j = dynamic_cast<Entidades::Jogador*>(atual->getInfo());
        if (j != 0) {
            pJogador = j;
            break;
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