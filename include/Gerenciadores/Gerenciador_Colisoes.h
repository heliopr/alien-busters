#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <list>
#include <vector>
#include <set>

namespace Entidades {
    class Entidade;
    class Projetil;
    class Explosao;
    namespace Personagens {
        class Jogador;
        class Inimigo;
    }
    namespace Obstaculos {
        class Obstaculo;
        class MinaExtraterrestre;
    }
}

namespace Listas {
    class ListaEntidades;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::vector<Entidades::Personagens::Inimigo*> LIs;
    std::list<Entidades::Obstaculos::Obstaculo*> LOs;
    std::list<Entidades::Obstaculos::MinaExtraterrestre*> LODs;
    std::list<Entidades::Explosao*> LExps;
    std::set<Entidades::Projetil*> LPs;
    Entidades::Personagens::Jogador* pJog1;
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

    void setJogador(Entidades::Personagens::Jogador* pJ) { pJog1 = pJ; }
    void setListaEntidades(Listas::ListaEntidades* pLE) { pListaEntidades = pLE; }

    void incluirInimigo(Entidades::Personagens::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
    void incluirObstaculoDificil(Entidades::Obstaculos::MinaExtraterrestre* pod);
    void incluirProjetil(Entidades::Projetil* pj);
    void limpar();

    void executar();
};

}

#endif
