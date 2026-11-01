#include "mapa.h"

Mapa::Mapa(int id, const char* nome)
    : id(id), obstaculos(nullptr), passagens(nullptr), entidades(nullptr),
      quantidadeObstaculos(0), quantidadePassagens(0), quantidadeEntidades(0),
      capacidadeObstaculos(0), capacidadePassagens(0), capacidadeEntidades(0) {
    int indice = 0;
    while (nome != nullptr && nome[indice] != '\0' && indice < 127) {
        this->nome[indice] = nome[indice];
        ++indice;
    }
    this->nome[indice] = '\0';
}

Mapa::~Mapa() {
    delete[] obstaculos;
    delete[] passagens;
    delete[] entidades;
}

int Mapa::obterId() const {
    return id;
}

const char* Mapa::obterNome() const {
    return nome;
}

void Mapa::adicionarObstaculo(int xmin, int xmax, int ymin, int ymax) {
    if (quantidadeObstaculos == capacidadeObstaculos) {
        const int novaCapacidade = capacidadeObstaculos == 0 ? 4 : capacidadeObstaculos * 2;
        Obstaculo* novosObstaculos = new Obstaculo[novaCapacidade];
        for (int indice = 0; indice < quantidadeObstaculos; ++indice) {
            novosObstaculos[indice] = obstaculos[indice];
        }
        delete[] obstaculos;
        obstaculos = novosObstaculos;
        capacidadeObstaculos = novaCapacidade;
    }
    obstaculos[quantidadeObstaculos++] = {
        xmin < xmax ? xmin : xmax, xmin > xmax ? xmin : xmax,
        ymin < ymax ? ymin : ymax, ymin > ymax ? ymin : ymax};
}

void Mapa::adicionarPassagem(int xmin, int xmax, int ymin, int ymax,
                             Mapa* mapaDestino, int destinoX, int destinoY, int destinoZ) {
    if (quantidadePassagens == capacidadePassagens) {
        const int novaCapacidade = capacidadePassagens == 0 ? 4 : capacidadePassagens * 2;
        Passagem* novasPassagens = new Passagem[novaCapacidade];
        for (int indice = 0; indice < quantidadePassagens; ++indice) {
            novasPassagens[indice] = passagens[indice];
        }
        delete[] passagens;
        passagens = novasPassagens;
        capacidadePassagens = novaCapacidade;
    }
    passagens[quantidadePassagens++] = {
        xmin < xmax ? xmin : xmax, xmin > xmax ? xmin : xmax,
        ymin < ymax ? ymin : ymax, ymin > ymax ? ymin : ymax,
        mapaDestino, destinoX, destinoY, destinoZ};
}

int Mapa::registrarEntidade(int x, int y, int z) {
    if (verificarColisao(x, y) || verificarColisaoEntidade(x, y, z, -1)) {
        return -1;
    }

    for (int indice = 0; indice < quantidadeEntidades; ++indice) {
        if (!entidades[indice].ativa) {
            entidades[indice] = {x, y, z, true};
            return indice;
        }
    }

    if (quantidadeEntidades == capacidadeEntidades) {
        const int novaCapacidade = capacidadeEntidades == 0 ? 4 : capacidadeEntidades * 2;
        Ocupacao* novasEntidades = new Ocupacao[novaCapacidade];
        for (int indice = 0; indice < quantidadeEntidades; ++indice) {
            novasEntidades[indice] = entidades[indice];
        }
        delete[] entidades;
        entidades = novasEntidades;
        capacidadeEntidades = novaCapacidade;
    }

    entidades[quantidadeEntidades] = {x, y, z, true};
    return quantidadeEntidades++;
}

void Mapa::atualizarEntidade(int indice, int x, int y, int z) {
    if (indice >= 0 && indice < quantidadeEntidades &&
        entidades[indice].ativa) {
        entidades[indice] = {x, y, z, true};
    }
}

void Mapa::removerEntidade(int indice) {
    if (indice >= 0 && indice < quantidadeEntidades) {
        entidades[indice].ativa = false;
    }
}

bool Mapa::verificarColisao(int x, int y) const {
    for (int indice = 0; indice < quantidadeObstaculos; ++indice) {
        const Obstaculo& obstaculo = obstaculos[indice];
        if (x >= obstaculo.xmin && x <= obstaculo.xmax &&
            y >= obstaculo.ymin && y <= obstaculo.ymax) {
            return true;
        }
    }
    return false;
}

bool Mapa::verificarColisaoEntidade(int x, int y, int z, int indiceIgnorado) const {
    for (int indice = 0; indice < quantidadeEntidades; ++indice) {
        const Ocupacao& entidade = entidades[indice];
        if (indice != indiceIgnorado && entidade.ativa &&
            entidade.x == x && entidade.y == y && entidade.z == z) {
            return true;
        }
    }
    return false;
}

bool Mapa::verificarPassagens(int x, int y, Passagem& passagemSaida) const {
    for (int indice = 0; indice < quantidadePassagens; ++indice) {
        const Passagem& passagem = passagens[indice];
        if (x >= passagem.xmin && x <= passagem.xmax &&
            y >= passagem.ymin && y <= passagem.ymax) {
            passagemSaida = passagem;
            return true;
        }
    }
    return false;
}
