#ifndef GERENCIADOR_GRAFICO_H
#define GERENCIADOR_GRAFICO_H

#include <SFML/Graphics.hpp>

namespace Gerenciadores {
    class Gerenciador_Grafico {
    private:
        sf::RenderWindow janela;

    public:
        Gerenciador_Grafico();
        ~Gerenciador_Grafico();

        bool estaAberto();
        void processarEventos();
        void renderizar();
        void mostrar();
    };
}

#endif