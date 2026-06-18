#ifndef ATIRADOR_H
#define ATIRADOR_H

namespace AlienBusters {
namespace Entidades {

class Atirador {
protected:
    float tempoRestante;

    void atualizarRecarga(float dt);
    bool podeAtirar() const;
    void reiniciarRecarga(float tempo);

public:
    Atirador();
    virtual ~Atirador();
};

}
}

#endif
