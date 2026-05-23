#ifndef LISTA_ENTIDADES_H
#define LISTA_ENTIDADES_H

#include "Listas/Lista.h"
#include "Entidades/Entidade.h"

namespace Listas {

class ListaEntidades {
private:
    Lista<Entidades::Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidades::Entidade *pE);
    void percorrer(float dt);
};

}

#endif