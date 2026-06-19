#ifndef ENTE_H
#define ENTE_H

#include <SFML/Graphics.hpp>

namespace AlienBusters {

namespace Gerenciadores { class Gerenciador_Grafico; }

class Ente {
protected:
    int id;
    static int proximoId;
    static Gerenciadores::Gerenciador_Grafico *pGG;
    sf::RectangleShape *pFig;

public:
    Ente();
    virtual ~Ente();

    virtual void executar(float dt = 0.f) = 0;
    virtual void desenhar();

    int getId() const;
    void setId(int novoId);
    static int getProximoId();
    static void setProximoId(int id);

    sf::RectangleShape *getFigura() const;

    void static setGG(Gerenciadores::Gerenciador_Grafico *pG);
};

}

#endif