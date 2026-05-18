#include "Listas/ListaEntidades.h"

namespace Listas {

ListaEntidades::ListaEntidades() : LEs() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidades::Entidade *pE) {
    LEs.incluir(pE);
}

void ListaEntidades::percorrer() {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            entidade->executar();
        }
        atual = atual->getProximo();
    }
}

}