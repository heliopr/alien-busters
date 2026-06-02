#ifndef LISTA_H
#define LISTA_H

namespace Listas {

template <typename TL>
class Lista {
public:
    class Elemento {
    private:
        Elemento *pProx;
        TL *pInfo;

    public:
        Elemento() : pProx(0), pInfo(0) {}

        ~Elemento() {
            pProx = 0;
            pInfo = 0;
        }

        void incluir(TL *p) { pInfo = p; }
        void setProx(Elemento *pE) { pProx = pE; }
        Elemento *getProx() const { return pProx; }
        TL *getInfo() const { return pInfo; }
    };

private:
    Elemento *pPrimeiro;
    Elemento *pUltimo;

public:
    Lista();
    ~Lista();

    void incluir(TL *p);
    void remover(TL *p);
    void limpar();
    bool vazia() const;

    Elemento *getPrimeiro() const { return pPrimeiro; }
    Elemento *getUltimo() const { return pUltimo; }
};

template <typename TL>
Lista<TL>::Lista() : pPrimeiro(0), pUltimo(0) {}

template <typename TL>
Lista<TL>::~Lista() {
    limpar();
}

template <typename TL>
void Lista<TL>::incluir(TL *p) {
    Elemento *novoElem = new Elemento();
    novoElem->incluir(p);

    if (pPrimeiro == 0) {
        pPrimeiro = novoElem;
        pUltimo = novoElem;
    } else {
        pUltimo->setProx(novoElem);
        pUltimo = novoElem;
    }
}

template <typename TL>
void Lista<TL>::remover(TL *p) {
    Elemento *atual = pPrimeiro;
    Elemento *anterior = 0;

    while (atual != 0) {
        if (atual->getInfo() == p) {
            if (anterior == 0) {
                pPrimeiro = atual->getProx();
            } else {
                anterior->setProx(atual->getProx());
            }

            if (atual == pUltimo) {
                pUltimo = anterior;
            }

            delete atual;
            return;
        }
        anterior = atual;
        atual = atual->getProx();
    }
}

template <typename TL>
void Lista<TL>::limpar() {
    Elemento *atual = pPrimeiro;
    while (atual != 0) {
        Elemento *proximo = atual->getProx();
        delete atual;
        atual = proximo;
    }
    pPrimeiro = 0;
    pUltimo = 0;
}

template <typename TL>
bool Lista<TL>::vazia() const {
    return pPrimeiro == 0;
}

}

#endif