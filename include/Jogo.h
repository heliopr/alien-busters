#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Pontuacoes.h"
#include "Fases/Fase_Lua.h"
#include "Fases/Fase_Marte.h"
#include "Menu.h"
#include "TelaMorte.h"
#include "TelaVitoria.h"

class Jogo {
private:
    enum Estado {
        ESTADO_MENU,
        ESTADO_JOGANDO,
        ESTADO_TELA_MORTE,
        ESTADO_TELA_VITORIA
    };
    
    enum OpcaoMenu {
        OPCAO_1JOGADOR = 0,
        OPCAO_FASES,
        OPCAO_RANKING,
        OPCAO_SAIR
    };

    enum OpcaoFase {
        FASE_LUA = 0,
        FASE_MARTE,
        FASE_VOLTAR
    };

    static Jogo* instancia;

    Fases::Fase* faseAtual;
    Entidades::Personagens::Jogador* pJog1;
    Entidades::Personagens::Jogador* pJog2;
    Menu menu;
    TelaMorte telaMorte;
    TelaVitoria telaVitoria;
    Estado estado;
    std::string nomeJogadorAtual;
    std::string nomeJogador2Atual;
    int faseSelecionada;
    int faseEmAndamento;
    bool doisJogadoresAtual;
    bool pontuacaoSalva;

    Jogo();

    void processarEventos();
    void atualizarEDesenhar(float dt);

    void tratarEventoTelaMorte(const sf::Event& evento);
    void tratarEventoTelaVitoria(const sf::Event& evento);
    void tratarEventoEntradaNome(const sf::Event& evento);
    void tratarEventoEntradaNomeJ2(const sf::Event& evento);
    void tratarEventoMenu(const sf::Event& evento);

    void iniciarFase(int fase, bool doisJogadores);
    void avancarFase();
    void voltarAoMenu();
    void salvarPontuacoes();

public:
    ~Jogo();

    static Jogo* getInstancia();

    void executar();
    void setNomeJogador(const std::string& nome) { nomeJogadorAtual = nome; }
};

#endif