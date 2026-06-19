#include "Gerenciadores/Gerenciador_Salvamento.h"
#include "Utilidades.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>

using AlienBusters::Utilidades;

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
    std::map<std::string, std::string> c = Utilidades::lerCampos(linha);
    if (c.find("nome1") == c.end()) {
        return false;
    }

    dados.nome1 = Utilidades::campoStr(c, "nome1");
    dados.nome2 = Utilidades::campoStr(c, "nome2");
    dados.numJogadores = Utilidades::campoInt(c, "jogadores", 1);
    dados.fase = Utilidades::campoInt(c, "fase");
    dados.pontos1 = Utilidades::campoInt(c, "pontos1");
    dados.pontos2 = Utilidades::campoInt(c, "pontos2");
    dados.vidas1 = Utilidades::campoInt(c, "vidas1", 3);
    dados.vidas2 = Utilidades::campoInt(c, "vidas2", 3);

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

        if (linha == "{") {
            DadosSalvos dados;
            std::string cabecalho;
            if (!std::getline(arquivo, cabecalho) || !parseCabecalho(cabecalho, dados)) {
                std::cerr << "Cabecalho invalido no salvamento: " << cabecalho << std::endl;
                continue;
            }

            std::string l;
            while (std::getline(arquivo, l) && l != "}") {
                if (l.empty()) {
                    continue;
                }
                if (l.compare(0, 9, "JOGADOR1 ") == 0) {
                    std::map<std::string, std::string> c = Utilidades::lerCampos(l.substr(9));
                    dados.x1 = Utilidades::campoFloat(c, "x");
                    dados.y1 = Utilidades::campoFloat(c, "y");
                    dados.vy1 = Utilidades::campoFloat(c, "vy");
                    dados.idJog1 = Utilidades::campoInt(c, "id", -1);
                } else if (l.compare(0, 9, "JOGADOR2 ") == 0) {
                    std::map<std::string, std::string> c = Utilidades::lerCampos(l.substr(9));
                    dados.x2 = Utilidades::campoFloat(c, "x");
                    dados.y2 = Utilidades::campoFloat(c, "y");
                    dados.vy2 = Utilidades::campoFloat(c, "vy");
                    dados.idJog2 = Utilidades::campoInt(c, "id", -1);
                } else if (l.compare(0, 9, "ENTIDADE ") == 0) {
                    dados.entidades.push_back(l.substr(9));
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

        arquivo << "{\n";
        arquivo << "nome1:" << d.nome1
            << ",nome2:" << d.nome2
            << ",jogadores:" << d.numJogadores
            << ",fase:" << d.fase
            << ",pontos1:" << d.pontos1
            << ",pontos2:" << d.pontos2
            << ",vidas1:" << d.vidas1
            << ",vidas2:" << d.vidas2 << "\n";

        arquivo << "JOGADOR1 id:" << d.idJog1 << ",x:" << d.x1 << ",y:" << d.y1 << ",vy:" << d.vy1 << "\n";
        if (d.numJogadores == 2) {
            arquivo << "JOGADOR2 id:" << d.idJog2 << ",x:" << d.x2 << ",y:" << d.y2 << ",vy:" << d.vy2 << "\n";
        }
        for (size_t j = 0; j < d.entidades.size(); ++j) {
            arquivo << "ENTIDADE " << d.entidades[j] << "\n";
        }

        arquivo << "}\n";
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
