#include "Gerenciadores/Gerenciador_Pontuacoes.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <sstream>
#include <stdexcept>

namespace AlienBusters {
namespace Gerenciadores {

EntradaPontuacao::EntradaPontuacao(const std::string& n, int p, const std::string& d)
    : nome(n), pontos(p), data(d) {
}

bool compararPontuacoes(const EntradaPontuacao& a, const EntradaPontuacao& b) {
    return a.pontos > b.pontos;
}

Gerenciador_Pontuacoes* Gerenciador_Pontuacoes::instancia = 0;

Gerenciador_Pontuacoes* Gerenciador_Pontuacoes::getInstancia() {
    if (instancia == 0) {
        instancia = new Gerenciador_Pontuacoes();
    }
    return instancia;
}

Gerenciador_Pontuacoes::Gerenciador_Pontuacoes(const std::string& caminho)
    : caminhoArquivo(caminho), threadRecarga(0) {
    carregarRanking();
}

Gerenciador_Pontuacoes::~Gerenciador_Pontuacoes() {
    if (threadRecarga != 0) {
        threadRecarga->wait();
        delete threadRecarga;
        threadRecarga = 0;
    }
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
    std::vector<EntradaPontuacao> novoRanking;

    std::ifstream arquivo(caminhoArquivo.c_str());
    if (arquivo.is_open()) {
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

            try {
                int pontos = 0;
                std::istringstream iss(pontosStr);
                if (!(iss >> pontos) || !(iss >> std::ws).eof()) {
                    throw std::invalid_argument("pontuacao invalida: " + pontosStr);
                }
                novoRanking.push_back(EntradaPontuacao(nome, pontos, data));
            } catch (const std::exception& e) {
                std::cerr << "Linha invalida no ranking: " << "(" << e.what() << ")" << std::endl;
                continue;
            }
        }

        arquivo.close();

        std::sort(novoRanking.begin(), novoRanking.end(), compararPontuacoes);
    }

    sf::Lock lock(mutex);
    ranking.swap(novoRanking);
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

    sf::Lock lock(mutex);

    ranking.push_back(EntradaPontuacao(nome, pontos, obterDataAtual()));

    std::sort(ranking.begin(), ranking.end(), compararPontuacoes);

    if (ranking.size() > (size_t)MAX_RANKING) {
        ranking.erase(ranking.begin() + MAX_RANKING, ranking.end());
    }

    salvarRanking();
}

std::vector<EntradaPontuacao> Gerenciador_Pontuacoes::getRankingTop(int quantidade) const {
    sf::Lock lock(mutex);

    std::vector<EntradaPontuacao> top;
    for (int i = 0; i < quantidade && i < (int)ranking.size(); ++i) {
        top.push_back(ranking[i]);
    }
    return top;
}

void Gerenciador_Pontuacoes::recarregarRankingAsync() {
    if (threadRecarga != 0) {
        threadRecarga->wait();
        delete threadRecarga;
        threadRecarga = 0;
    }

    threadRecarga = new sf::Thread(&Gerenciador_Pontuacoes::carregarRanking, this);
    threadRecarga->launch();
}

bool Gerenciador_Pontuacoes::ehNovaAlta(int pontos) const {
    sf::Lock lock(mutex);

    if (ranking.size() < (size_t)MAX_RANKING) {
        return true;
    }
    return pontos > ranking.back().pontos;
}

}
}
