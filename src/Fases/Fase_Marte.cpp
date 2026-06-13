#include "Fases/Fase_Marte.h"
#include "Entidades/Plataforma.h"
#include "Entidades/Chao.h"
#include "Entidades/Slime.h"
#include "Entidades/MinaExtraterrestre.h"
#include "Entidades/Demonio.h"
#include <cstdlib>
#include <ctime>

namespace Fases {

Fase_Marte::Fase_Marte(Entidades::Personagens::Jogador* pJogador, Entidades::Personagens::Jogador* pJogador2) : Fase(pJogador, pJogador2) {
    criarCenario();
    criarObstaculos();
    criarInimigos();
}

Fase_Marte::~Fase_Marte() {
}

void Fase_Marte::criarInimigos() {
    criarSlimes();
    criarDemonios();
}

void Fase_Marte::criarObstaculos() {
    struct plataforma { float x, y; };

    static const plataforma plataformas[] = {
        {250.f,  580.f},
        {420.f,  500.f},
        {580.f,  420.f},
        {150.f,  460.f},
        {320.f,  380.f},
        {480.f,  300.f},
        {720.f,  440.f},
        {1300.f, 360.f},
        {1550.f, 460.f},
        {1900.f, 480.f},
        {2050.f, 380.f},
        {2200.f, 280.f}
    };
    const int totalPlataformas = sizeof(plataformas) / sizeof(plataformas[0]);
    const int minimoPlataformas = 3;

    static bool sementeInicializada = false;
    if (!sementeInicializada) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        sementeInicializada = true;
    }

    int indices[totalPlataformas];
    for (int i = 0; i < totalPlataformas; ++i) {
        indices[i] = i;
    }
    for (int i = totalPlataformas - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    int quantidade = minimoPlataformas + (std::rand() % (totalPlataformas - minimoPlataformas + 1));

    for (int i = 0; i < quantidade; ++i) {
        const plataforma& d = plataformas[indices[i]];
        Entidades::Obstaculos::Plataforma* p = new Entidades::Obstaculos::Plataforma(d.x, d.y);
        GC.incluirObstaculo(p);
        lista_ents.incluir(p);
    }

    Entidades::Obstaculos::Chao* parede1 = new Entidades::Obstaculos::Chao(980.f, 600.f, 120.f, 80.f);
    Entidades::Obstaculos::Chao* parede2 = new Entidades::Obstaculos::Chao(2500.f, 300.f, 400.f, 600.f);
    GC.incluirObstaculo(parede1);
    GC.incluirObstaculo(parede2);
    lista_ents.incluir(parede1);
    lista_ents.incluir(parede2);

    criarMinasExtraterrestres();
}

void Fase_Marte::criarDemonios() {
    Entidades::Personagens::Demonio* inimigo1 = new Entidades::Personagens::Demonio(800.f, 300.f);
    lista_ents.incluir(inimigo1);
    GC.incluirInimigo(inimigo1);

    Entidades::Personagens::Demonio* inimigo2 = new Entidades::Personagens::Demonio(2000.f, 350.f);
    lista_ents.incluir(inimigo2);
    GC.incluirInimigo(inimigo2);
}

void Fase_Marte::criarMinasExtraterrestres() {
    static const float posicoes[][2] = {
        { 500.f, 660.f},
        {1130.f, 660.f},
        {1600.f, 660.f},
        {1980.f, 660.f},
        {2300.f, 660.f}
    };
    const int total  = sizeof(posicoes) / sizeof(posicoes[0]);
    const int minimo = 3;

    int indices[total];
    for (int i = 0; i < total; ++i) indices[i] = i;
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = indices[i]; indices[i] = indices[j]; indices[j] = tmp;
    }

    int quantidade = minimo + std::rand() % (total - minimo + 1);
    for (int i = 0; i < quantidade; ++i) {
        Entidades::Obstaculos::MinaExtraterrestre* od = new Entidades::Obstaculos::MinaExtraterrestre(posicoes[indices[i]][0], posicoes[indices[i]][1]);
        GC.incluirObstaculoDificil(od);
        lista_ents.incluir(od);
    }
}
void Fase_Marte::criarSlimes() {
    static const float posicoes[][2] = {
        { 500.f, 400.f},
        { 600.f, 300.f},
        { 850.f, 300.f},
        {1200.f, 350.f},
        {1600.f, 300.f},
        {2000.f, 400.f},
        {2400.f, 300.f}
    };
    const int total   = sizeof(posicoes) / sizeof(posicoes[0]);
    const int minimo  = 3;

    int indices[total];
    for (int i = 0; i < total; ++i) indices[i] = i;
    for (int i = total - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = indices[i]; indices[i] = indices[j]; indices[j] = tmp;
    }

    int quantidade = minimo + std::rand() % (total - minimo + 1);
    for (int i = 0; i < quantidade; ++i) {
        Entidades::Personagens::Slime* s = new Entidades::Personagens::Slime(posicoes[indices[i]][0], posicoes[indices[i]][1]);
        lista_ents.incluir(s);
        GC.incluirInimigo(s);
    }
}

}

