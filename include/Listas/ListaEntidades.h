#ifndef LISTA_ENTIDADES_H
#define LISTA_ENTIDADES_H

#include "Listas/Lista.h"
#include "Entidades/Entidade.h"

namespace Entidades { namespace Personagens { class Jogador; } }

namespace Listas {

class ListaEntidades {
private:
    Lista<Entidades::Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidades::Entidade *pE);
    void remover(Entidades::Entidade *pE);
    void limpar();
    void percorrer(float dt, Entidades::Personagens::Jogador *pJogador);
};

}

#endif
