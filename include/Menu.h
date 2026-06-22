#ifndef MENU_H
#define MENU_H

#include "Ente.h"
#include "Gerenciadores/Gerenciador_Pontuacoes.h"
#include "Gerenciadores/Gerenciador_Salvamento.h"
#include <vector>
#include <string>

namespace AlienBusters {

class Jogo;

class Menu : public Ente {
private:
    enum TelaMenu {
        TELA_PRINCIPAL,
        TELA_ENTRADA_NOME,
        TELA_ENTRADA_NOME_J2,
        TELA_RANKING,
        TELA_NOVO_JOGO,
        TELA_CONTINUAR
    };

    Jogo* pJog;
    int opcaoSelecionada;
    int opcaoNovoJogoSelecionada;
    int opcaoContinuarSelecionada;
    int numJogadores;
    bool emSubmenu;
    TelaMenu telaAtual;

    std::string nomeJogador;
    std::string nomeJogador2;

    std::vector<sf::Text> opcoes;
    std::vector<sf::Text> opcoesNovoJogo;
    std::vector<sf::Text> textoRanking;
    std::vector<sf::Text> opcoesContinuar;
    std::vector<Gerenciadores::DadosSalvos> saves;

    sf::Font fonte;
    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;
    sf::Text textoCursor;
    sf::Text textoTitulo;

    void criarTextos(std::vector<sf::Text>& lista, std::string nomes[], int total, float yInicio);
    void atualizarTextoJogadores();
    void gerarTextoRanking();
    void atualizarCoresContinuar();

public:
    Menu(Jogo* pJ = 0);
    virtual ~Menu();

    void subirOpcao();
    void descerOpcao();
    void entrarSubmenu();
    void sairSubmenu();
    void alternarJogadores();
    void entrarTelaNome();
    void irParaNomeJogador2();
    void adicionarLetraAoNome(sf::Uint32 unicode);
    void removerLetraDoNome();
    void confirmarNome();
    void confirmarNomeJ2();
    void voltarDaTelaNome();
    void voltarDoRanking();
    void entrarTelaContinuar();
    void resetarMenu();

    bool getEmSubmenu() const;
    bool emTelaEntradaNome() const;
    bool emTelaEntradaNomeJ2() const;
    bool emTelaRanking() const;
    bool emTelaNovoJogo() const;
    bool emTelaContinuar() const;
    int getOpcaoSelecionada() const;
    int getOpcaoNovoJogoSelecionada() const;
    int getOpcaoContinuarSelecionada() const;
    int getNumSaves() const;
    const Gerenciadores::DadosSalvos& getSaveSelecionado() const;
    int getNumJogadores() const;
    std::string getNomeJogador() const;
    std::string getNomeJogador2() const;

    void executar(float dt = 0.f);
    void desenhar();
};

}

#endif
