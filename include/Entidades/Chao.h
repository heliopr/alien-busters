#ifndef CHAO_H
#define CHAO_H

#include "Entidade.h"

namespace Entidades {

class Chao : public Entidade {
private:
    float altura;
    float largura;

public:
    Chao(float x, float y, float largura, float altura);
    ~Chao();

    void executar(float dt);
    void salvar();
    sf::FloatRect getLimitesColisao() const;
};

}

#endif