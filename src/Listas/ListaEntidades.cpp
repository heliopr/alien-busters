#include "Listas/ListaEntidades.h"
#include "Entidades/Explosao.h"

namespace AlienBusters {
namespace Listas {

ListaEntidades::ListaEntidades() : LEs() {}

ListaEntidades::~ListaEntidades() {}

void ListaEntidades::incluir(Entidades::Entidade *pE) {
    LEs.incluir(pE);
}

void ListaEntidades::incluir(Entidades::Entidade *pE, float x, float y) {
    if (pE != 0) {
        pE->setX(x);
        pE->setY(y);
    }
    LEs.incluir(pE);
}

ListaEntidades& ListaEntidades::operator+=(Entidades::Entidade *pE) {
    LEs.incluir(pE);
    return *this;
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

void ListaEntidades::criarExplosao(float x, float y) {
    LEs.incluir(new Entidades::Explosao(x, y));
}

void ListaEntidades::percorrer(float dt) {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        Lista<Entidades::Entidade>::Elemento *prox = atual->getProx();
        if (entidade != 0) {
            entidade->executar(dt);
            if (entidade->finalizada()) {
                LEs.remover(entidade);
                delete entidade;
            }
        }
        atual = prox;
    }
}

void ListaEntidades::desenhar() {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            entidade->desenhar();
        }
        atual = atual->getProx();
    }
}

void ListaEntidades::serializar(std::vector<std::string>& linhas) const {
    Lista<Entidades::Entidade>::Elemento *atual = LEs.getPrimeiro();
    while (atual != 0) {
        Entidades::Entidade *entidade = atual->getInfo();
        if (entidade != 0) {
            std::string linha = entidade->serializar();
            if (!linha.empty()) {
                linhas.push_back(linha);
            }
        }
        atual = atual->getProx();
    }
}

}
}
