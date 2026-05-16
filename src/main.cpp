#include "../include/Gerenciadores/Gerenciador_Grafico.h"

int main() {
    Gerenciador_Grafico gc;

    while (gc.estaAberto()) {
        gc.processarEventos();
        gc.renderizar();
        gc.mostrar();
    }

    return 0;
}