#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"

class Jogo {
private:
    Gerenciadores::Gerenciador_Grafico GG;

public:
    Jogo();
    ~Jogo();

    void executar();
};

#endif