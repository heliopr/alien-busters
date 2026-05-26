#ifndef GERENCIADOR_COLISOES_H
#define GERENCIADOR_COLISOES_H

#include <vector>
#include <list>
#include <set>

// Forward declarations
class Entidade;
class Jogador;
class Inimigo;
class Obstaculo;
class Projetil;

namespace Gerenciadores {

class Gerenciador_Colisoes {
private:
    std::vector<Inimigo*> Lis;
    std::list<Obstaculo*> LOs;
    std::set<Projetil*> LPs;
    Jogador* pJog1;

    const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimigs();
    void tratarColisoesJogsProjeteis();

public:
    Gerenciador_Colisoes();
    ~Gerenciador_Colisoes();

    void setJogador(Jogador* pJ);

    void incluirInimigo(Inimigo* pi);
    void incluirObstaculo(Obstaculo* po);
    void incluirProjetil(Projetil* pj);

    void executar();
};

}

#endif