#ifndef JOGO_H
#define JOGO_H

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Pontuacoes.h"
#include "Gerenciadores/Gerenciador_Salvamento.h"
#include "Gerenciadores/Gerenciador_Eventos.h"
#include "Gerenciadores/ObservadorEventos.h"
#include "Fases/Fase_Lua.h"
#include "Fases/Fase_Marte.h"
#include "Menu.h"
#include "TelaMorte.h"
#include "TelaVitoria.h"
#include "TelaPause.h"

namespace AlienBusters {

class Jogo : public Gerenciadores::ObservadorEventos {
private:
    enum Estado {
        ESTADO_MENU,
        ESTADO_JOGANDO,
        ESTADO_PAUSE,
        ESTADO_TELA_MORTE,
        ESTADO_TELA_VITORIA
    };
    
    enum OpcaoMenu {
        OPCAO_NOVO_JOGO = 0,
        OPCAO_CONTINUAR,
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
    TelaPause telaPause;
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
    void tratarEvento(const sf::Event& evento);

    void tratarEventoTelaMorte(const sf::Event& evento);
    void tratarEventoTelaVitoria(const sf::Event& evento);
    void tratarEventoPause(const sf::Event& evento);
    void tratarEventoEntradaNome(const sf::Event& evento);
    void tratarEventoEntradaNomeJ2(const sf::Event& evento);
    void tratarEventoMenu(const sf::Event& evento);

    void iniciarFase(int fase, bool doisJogadores,
                     int pontos1 = 0, int pontos2 = 0, int vidas1 = 3, int vidas2 = 3);
    void avancarFase();
    void voltarAoMenu();
    void salvarPontuacoes();
    void salvarProgresso();
    void salvarEstadoCompleto();
    void iniciarFaseSnapshot(const Gerenciadores::DadosSalvos& dados);
    void continuarJogo(const Gerenciadores::DadosSalvos& dados);

public:
    ~Jogo();

    static Jogo* getInstancia();

    void executar();
    void setNomeJogador(const std::string& nome) { nomeJogadorAtual = nome; }

    // ObservadorEventos: recebe cada evento repassado pelo Gerenciador_Eventos.
    void aoReceberEvento(const sf::Event& evento);
};

}

#endif