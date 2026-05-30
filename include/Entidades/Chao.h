#ifndef CHAO_H
#define CHAO_H

#include "Entidades/Entidade.h"

namespace Entidades {

class Chao : public Entidade {
private:
    float largura;
    float altura;
    sf::Texture texturaChao;

public:
    Chao(float posX, float posY, float larg, float alt);
    ~Chao();

    void executar(float dt);
    void salvar();
    sf::FloatRect getLimitesColisao() const;
};

}

#endif