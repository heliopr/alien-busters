#ifndef ELEMENTO_H
#define ELEMENTO_H

namespace Listas {
    template <typename TE>
    class Elemento {
    private:
        Elemento<TE> *pProx;
        TE *pInfo;

    public:
        Elemento();
        ~Elemento();

        void incluir(TE *p);
        void setProx(Elemento<TE> *pE);

        Elemento<TE> *getProximo() const;
        TE *getInfo() const;
    };

    template <typename TE>
    Elemento<TE>::Elemento() : pProx(0), pInfo(0) {}

    template <typename TE>
    Elemento<TE>::~Elemento() {
        pProx = 0;
        pInfo = 0;
    }

    template <typename TE>
    void Elemento<TE>::incluir(TE *p) {
        pInfo = p;
    }

    template <typename TE>
    void Elemento<TE>::setProx(Elemento<TE> *pE) {
        pProx = pE;
    }

    template <typename TE>
    Elemento<TE> *Elemento<TE>::getProximo() const {
        return pProx;
    }

    template <typename TE>
    TE *Elemento<TE>::getInfo() const {
        return pInfo;
    }
}

#endif