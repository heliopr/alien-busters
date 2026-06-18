#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <set>

namespace AlienBusters {

namespace Entidades {
    class Entidade;
    class Chao;
    namespace Projeteis {
        class Projetil;
    }
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
    static Gerenciador_Colisoes* instancia;

    enum ResultadoColisao {
        SEM_COLISAO,
        COLISAO_ESQUERDA,
        COLISAO_DIREITA,
        COLISAO_CIMA,
        COLISAO_BAIXO
    };

    std::vector<Entidades::Personagens::Inimigo*> LIs;
    std::list<Entidades::Obstaculos::Obstaculo*> LOs;
    std::list<Entidades::Chao*> LCs;
    std::set<Entidades::Projeteis::Projetil*> LPs;
    Entidades::Personagens::Jogador* pJog1;
    Entidades::Personagens::Jogador* pJog2;
    Listas::ListaEntidades* pListaEntidades;

    bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
    ResultadoColisao detectarColisaoObstaculo(const sf::FloatRect& box, const sf::FloatRect& boxObs) const;
    bool haPlataformaEm(float x, float y) const;

    void resolverColisaoJogador(Entidades::Personagens::Jogador* jog, const sf::FloatRect& boxObs);
    ResultadoColisao resolverColisaoInimigo(Entidades::Personagens::Inimigo* ini, const sf::FloatRect& boxObs);

    void tratarColisoesJogObstacs(Entidades::Personagens::Jogador* jog);
    void tratarColisoesInimigosObstacs();
    void removerObstaculosDestruidos();
    void tratarColisoesJogInimigs(Entidades::Personagens::Jogador* jog);
    void tratarColisoesJogsProjeteis();

    bool projetilColidiu(Entidades::Projeteis::Projetil* p) const;
    bool tratarQuiqueProjetil(Entidades::Projeteis::Projetil* p);
    bool projetilColidiuComInimigo(Entidades::Projeteis::Projetil* p);
    bool projetilColidiuComJogador(Entidades::Projeteis::Projetil* p);
    bool projetilAtingiuJogador(Entidades::Projeteis::Projetil* p, Entidades::Personagens::Jogador* jog);
    void removerProjetil(std::set<Entidades::Projeteis::Projetil*>::iterator it);

    Gerenciador_Colisoes();

public:
    ~Gerenciador_Colisoes();

    static Gerenciador_Colisoes* getInstancia();

    void setJogador(Entidades::Personagens::Jogador* pJ) { pJog1 = pJ; }
    void setJogador2(Entidades::Personagens::Jogador* pJ) { pJog2 = pJ; }
    void setListaEntidades(Listas::ListaEntidades* pLE) { pListaEntidades = pLE; }

    void incluirInimigo(Entidades::Personagens::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
    void incluirChao(Entidades::Chao* pc);
    void incluirProjetil(Entidades::Projeteis::Projetil* pj);
    void limpar();

    const std::vector<Entidades::Personagens::Inimigo*>& getInimigos() const { return LIs; }

    void executar();
};

}
}

#endif
