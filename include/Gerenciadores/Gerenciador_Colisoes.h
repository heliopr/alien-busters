#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <SFML/Graphics.hpp>
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
    }
}

namespace Listas {
    class ListaEntidades;
}

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    enum ResultadoColisao {
        SEM_COLISAO,
        COLISAO_ESQUERDA,
        COLISAO_DIREITA,
        COLISAO_CIMA,
        COLISAO_BAIXO
    };

    std::vector<Entidades::Personagens::Inimigo*> LIs;
    std::list<Entidades::Obstaculos::Obstaculo*> LOs;
    std::list<Entidades::Explosao*> LExps;
    std::set<Entidades::Projetil*> LPs;
    Entidades::Personagens::Jogador* pJog1;
    Entidades::Personagens::Jogador* pJog2;
    Listas::ListaEntidades* pListaEntidades;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    ResultadoColisao detectarColisaoObstaculo(const sf::FloatRect& box, const sf::FloatRect& boxObs) const;
    bool haPlataformaEm(float x, float y) const;

    void tratarColisoesJogObstacs(Entidades::Personagens::Jogador* jog);
    void tratarColisoesInimigosObstacs();
    void removerObstaculosDestruidos();
    void tratarColisoesJogInimigs(Entidades::Personagens::Jogador* jog);
    void tratarColisoesJogsProjeteis();

    bool projetilColidiuComObstaculo(Entidades::Projetil* p) const;
    bool projetilColidiuComInimigo(Entidades::Projetil* p);
    bool projetilColidiuComJogador(Entidades::Projetil* p);
    bool projetilAtingiuJogador(Entidades::Projetil* p, Entidades::Personagens::Jogador* jog);
    void removerProjetil(std::set<Entidades::Projetil*>::iterator it);

    void criarExplosao(float x, float y);
    void limparExplosoes();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void setJogador(Entidades::Personagens::Jogador* pJ) { pJog1 = pJ; }
    void setJogador2(Entidades::Personagens::Jogador* pJ) { pJog2 = pJ; }
    void setListaEntidades(Listas::ListaEntidades* pLE) { pListaEntidades = pLE; }

    void incluirInimigo(Entidades::Personagens::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
    void incluirProjetil(Entidades::Projetil* pj);
    void limpar();

    const std::vector<Entidades::Personagens::Inimigo*>& getInimigos() const { return LIs; }

    void executar();
};

}

#endif
