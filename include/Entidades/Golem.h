#ifndef GOLEM_H
#define GOLEM_H

#include "Entidades/Inimigo.h"
#include "Entidades/Atirador.h"
#include <SFML/Graphics.hpp>

namespace AlienBusters {
namespace Entidades {
namespace Personagens {

class Golem : public Inimigo, public Atirador {
private:
    float tempoRecarga; // [3, 5]

public:
    Golem(float x = 400.f, float y = 300.f);
    ~Golem();

    void executar(float dt);
    void salvar();
    std::string serializar() const;
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;

    void atirar(Jogador* alvo, float dt);
};

}
}
}

#endif
