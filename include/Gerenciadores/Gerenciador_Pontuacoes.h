#ifndef GERENCIADOR_PONTUACOES_H
#define GERENCIADOR_PONTUACOES_H

#include <string>
#include <vector>
#include <SFML/System.hpp>

namespace AlienBusters {
namespace Gerenciadores {

struct EntradaPontuacao {
    std::string nome;
    int pontos;
    std::string data;

    EntradaPontuacao(const std::string& n = "", int p = 0, const std::string& d = "");
};

class Gerenciador_Pontuacoes {
private:
    static Gerenciador_Pontuacoes* instancia;

    std::vector<EntradaPontuacao> ranking;
    std::string caminhoArquivo;
    static const int MAX_RANKING = 10;

    mutable sf::Mutex mutex;
    sf::Thread* threadRecarga;

    void carregarRanking();
    void salvarRanking();
    std::string obterDataAtual();

    Gerenciador_Pontuacoes(const std::string& caminho = "ranking.txt");

public:
    ~Gerenciador_Pontuacoes();

    static Gerenciador_Pontuacoes* getInstancia();

    void adicionarPontuacao(const std::string& nome, int pontos);
    std::vector<EntradaPontuacao> getRankingTop(int quantidade = MAX_RANKING) const;
    
    void recarregarRankingAsync();

    bool ehNovaAlta(int pontos) const;
};

}
}

#endif
