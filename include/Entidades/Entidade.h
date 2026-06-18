#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "Ente.h"
#include "Configuracao.h"
#include <sstream>
#include <string>

namespace AlienBusters {
namespace Entidades {

class Entidade : public Ente {
protected:
    float x;
    float y;
    float vy;

    std::ostringstream buffer;
    void salvarDataBuffer();

    void aplicarGravidade(float dt, float gravidade = Config::GRAVIDADE);
    void contrariarGravidade(float dt);

public:
    Entidade();
    virtual ~Entidade();

public:
    virtual void executar(float dt) = 0;
    virtual void salvar() = 0;
    virtual void desenhar();

    // Serializa a entidade em uma unica linha de texto para o salvamento.
    // Entidades persistentes sobrescrevem este metodo; as transitorias
    // (ex.: Explosao) retornam "" e sao ignoradas no salvamento.
    virtual std::string serializar() const { return ""; }

    virtual bool finalizada() const { return false; }

    float getX() const;
    float getY() const;
    void setX(float novoX);
    void setY(float novoY);
    float getVy() const;
    void setVy(float v);
    virtual sf::FloatRect getHitbox() const = 0;
};

}
}

#endif