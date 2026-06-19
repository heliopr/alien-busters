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
    float tempoRecarga;

public:
    Golem(float x = 400.f, float y = 300.f);
    ~Golem();

    void executar(float dt = 0.f);
    void salvar();
    void danificar(Jogador* p);
    sf::FloatRect getHitbox() const;

    float getTempoRecarga() const { return tempoRecarga; }
    void setTempoRecarga(float t) { tempoRecarga = t; }

    void atirar(Jogador* alvo, float dt);
};

}
}
}

#endif
