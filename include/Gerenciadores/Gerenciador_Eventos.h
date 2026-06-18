#ifndef GERENCIADOR_EVENTOS_H
#define GERENCIADOR_EVENTOS_H

#include "Gerenciadores/ObservadorEventos.h"
#include <vector>

namespace AlienBusters {
namespace Gerenciadores {

// Subject do padrao Observer. Coleta os eventos do SFML (atraves do
// Gerenciador_Grafico) e os repassa a todos os observadores inscritos.
class Gerenciador_Eventos {
private:
    static Gerenciador_Eventos* instancia;

    std::vector<ObservadorEventos*> observadores;

    Gerenciador_Eventos();

public:
    ~Gerenciador_Eventos();

    static Gerenciador_Eventos* getInstancia();

    void inscrever(ObservadorEventos* observador);
    void desinscrever(ObservadorEventos* observador);

    // Repassa um unico evento para todos os observadores inscritos.
    void notificar(const sf::Event& evento);

    // Coleta todos os eventos pendentes da janela e os notifica.
    void processar();
};

}
}

#endif
