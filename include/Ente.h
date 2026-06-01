#ifndef ENTE_H
#define ENTE_H

#include <SFML/Graphics.hpp>

namespace Gerenciadores { class Gerenciador_Grafico; }

class Ente {
protected:
    int id;
    static Gerenciadores::Gerenciador_Grafico *pGrafico; 
    sf::RectangleShape *pFig;

public:
    Ente();
    virtual ~Ente();

    virtual void executar(float dt) = 0;
    virtual void desenhar();

    sf::RectangleShape *getFigura() const;

    void static setGG(Gerenciadores::Gerenciador_Grafico *pG);
};

#endif