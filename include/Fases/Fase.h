#ifndef FASE_H
#define FASE_H

#include "Ente.h"
#include "Listas/ListaEntidades.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Jogador.h"
#include <string>
#include <vector>

namespace AlienBusters {

namespace Entidades {
class Foguete;
}

namespace Fases {

class Fase : public Ente {
protected:
    Listas::ListaEntidades lista_ents;
    Gerenciadores::Gerenciador_Colisoes* pGC;
    Entidades::Personagens::Jogador* pJogador;
    Entidades::Personagens::Jogador* pJogador2;
    Entidades::Foguete* pFoguete;
    bool concluida;
    std::string nomeJogador;
    std::string nomeJogador2;
    bool gerarConteudo;

public:
    enum CategoriaEntidade {
        CAT_OUTRO = 0,
        CAT_CHAO,
        CAT_OBSTACULO,
        CAT_INIMIGO,
        CAT_FOGUETE,
        CAT_PROJETIL
    };

    Fase(Entidades::Personagens::Jogador* pJogador,
         Entidades::Personagens::Jogador* pJogador2 = 0,
         const std::string& nome1 = "", const std::string& nome2 = "",
         bool gerarConteudo = true);
    virtual ~Fase();

    virtual void executar(float dt);
    virtual void desenhar();
    virtual void reiniciar();
    bool jogadorPerdeu() const;
    bool faseConcluida() const { return concluida; }

    // Serializa todas as entidades vivas da fase (cenario, inimigos,
    // obstaculos, foguete e projeteis) em linhas de texto.
    void montarSnapshot(std::vector<std::string>& linhas) const;

    // Recria as entidades a partir das linhas salvas, registrando-as nos
    // gerenciadores apropriados. Usado ao continuar um jogo salvo.
    void carregarSnapshot(const std::vector<std::string>& linhas);

protected:
    void processarJogador(Entidades::Personagens::Jogador* pJog, float dt);
    void processarInimigos(float dt);
    void verificarFoguete();
    std::vector<sf::Vector2f> sortearPosicoes(const float posicoes[][2], int total, int minimo, int maximo) const;
    Entidades::Personagens::Jogador* jogadorMaisProximo(float x, float y) const;
    void atualizarCamera();
    Entidades::Entidade* criarEntidadeDeLinha(const std::string& linha, int& categoria) const;
    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;
    virtual void criarFoguete();
    virtual void criarCenario();
    void criarCenario(const sf::Color& cor);
    virtual void criarSlimes() = 0;
};

}
}

#endif
