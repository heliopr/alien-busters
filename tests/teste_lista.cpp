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

int main() {

    teste_lista_vazia();
    teste_incluir();

    std::cout << "PASSOU teste_lista.cpp" << std::endl;
    return 0;
}