#ifndef LISTA_ENTIDADES_H
#define LISTA_ENTIDADES_H

#include "Listas/Lista.h"
#include "Entidades/Entidade.h"

namespace AlienBusters {
namespace Listas {

class ListaEntidades {
private:
    Lista<Entidades::Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidades::Entidade *pE);
    void incluir(Entidades::Entidade *pE, float x, float y);
    ListaEntidades& operator+=(Entidades::Entidade *pE);
    void remover(Entidades::Entidade *pE);
    void limpar();
    void criarExplosao(float x, float y);
    void percorrer(float dt);
    void desenhar();
};

}
}

#endif
