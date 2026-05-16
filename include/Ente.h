#ifndef ENTE_H
#define ENTE_H

#include "Gerenciadores/Gerenciador_Grafico.h"

class Ente {
protected:
    int id;
    static Gerenciadores::Gerenciador_Grafico *pGG;
    // TODO: adicionar pFig

public:
    Ente();
    virtual ~Ente();

    virtual void executar() = 0;
    void desenhar();

    void static setGG(Gerenciadores::Gerenciador_Grafico *pG);
};

#endif