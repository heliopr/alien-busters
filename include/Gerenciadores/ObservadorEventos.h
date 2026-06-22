#ifndef OBSERVADOR_EVENTOS_H
#define OBSERVADOR_EVENTOS_H

#include <SFML/Window/Event.hpp>

namespace AlienBusters {
namespace Gerenciadores {

class ObservadorEventos {
public:
    virtual ~ObservadorEventos();

    virtual void aoReceberEvento(const sf::Event& evento) = 0;
};

}
}

#endif
