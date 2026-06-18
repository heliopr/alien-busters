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

    bool getEmSubmenu() const { return emSubmenu; }
    bool emTelaEntradaNome() const { return telaAtual == TELA_ENTRADA_NOME; }
    bool emTelaEntradaNomeJ2() const { return telaAtual == TELA_ENTRADA_NOME_J2; }
    bool emTelaRanking() const { return telaAtual == TELA_RANKING; }
    bool emTelaNovoJogo() const { return telaAtual == TELA_NOVO_JOGO; }
    bool emTelaContinuar() const { return telaAtual == TELA_CONTINUAR; }
    int getOpcaoSelecionada() const { return opcaoSelecionada; }
    int getOpcaoNovoJogoSelecionada() const { return opcaoNovoJogoSelecionada; }
    int getOpcaoContinuarSelecionada() const { return opcaoContinuarSelecionada; }
    int getNumSaves() const { return (int)saves.size(); }
    const Gerenciadores::DadosSalvos& getSaveSelecionado() const { return saves[opcaoContinuarSelecionada]; }
    int getNumJogadores() const { return numJogadores; }
    std::string getNomeJogador() const { return nomeJogador; }
    std::string getNomeJogador2() const { return nomeJogador2; }

    void executar(float dt = 0.f);
    void desenhar();
};

}

#endif
