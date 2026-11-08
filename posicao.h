#ifndef POSICAO_H
#define POSICAO_H

#include "mapa.h"

class Posicao {
public:
    struct Dados {
        int x;
        int y;
        int z;
        Mapa* mapa;
    };

    Posicao(Mapa* mapa, int x, int y, int z);
    ~Posicao();
    Posicao(const Posicao&) = delete;
    Posicao& operator=(const Posicao&) = delete;

    bool movimentar(int deltaX, int deltaY, int deltaZ);
    bool definirMapa(Mapa* novoMapa, int x, int y, int z);
    Dados obterPosicao() const;

private:
    int x;
    int y;
    int z;
    Mapa* mapaAtual;
    int indiceEntidadeMapa;
};

#endif