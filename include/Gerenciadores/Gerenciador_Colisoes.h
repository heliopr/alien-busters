#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <list>
#include <vector>
#include <set>

namespace Entidades {
    class Entidade;
    class Jogador;
    class Obstaculo;
    class Obst_Medio;
    class Inimigo;
    class Projetil;
}

namespace Listas {
    class ListaEntidades;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::vector<Entidades::Inimigo*> LIs;
    std::list<Entidades::Obstaculo*> LOs;
    std::list<Entidades::Obst_Medio*> LOMs;
    std::set<Entidades::Projetil*> LPs;
    Entidades::Jogador* pJog1;
    Listas::ListaEntidades* pListaEntidades;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsObstacsMedios();
    void tratarColisoesJogsInimigs();
    void tratarColisoesJogsProjeteis();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void setJogador(Entidades::Jogador* pJ) { pJog1 = pJ; }
    void setListaEntidades(Listas::ListaEntidades* pLE) { pListaEntidades = pLE; }

    void incluirInimigo(Entidades::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculo* po);
    void incluirObstaculoMedio(Entidades::Obst_Medio* pom);
    void incluirProjetil(Entidades::Projetil* pj);
    
    void executar();
};

}

#endif