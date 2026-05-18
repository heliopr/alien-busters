#include <iostream>

#include "Jogo.h"
#include "Listas/Lista.h"

int main() {
    Listas::Lista<int> lista;

    int x = 0, y = -3, z = 8;
    lista.incluir(&x);
    lista.incluir(&y);
    lista.incluir(&z);

    Listas::Lista<int>::Elemento *atual = lista.getPrimeiro();
    while (atual != 0) {
        std::cout << *atual->getInfo() << std::endl;
        atual = atual->getProximo();
    }

    lista.limpar();

    /*Jogo jogo;
    jogo.executar();*/
    return 0;
}