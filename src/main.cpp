#include <iostream>

#include "Jogo.h"
#include "Listas/Lista.h"

int main() {
    int x = 10;
    int y = -100;

    Listas::Elemento<int> a;
    a.incluir(&x);

    Listas::Elemento<int> b;
    b.incluir(&y);
    a.setProx(&b);

    std::cout << *a.getInfo() << std::endl;
    std::cout << *(a.getProximo()->getInfo()) << std::endl;
    std::cout << (a.getProximo()->getProximo()) << std::endl;

    Jogo jogo;
    jogo.executar();
    return 0;
}