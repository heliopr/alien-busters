#include <iostream>
#include <cassert>

#include "Listas/Lista.h"

using namespace Listas;

void teste_lista_vazia() {
    Lista<int> lista;
    
    assert(lista.vazia() == true);
    assert(lista.getPrimeiro() == 0);
    assert(lista.getUltimo() == 0);
    
    std::cout << "OK teste_lista_vazia" << std::endl;
}

void teste_incluir() {
    Lista<int> lista;
    int x = 33;
    lista.incluir(&x);

    assert(lista.vazia() == false);
    assert(lista.getPrimeiro() != 0);
    assert(lista.getPrimeiro() == lista.getUltimo());
    assert(lista.getPrimeiro()->getInfo() == &x);
    assert(*(lista.getPrimeiro()->getInfo()) == x);
    
    std::cout << "OK teste_incluir" << std::endl;
}

void teste_limpar() {
    Lista<int> lista;

    int v[10];

    for (int i = 0; i < 10; i++) {
        v[i] = i;
        lista.incluir(&v[i]);
    }

    lista.limpar();
    assert(lista.vazia() == true);
    
    std::cout << "OK teste_limpar" << std::endl;
}

void teste_incluir_varios() {
    Lista<int> lista;
    int num = 1000;

    int *v = new int[num];
    for (int i = 0; i < num; i++) {
        v[i] = i;
        lista.incluir(&v[i]);
    }

    Lista<int>::Elemento *atual = lista.getPrimeiro();
    int cont = 0;
    while (atual != 0) {
        cont++;
        atual = atual->getProximo();
    }

    assert(cont == num);

    lista.limpar();
    
    delete[] v;

    std::cout << "OK teste_incluir_varios" << std::endl;
}

int main() {

    teste_lista_vazia();
    teste_incluir();
    teste_limpar();
    teste_incluir_varios();

    std::cout << "PASSOU teste_lista.cpp" << std::endl;
    return 0;
}