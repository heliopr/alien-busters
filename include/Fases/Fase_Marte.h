#ifndef FASE_MARTE_H
#define FASE_MARTE_H

#include "Fases/Fase.h"
#include <string>

namespace AlienBusters {
namespace Fases {

class Fase_Marte : public Fase {
private:
    const int maxSlimes;
    const int maxGolems;
    const int maxMinas;

public:
    Fase_Marte(Entidades::Personagens::Jogador* pJogador,
               Entidades::Personagens::Jogador* pJogador2 = 0,
               const std::string& nome1 = "", const std::string& nome2 = "");
    ~Fase_Marte();

protected:
    void criarInimigos();
    void criarObstaculos();
    void criarFoguete();
    void criarMinasExtraterrestres();
    void criarSlimes();
    void criarGolems();
};

}
}

#endif
