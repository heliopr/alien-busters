#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <list>
#include <SFML/Graphics.hpp>

namespace Entidades {
    class Entidade;
    class Jogador;
    class Obstaculo;
    class Chao;
    class Inimigo;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::list<Entidades::Obstaculo*> LOs;
    std::list<Entidades::Chao*> LChaos;
    std::list<Entidades::Inimigo*> LIs;
    Entidades::Jogador* pJog1;
    bool precisaResetar;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsChao();
    void tratarColisoesInimigsObstacs();
    void tratarColisoesInimigsChao();
    void tratarColisoesJogsInimigs();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    bool getPrecisaResetar() const { return precisaResetar; }

    void setJogador(Entidades::Jogador* pJ);
    void incluirObstaculo(Entidades::Obstaculo* po);
    void incluirChao(Entidades::Chao* pc);
    void incluirInimigo(Entidades::Inimigo* pi);

    void executar();
};

}

#endif