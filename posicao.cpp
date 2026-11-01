#include "posicao.h"

#include <iostream>

static long long valorAbsoluto(long long valor) {
    return valor < 0 ? -valor : valor;
}

Posicao::Posicao(Mapa* mapa, int x, int y, int z)
    : x(x), y(y), z(z), mapaAtual(mapa), indiceEntidadeMapa(-1) {
    if (mapaAtual != nullptr) {
        indiceEntidadeMapa = mapaAtual->registrarEntidade(x, y, z);
        if (indiceEntidadeMapa < 0) {
            mapaAtual = nullptr;
        }
    }
}

Posicao::~Posicao() {
    if (mapaAtual != nullptr) {
        mapaAtual->removerEntidade(indiceEntidadeMapa);
    }
}

bool Posicao::movimentar(int deltaX, int deltaY, int deltaZ) {
    if (deltaX == 0 && deltaY == 0 && deltaZ == 0) {
        Mapa::Passagem passagemAtiva;
        if (mapaAtual != nullptr && mapaAtual->verificarPassagens(x, y, passagemAtiva) &&
            passagemAtiva.mapaDestino != nullptr) {
            if (!definirMapa(passagemAtiva.mapaDestino, passagemAtiva.destinoX,
                             passagemAtiva.destinoY, passagemAtiva.destinoZ)) {
                std::cout << "[Colisao] Passagem bloqueada por obstaculo ou entidade!\n";
                return false;
            }
            std::cout << "[Passagem] Transicao ativada para: "
                      << mapaAtual->obterNome() << "\n";
        }
        return true;
    }

    const long long origemX = x;
    const long long origemY = y;
    const long long origemZ = z;
    const long long deslocamentoX = deltaX;
    const long long deslocamentoY = deltaY;
    const long long deslocamentoZ = deltaZ;
    const long long passosX = valorAbsoluto(deslocamentoX);
    const long long passosY = valorAbsoluto(deslocamentoY);
    const long long passosZ = valorAbsoluto(deslocamentoZ);
    const long long quantidadePassos =
        (passosX > passosY ? (passosX > passosZ ? passosX : passosZ)
                           : (passosY > passosZ ? passosY : passosZ));

    for (long long passo = 1; passo <= quantidadePassos; ++passo) {
        const long long proximoXLong = origemX + deslocamentoX * passo / quantidadePassos;
        const long long proximoYLong = origemY + deslocamentoY * passo / quantidadePassos;
        const long long proximoZLong = origemZ + deslocamentoZ * passo / quantidadePassos;
        const long long maximo = static_cast<long long>((~0u) >> 1);
        const long long minimo = -maximo - 1;
        if (proximoXLong < minimo || proximoXLong > maximo ||
            proximoYLong < minimo || proximoYLong > maximo ||
            proximoZLong < minimo || proximoZLong > maximo) {
            return false;
        }

        const int proximoX = static_cast<int>(proximoXLong);
        const int proximoY = static_cast<int>(proximoYLong);
        const int proximoZ = static_cast<int>(proximoZLong);
        const bool avancouX = proximoX != x;
        const bool avancouY = proximoY != y;
        bool colidiuNaDiagonal = false;

        if (mapaAtual != nullptr && avancouX && avancouY) {
            colidiuNaDiagonal =
                mapaAtual->verificarColisao(proximoX, y) ||
                mapaAtual->verificarColisao(x, proximoY) ||
                mapaAtual->verificarColisaoEntidade(proximoX, y, z, indiceEntidadeMapa) ||
                mapaAtual->verificarColisaoEntidade(x, proximoY, z, indiceEntidadeMapa);
        }

        if (mapaAtual != nullptr &&
            (colidiuNaDiagonal || mapaAtual->verificarColisao(proximoX, proximoY) ||
             mapaAtual->verificarColisaoEntidade(proximoX, proximoY, proximoZ,
                                                 indiceEntidadeMapa))) {
            std::cout << "[Colisao] Movimento bloqueado por obstaculo ou entidade!\n";
            return false;
        }

        x = proximoX;
        y = proximoY;
        z = proximoZ;
        if (mapaAtual != nullptr) {
            mapaAtual->atualizarEntidade(indiceEntidadeMapa, x, y, z);
        }

        Mapa::Passagem passagemAtiva;
        if (mapaAtual != nullptr && mapaAtual->verificarPassagens(x, y, passagemAtiva) &&
            passagemAtiva.mapaDestino != nullptr) {
            if (!definirMapa(passagemAtiva.mapaDestino, passagemAtiva.destinoX,
                             passagemAtiva.destinoY, passagemAtiva.destinoZ)) {
                std::cout << "[Colisao] Passagem bloqueada por obstaculo ou entidade!\n";
                return false;
            }
            std::cout << "[Passagem] Transicao ativada para: "
                      << mapaAtual->obterNome() << "\n";
            return true;
        }
    }

    return true;
}

bool Posicao::definirMapa(Mapa* novoMapa, int novoX, int novoY, int novoZ) {
    if (novoMapa != nullptr) {
        const int indiceIgnorado = novoMapa == mapaAtual ? indiceEntidadeMapa : -1;
        if (novoMapa->verificarColisao(novoX, novoY) ||
            novoMapa->verificarColisaoEntidade(novoX, novoY, novoZ, indiceIgnorado)) {
            return false;
        }
    }

    if (novoMapa == mapaAtual) {
        x = novoX;
        y = novoY;
        z = novoZ;
        if (mapaAtual != nullptr) {
            mapaAtual->atualizarEntidade(indiceEntidadeMapa, x, y, z);
        }
        return true;
    }

    if (mapaAtual != nullptr) {
        mapaAtual->removerEntidade(indiceEntidadeMapa);
    }
    mapaAtual = novoMapa;
    x = novoX;
    y = novoY;
    z = novoZ;
    indiceEntidadeMapa = mapaAtual != nullptr ? mapaAtual->registrarEntidade(x, y, z) : -1;
    return true;
}

Posicao::Dados Posicao::obterPosicao() const {
    return {x, y, z, mapaAtual};
}
