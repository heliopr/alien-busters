#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <vector>
#include <list>
#include <set>

namespace Entidades {
    class Entidade;
    class Jogador;
    class Obstaculo;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::list<Entidades::Obstaculo*> LOs;
    Entidades::Jogador* pJog1;

    const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    void tratarColisoesJogsObstacs();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void setJogador(Entidades::Jogador* pJ);

    void incluirObstaculo(Entidades::Obstaculo* po);

    void executar();
};

}

#endif