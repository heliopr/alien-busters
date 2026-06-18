#ifndef OBSERVADOR_EVENTOS_H
#define OBSERVADOR_EVENTOS_H

#include <SFML/Window/Event.hpp>

namespace AlienBusters {
namespace Gerenciadores {

// Interface do padrao Observer: qualquer classe que queira reagir aos
// eventos de entrada (teclado, fechamento de janela, etc.) deve herdar
// desta interface e inscrever-se no Gerenciador_Eventos.
class ObservadorEventos {
public:
    virtual ~ObservadorEventos() {}

    // Chamado pelo Gerenciador_Eventos (Subject) para cada evento coletado.
    virtual void aoReceberEvento(const sf::Event& evento) = 0;
};

}
}

#endif
