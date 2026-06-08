#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <list>
#include <vector>
#include <set>

namespace Entidades {
    class Entidade;
    class Jogador;
    class Obstaculo;
    class Obst_Dificil;
    class Inimigo;
    class Projetil;
    class Explosao;
}

namespace Listas {
    class ListaEntidades;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::vector<Entidades::Inimigo*> LIs;
    std::list<Entidades::Obstaculo*> LOs;
    std::list<Entidades::Obst_Dificil*> LODs;
    std::list<Entidades::Explosao*> LExps;
    std::set<Entidades::Projetil*> LPs;
    Entidades::Jogador* pJog1;
    Listas::ListaEntidades* pListaEntidades;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsObstacsDificeis();
    void tratarColisoesJogsInimigs();
    void tratarColisoesJogsProjeteis();
    void criarExplosao(float x, float y);
    void limparExplosoes();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void setJogador(Entidades::Jogador* pJ) { pJog1 = pJ; }
    void setListaEntidades(Listas::ListaEntidades* pLE) { pListaEntidades = pLE; }

    void incluirInimigo(Entidades::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculo* po);
    void incluirObstaculoDificil(Entidades::Obst_Dificil* pod);
    void incluirProjetil(Entidades::Projetil* pj);
    void limpar();
    
    void executar();
};

}

#endif