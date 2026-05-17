#include <iostream>

#include "Jogo.h"
#include "Listas/Elemento.h"
#include "Listas/Lista.h"

void testarLista() {
    Listas::Lista<int> lista;

    for (int i = 0; i < 10; i++) {
        int *x = new int(i);
        lista.incluir(x);
    }

    std::cout << "Imprimindo lista" << std::endl;
    Listas::Elemento<int> *atual = lista.getPrimeiro();
    while (atual != 0) {
        int x = *atual->getInfo();
        std::cout << x << " ";
        atual = atual->getProximo();
    }
    std::cout << std::endl;

    atual = lista.getPrimeiro();
    while (atual != 0) {
        delete atual->getInfo();
        atual = atual->getProximo();
    }

    lista.limpar();
}

int main() {
    testarLista();

    /*
    Jogo jogo;
    jogo.executar();
    */
    return 0;
}