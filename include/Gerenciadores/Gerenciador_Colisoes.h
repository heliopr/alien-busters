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
    class Projetil;
}
namespace Listas {
    class ListaEntidades;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::list<Entidades::Obstaculo*> LOs;
    std::list<Entidades::Chao*> LChaos;
    std::list<Entidades::Inimigo*> LIs;
    std::list<Entidades::Projetil*> LPs;
    Entidades::Jogador* pJog1;
    Listas::ListaEntidades* pListaEntidades;
    bool precisaResetar;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsChao();
    void tratarColisoesInimigsObstacs();
    void tratarColisoesInimigsChao();
    void tratarColisoesJogsInimigs();
    void tratarColisoesProjetil();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    bool getPrecisaResetar() const { return precisaResetar; }

    void setJogador(Entidades::Jogador* pJ);
    void setListaEntidades(Listas::ListaEntidades* pLE);
    void incluirObstaculo(Entidades::Obstaculo* po);
    void incluirChao(Entidades::Chao* pc);
    void incluirInimigo(Entidades::Inimigo* pi);
    void incluirProjetil(Entidades::Projetil* pP);

    void executar();
};

}

#endif