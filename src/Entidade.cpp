#include "Entidade.h"
#include <algorithm>
#include <stdexcept>

Entidade::Entidade(const std::string& nome, Mapa* mapa, int x, int y, int z,
                   int vida, int ataque, int defesa)
    : nome(nome), posicao(mapa, x, y, z), vidaMaxima(vida), vida(vida),
      ataqueBase(ataque), defesaBase(defesa) {
    if (vida <= 0 || ataque < 0 || defesa < 0)
        throw std::invalid_argument("Atributos invalidos para " + nome);
}

int Entidade::calcularAtaque() const { return ataqueBase; }
int Entidade::calcularDefesa() const { return defesaBase; }

int Entidade::receberDano(int danoBruto) {
    if (!estaViva())
        throw std::logic_error(nome + " ja foi derrotado");
    int dano = std::min(vida, std::max(1, danoBruto - calcularDefesa()));
    vida -= dano;
    return dano;
}

void Entidade::curar(int quantidade) {
    if (quantidade < 0) throw std::invalid_argument("Cura negativa");
    vida = std::min(vidaMaxima, vida + quantidade);
}

bool Entidade::estaViva() const { return vida > 0; }
const std::string& Entidade::getNome() const { return nome; }
const Posicao& Entidade::getPosicao() const { return posicao; }
Posicao& Entidade::getPosicao() { return posicao; }
int Entidade::getVida() const { return vida; }
int Entidade::getVidaMaxima() const { return vidaMaxima; }