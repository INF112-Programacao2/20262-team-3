#ifndef MAPA_H
#define MAPA_H

class Mapa {
public:
    struct Obstaculo {
        int xmin;
        int xmax;
        int ymin;
        int ymax;
    };

    struct Passagem {
        int xmin;
        int xmax;
        int ymin;
        int ymax;
        Mapa* mapaDestino;
        int destinoX;
        int destinoY;
        int destinoZ;
    };

    Mapa(int id, const char* nome);
    ~Mapa();
    Mapa(const Mapa&) = delete;
    Mapa& operator=(const Mapa&) = delete;

    int obterId() const;
    const char* obterNome() const;

    void adicionarObstaculo(int xmin, int xmax, int ymin, int ymax);
    void adicionarPassagem(int xmin, int xmax, int ymin, int ymax,
                           Mapa* mapaDestino, int destinoX, int destinoY, int destinoZ);
    int registrarEntidade(int x, int y, int z);
    void atualizarEntidade(int indice, int x, int y, int z);
    void removerEntidade(int indice);
    bool verificarColisao(int x, int y) const;
    bool verificarColisaoEntidade(int x, int y, int z, int indiceIgnorado) const;
    bool verificarPassagens(int x, int y, Passagem& passagemSaida) const;

private:
    struct Ocupacao {
        int x;
        int y;
        int z;
        bool ativa;
    };

    int id;
    char nome[128];
    Obstaculo* obstaculos;
    Passagem* passagens;
    Ocupacao* entidades;
    int quantidadeObstaculos;
    int quantidadePassagens;
    int quantidadeEntidades;
    int capacidadeObstaculos;
    int capacidadePassagens;
    int capacidadeEntidades;
};

#endif