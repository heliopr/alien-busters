#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <list>
#include <vector>
#include <set>
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
    std::vector<Entidades::Inimigo*> LIs;
    std::set<Entidades::Projetil*> LPs;
    Entidades::Jogador* pJog1;
    Listas::ListaEntidades* pListaEntidades;
    bool precisaResetar;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsChao();
    void tratarColisoesInimigsObstacs();
    void tratarColisoesInimigsChao();
    void tratarColisoesJogsInimigs();
    void tratarColisoesJogsProjeteis();

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