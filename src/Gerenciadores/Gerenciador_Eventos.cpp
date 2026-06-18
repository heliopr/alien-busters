#include "Gerenciadores/Gerenciador_Eventos.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

namespace AlienBusters {
namespace Gerenciadores {

Gerenciador_Eventos* Gerenciador_Eventos::instancia = 0;

Gerenciador_Eventos* Gerenciador_Eventos::getInstancia() {
    if (instancia == 0) {
        instancia = new Gerenciador_Eventos();
    }
    return instancia;
}

Gerenciador_Eventos::Gerenciador_Eventos() : observadores() {}

Gerenciador_Eventos::~Gerenciador_Eventos() {
    observadores.clear();
}

void Gerenciador_Eventos::inscrever(ObservadorEventos* observador) {
    if (observador == 0) {
        return;
    }

    // Evita inscrever o mesmo observador duas vezes.
    for (size_t i = 0; i < observadores.size(); ++i) {
        if (observadores[i] == observador) {
            return;
        }
    }

    observadores.push_back(observador);
}

void Gerenciador_Eventos::desinscrever(ObservadorEventos* observador) {
    for (size_t i = 0; i < observadores.size(); ++i) {
        if (observadores[i] == observador) {
            observadores.erase(observadores.begin() + i);
            return;
        }
    }
}

void Gerenciador_Eventos::notificar(const sf::Event& evento) {
    for (size_t i = 0; i < observadores.size(); ++i) {
        if (observadores[i] != 0) {
            observadores[i]->aoReceberEvento(evento);
        }
    }
}

void Gerenciador_Eventos::processar() {
    Gerenciador_Grafico* GG = Gerenciador_Grafico::getInstancia();

    sf::Event evento;
    while (GG->coletarEventos(evento)) {
        notificar(evento);
    }
}

}
}
