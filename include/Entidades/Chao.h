#ifndef CHAO_H
#define CHAO_H

#include "Entidades/Entidade.h"

namespace AlienBusters {
namespace Entidades {

class Chao : public Entidade {
private:
    float altura;
    float largura;

public:
    Chao(float x, float y, float largura, float altura, sf::Color cor = sf::Color(145, 60, 25));
    ~Chao();

    void executar(float dt);
    void salvar();
    sf::FloatRect getHitbox() const;
};

}
}

#endif
