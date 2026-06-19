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

bool Gerenciador_Salvamento::parseCabecalho(const std::string& linha, DadosSalvos& dados) {
    // Formato: nome1|nome2|numJogadores|fase|pontos1|pontos2|vidas1|vidas2
    std::vector<std::string> campos;
    std::stringstream ss(linha);
    std::string campo;
    while (std::getline(ss, campo, '|')) {
        campos.push_back(campo);
    }

    if (campos.size() != 8) {
        return false;
    }

    dados.nome1 = campos[0];
    dados.nome2 = campos[1];
    std::istringstream(campos[2]) >> dados.numJogadores;
    std::istringstream(campos[3]) >> dados.fase;
    std::istringstream(campos[4]) >> dados.pontos1;
    std::istringstream(campos[5]) >> dados.pontos2;
    std::istringstream(campos[6]) >> dados.vidas1;
    std::istringstream(campos[7]) >> dados.vidas2;

    return !dados.nome1.empty();
}

void Gerenciador_Salvamento::carregarSaves() {
    saves.clear();

    std::ifstream arquivo(caminhoArquivo.c_str());
    if (!arquivo.is_open()) {
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) {
            continue;
        }

        if (linha == "SAVE") {
            DadosSalvos dados;
            std::string cabecalho;
            if (!std::getline(arquivo, cabecalho) || !parseCabecalho(cabecalho, dados)) {
                std::cerr << "Cabecalho invalido no salvamento: " << cabecalho << std::endl;
                continue;
            }

            std::string l;
            while (std::getline(arquivo, l) && l != "ENDSAVE") {
                if (l.empty()) {
                    continue;
                }
                if (l.compare(0, 5, "JOG1 ") == 0) {
                    std::istringstream(l.substr(5)) >> dados.x1 >> dados.y1 >> dados.vy1;
                } else if (l.compare(0, 5, "JOG2 ") == 0) {
                    std::istringstream(l.substr(5)) >> dados.x2 >> dados.y2 >> dados.vy2;
                } else if (l.compare(0, 4, "ENT ") == 0) {
                    dados.entidades.push_back(l.substr(4));
                }
            }

            saves.push_back(dados);
        } else {
            DadosSalvos dados;
            if (parseCabecalho(linha, dados)) {
                saves.push_back(dados);
            } else {
                std::cerr << "Linha invalida no salvamento: " << linha << std::endl;
            }
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
        const DadosSalvos& d = saves[i];

        arquivo << "SAVE\n";
        arquivo << d.nome1 << "|"
            << d.nome2 << "|"
            << d.numJogadores << "|"
            << d.fase << "|"
            << d.pontos1 << "|"
            << d.pontos2 << "|"
            << d.vidas1 << "|"
            << d.vidas2 << "\n";

        arquivo << "JOG1 " << d.x1 << " " << d.y1 << " " << d.vy1 << "\n";
        if (d.numJogadores == 2) {
            arquivo << "JOG2 " << d.x2 << " " << d.y2 << " " << d.vy2 << "\n";
        }
        for (size_t j = 0; j < d.entidades.size(); ++j) {
            arquivo << "ENT " << d.entidades[j] << "\n";
        }

        arquivo << "ENDSAVE\n";
    }

    arquivo.close();
}

void Gerenciador_Salvamento::salvarJogo(const DadosSalvos& dados) {
    if (dados.nome1.empty()) {
        return;
    }

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
