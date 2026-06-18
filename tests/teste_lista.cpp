#include <iostream>
#include <cassert>

#include "Listas/Lista.h"

using namespace AlienBusters::Listas;

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
        atual = atual->getProx();
    }

    assert(cont == num);

    lista.limpar();

    delete[] v;

    std::cout << "OK teste_incluir_varios" << std::endl;
}

void teste_ordem_elementos() {
    Lista<int> lista;
    int valores[3] = {10, 20, 30};

    lista.incluir(&valores[0]);
    lista.incluir(&valores[1]);
    lista.incluir(&valores[2]);

    Lista<int>::Elemento *atual = lista.getPrimeiro();

    assert(atual != 0);
    assert(*(atual->getInfo()) == 10);
    
    atual = atual->getProx();
    assert(atual != 0);
    assert(*(atual->getInfo()) == 20);
    
    atual = atual->getProx();
    assert(atual != 0);
    assert(*(atual->getInfo()) == 30);
    
    assert(atual == lista.getUltimo());
    
    assert(atual->getProx() == 0);

    std::cout << "OK teste_ordem_elementos" << std::endl;
}

void teste_limpar_lista_vazia() {
    Lista<int> lista;
    
    lista.limpar();
    
    assert(lista.vazia() == true);
    assert(lista.getPrimeiro() == 0);
    assert(lista.getUltimo() == 0);

    std::cout << "OK teste_limpar_lista_vazia" << std::endl;
}

int main() {

    teste_lista_vazia();
    teste_incluir();
    teste_limpar();
    teste_incluir_varios();

    teste_limpar_lista_vazia();
    teste_ordem_elementos();

    std::cout << "PASSOU teste_lista.cpp" << std::endl;
    return 0;
}