#ifndef GERENCIADOR_SALVAMENTO_H
#define GERENCIADOR_SALVAMENTO_H

#include <string>
#include <vector>

namespace AlienBusters {
namespace Gerenciadores {

struct DadosSalvos {
    std::string nome1;
    std::string nome2;
    int numJogadores;
    int fase;
    int pontos1;
    int pontos2;
    int vidas1;
    int vidas2;

    float x1, y1, vy1;
    int idJog1;
    float x2, y2, vy2;
    int idJog2;
    std::vector<std::string> entidades;

    DadosSalvos() : nome1(""), nome2(""), numJogadores(1), fase(0),
        pontos1(0), pontos2(0), vidas1(3), vidas2(3),
        x1(0.f), y1(0.f), vy1(0.f), idJog1(-1),
        x2(0.f), y2(0.f), vy2(0.f), idJog2(-1), entidades() {

    }
};

class Gerenciador_Salvamento {
private:
    static Gerenciador_Salvamento* instancia;

    std::vector<DadosSalvos> saves;
    std::string caminhoArquivo;

    void carregarSaves();
    void escreverArquivo();
    static bool parseCabecalho(const std::string& linha, DadosSalvos& dados);

    Gerenciador_Salvamento(const std::string& caminho = "saves.txt");

public:
    ~Gerenciador_Salvamento();

    static Gerenciador_Salvamento* getInstancia();

    void salvarJogo(const DadosSalvos& dados);
    void removerJogo(const std::string& nome1);

    bool existeJogo(const std::string& nome1) const;
    const std::vector<DadosSalvos>& getSaves() const { return saves; }
};

}
}

#endif
