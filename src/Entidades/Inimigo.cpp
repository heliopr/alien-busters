#include "Entidades/Inimigo.h"
#include "Entidades/Jogador.h"
#include "Configuracao.h"
#include <cstddef>
#include <iostream>

namespace Entidades {
namespace Personagens {

sf::SoundBuffer Inimigo::bufferDano;
sf::Sound Inimigo::somDano;
bool Inimigo::somCarregado = false;

Inimigo::Inimigo() : Personagem(), nivel_maldade(0), velocidadeX(-50.f), tempoFlashDano(0.f) {
    if (!somCarregado) {
        if (bufferDano.loadFromFile("assets/sounds/hit.mp3")) {
            somDano.setBuffer(bufferDano);
            somCarregado = true;
        } else {
            std::cerr << "Erro ao carregar som assets/sounds/hit.mp3!" << std::endl;
        }
    }
}

Inimigo::~Inimigo() {
}

void Inimigo::mover(float dt) {
    x += velocidadeX * dt;
    aplicarGravidade(dt);

    if (y > Config::ALTURA_LIMITE_QUEDA) {
        y = Config::POSICAO_INICIAL_Y;
        vy = 0.f;
    }
}

void Inimigo::atualizarFlashDano(float dt) {
    if (tempoFlashDano > 0.f) {
        tempoFlashDano -= dt;
        if (tempoFlashDano < 0.f) {
            tempoFlashDano = 0.f;
        }
    }
}

void Inimigo::levarDano() {
    num_vidas--;
    tempoFlashDano = Config::DURACAO_FLASH_DANO;
    if (somCarregado && num_vidas > 0) {
        somDano.play();
    }
}

void Inimigo::danificar(Jogador* p) {
    if (p != NULL && !p->estaInvulneravel()) {
        p->perderVida();
        p->ativarInvulnerabilidade();
    }
}

}
}