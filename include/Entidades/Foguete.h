#ifndef FOGUETE_H
#define FOGUETE_H

#include "Entidades/Entidade.h"
#include <SFML/Graphics.hpp>

namespace AlienBusters {
namespace Entidades {

class Foguete : public Entidade {
private:
    static const float LARGURA;
    static const float ALTURA;

    sf::Texture textura;

public:
    Foguete(float x, float y);
    ~Foguete();

    void executar(float dt);
    void salvar();
    std::string serializar() const;
    sf::FloatRect getHitbox() const;
};

}
}

#endif
