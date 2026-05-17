#ifndef LISTA_H
#define LISTA_H

#include "Elemento.h"

namespace Listas {
    template <typename TL>
    class Lista {
    private:
        Elemento<TL> *pPrimeiro;
        Elemento<TL> *pUltimo;
    public:
        Lista();
        ~Lista();

        void incluir(TL* p);
        void limpar();

        Elemento<TL>* getPrimeiro() const;
        Elemento<TL>* getUltimo() const;
        bool vazia() const;
    };

    template <typename TL>
    Lista<TL>::Lista() : pPrimeiro(0), pUltimo(0) {}

    template <typename TL>
    Lista<TL>::~Lista() {
        limpar();
    }

    template <typename TL>
    void Lista<TL>::incluir(TL* p) {
        Elemento<TL>* novoElem = new Elemento<TL>();
        novoElem->incluir(p);

        if (pPrimeiro == 0) {
            pPrimeiro = novoElem;
            pUltimo   = novoElem;
        }
        else {
            pUltimo->setProx(novoElem);
            pUltimo = novoElem;
        }
    }

    template <typename TL>
    void Lista<TL>::limpar() {
        Elemento<TL>* atual = pPrimeiro;

        while (atual != 0) {
            Elemento<TL>* proximo = atual->getProximo();
            delete atual;
            atual = proximo;
        }

        pPrimeiro = 0;
        pUltimo   = 0;
    }

    template <typename TL>
    Elemento<TL>* Lista<TL>::getPrimeiro() const {
        return pPrimeiro;
    }

    template <typename TL>
    Elemento<TL>* Lista<TL>::getUltimo() const {
        return pUltimo;
    }

    template <typename TL>
    bool Lista<TL>::vazia() const {
        return pPrimeiro == 0;
    }
}

#endif