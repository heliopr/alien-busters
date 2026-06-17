#ifndef GERENCIADOR_PONTUACOES_H
#define GERENCIADOR_PONTUACOES_H

#include <string>
#include <vector>

namespace Gerenciadores {

struct EntradaPontuacao {
    std::string nome;
    int pontos;
    std::string data;

    EntradaPontuacao(const std::string& n = "", int p = 0, const std::string& d = "")
        : nome(n), pontos(p), data(d) {}
};

class Gerenciador_Pontuacoes {
private:
    static Gerenciador_Pontuacoes* instancia;

    std::vector<EntradaPontuacao> ranking;
    std::string caminhoArquivo;
    static const int MAX_RANKING = 10;

    void carregarRanking();
    void salvarRanking();
    std::string obterDataAtual();

    Gerenciador_Pontuacoes(const std::string& caminho = "ranking.dat");

public:
    ~Gerenciador_Pontuacoes();

    static Gerenciador_Pontuacoes* getInstancia();

    void adicionarPontuacao(const std::string& nome, int pontos);
    const std::vector<EntradaPontuacao>& getRanking() const { return ranking; }
    std::vector<EntradaPontuacao> getRankingTop(int quantidade = MAX_RANKING) const;

    bool ehNovaAlta(int pontos) const;
};

}

#endif
