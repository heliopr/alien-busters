#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <list>
#include <SFML/Graphics.hpp>

namespace Entidades {
    class Entidade;
    class Jogador;
    class Obstaculo;
    class Chao;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::list<Entidades::Obstaculo*> LOs;
    std::list<Entidades::Chao*> LChaos;
    Entidades::Jogador* pJog1;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsChao();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void setJogador(Entidades::Jogador* pJ);
    void incluirObstaculo(Entidades::Obstaculo* po);
    void incluirChao(Entidades::Chao* pc);

    void executar();
};

}

#endif