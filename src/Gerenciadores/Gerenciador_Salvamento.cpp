#include "Gerenciadores/Gerenciador_Salvamento.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace AlienBusters {
namespace Gerenciadores {

Gerenciador_Salvamento* Gerenciador_Salvamento::instancia = 0;

Gerenciador_Salvamento* Gerenciador_Salvamento::getInstancia() {
    if (instancia == 0) {
        instancia = new Gerenciador_Salvamento();
    }
    return instancia;
}

Gerenciador_Salvamento::Gerenciador_Salvamento(const std::string& caminho)
    : caminhoArquivo(caminho) {
    carregarSaves();
}

Gerenciador_Salvamento::~Gerenciador_Salvamento() {
}

void Gerenciador_Salvamento::carregarSaves() {
    saves.clear();

    std::ifstream arquivo(caminhoArquivo.c_str());
    if (!arquivo.is_open()) {
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        // Formato: nome1|nome2|numJogadores|fase|pontos1|pontos2|vidas1|vidas2
        std::vector<std::string> campos;
        std::stringstream ss(linha);
        std::string campo;
        while (std::getline(ss, campo, '|')) {
            campos.push_back(campo);
        }

        if (campos.size() != 8) {
            std::cerr << "Linha invalida no salvamento (campos): " << linha << std::endl;
            continue;
        }

        try {
            DadosSalvos dados;
            dados.nome1 = campos[0];
            dados.nome2 = campos[1];

            std::istringstream(campos[2]) >> dados.numJogadores;
            std::istringstream(campos[3]) >> dados.fase;
            std::istringstream(campos[4]) >> dados.pontos1;
            std::istringstream(campos[5]) >> dados.pontos2;
            std::istringstream(campos[6]) >> dados.vidas1;
            std::istringstream(campos[7]) >> dados.vidas2;

            if (dados.nome1.empty()) {
                throw std::invalid_argument("nome do jogador vazio");
            }

            saves.push_back(dados);
        } catch (const std::exception& e) {
            std::cerr << "Linha invalida no salvamento: (" << e.what() << ")" << std::endl;
            continue;
        }
    }

    arquivo.close();
}

void Gerenciador_Salvamento::escreverArquivo() {
    std::ofstream arquivo(caminhoArquivo.c_str());
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo de salvamento: " << caminhoArquivo << std::endl;
        return;
    }

    for (size_t i = 0; i < saves.size(); ++i) {
        arquivo << saves[i].nome1 << "|"
                << saves[i].nome2 << "|"
                << saves[i].numJogadores << "|"
                << saves[i].fase << "|"
                << saves[i].pontos1 << "|"
                << saves[i].pontos2 << "|"
                << saves[i].vidas1 << "|"
                << saves[i].vidas2 << "\n";
    }

    arquivo.close();
}

void Gerenciador_Salvamento::salvarJogo(const DadosSalvos& dados) {
    if (dados.nome1.empty()) {
        return;
    }

    // Atualiza o save existente do mesmo jogador, ou adiciona um novo.
    for (size_t i = 0; i < saves.size(); ++i) {
        if (saves[i].nome1 == dados.nome1) {
            saves[i] = dados;
            escreverArquivo();
            return;
        }
    }

    saves.push_back(dados);
    escreverArquivo();
}

void Gerenciador_Salvamento::removerJogo(const std::string& nome1) {
    for (size_t i = 0; i < saves.size(); ++i) {
        if (saves[i].nome1 == nome1) {
            saves.erase(saves.begin() + i);
            escreverArquivo();
            return;
        }
    }
}

bool Gerenciador_Salvamento::existeJogo(const std::string& nome1) const {
    for (size_t i = 0; i < saves.size(); ++i) {
        if (saves[i].nome1 == nome1) {
            return true;
        }
    }
    return false;
}

}
}
