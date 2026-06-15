#include "Gerenciadores/Gerenciador_Pontuacoes.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <sstream>

namespace Gerenciadores {

// Comparador para ordenar pontuações
bool compararPontuacoes(const EntradaPontuacao& a, const EntradaPontuacao& b) {
    return a.pontos > b.pontos;
}

Gerenciador_Pontuacoes::Gerenciador_Pontuacoes(const std::string& caminho)
    : caminhoArquivo(caminho) {
    carregarRanking();
}

Gerenciador_Pontuacoes::~Gerenciador_Pontuacoes() {
}

std::string Gerenciador_Pontuacoes::obterDataAtual() {
    time_t agora = time(0);
    struct tm* dataLocal = localtime(&agora);

    std::stringstream ss;
    ss << (dataLocal->tm_mday < 10 ? "0" : "")
       << dataLocal->tm_mday << "/"
       << (dataLocal->tm_mon + 1 < 10 ? "0" : "")
       << (dataLocal->tm_mon + 1) << "/"
       << (1900 + dataLocal->tm_year);

    return ss.str();
}

void Gerenciador_Pontuacoes::carregarRanking() {
    ranking.clear();

    std::ifstream arquivo(caminhoArquivo.c_str());
    if (!arquivo.is_open()) {
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        size_t pos1 = linha.find('|');
        if (pos1 == std::string::npos) continue;

        std::string nome = linha.substr(0, pos1);

        size_t pos2 = linha.find('|', pos1 + 1);
        if (pos2 == std::string::npos) continue;

        std::string pontosStr = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string data = linha.substr(pos2 + 1);

        int pontos = 0;
        std::istringstream iss(pontosStr);
        iss >> pontos;

        ranking.push_back(EntradaPontuacao(nome, pontos, data));
    }

    arquivo.close();

    // Ordenar por pontos decrescentes
    std::sort(ranking.begin(), ranking.end(), compararPontuacoes);
}

void Gerenciador_Pontuacoes::salvarRanking() {
    std::ofstream arquivo(caminhoArquivo.c_str());
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de ranking: " << caminhoArquivo << std::endl;
        return;
    }

    for (size_t i = 0; i < ranking.size(); ++i) {
        arquivo << ranking[i].nome << "|"
                << ranking[i].pontos << "|"
                << ranking[i].data << "\n";
    }

    arquivo.close();
}

void Gerenciador_Pontuacoes::adicionarPontuacao(const std::string& nome, int pontos) {
    if (nome.empty() || pontos <= 0) {
        return;
    }

    ranking.push_back(EntradaPontuacao(nome, pontos, obterDataAtual()));

    // Ordenar por pontos decrescentes
    std::sort(ranking.begin(), ranking.end(), compararPontuacoes);

    // Manter apenas os top MAX_RANKING
    if (ranking.size() > (size_t)MAX_RANKING) {
        ranking.erase(ranking.begin() + MAX_RANKING, ranking.end());
    }

    salvarRanking();
}

std::vector<EntradaPontuacao> Gerenciador_Pontuacoes::getRankingTop(int quantidade) const {
    std::vector<EntradaPontuacao> top;
    for (int i = 0; i < quantidade && i < (int)ranking.size(); ++i) {
        top.push_back(ranking[i]);
    }
    return top;
}

bool Gerenciador_Pontuacoes::ehNovaAlta(int pontos) const {
    if (ranking.size() < (size_t)MAX_RANKING) {
        return true;
    }
    return pontos > ranking.back().pontos;
}

}
