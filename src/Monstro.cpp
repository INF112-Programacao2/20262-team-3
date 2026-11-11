#include "Monstro.h"
#include <stdexcept>

Monstro::Monstro(const std::string& nome, Mapa* mapa, int x, int y, int z,
                 int vida, int ataque, int defesa, int alcance)
    : Entidade(nome, mapa, x, y, z, vida, ataque, defesa),
      alcanceBase(alcance) {
    if (alcance < 1)
        throw std::invalid_argument("Alcance invalido para " + nome);
}

int Monstro::getAlcance() const { return alcanceBase; }

int Monstro::atacar(Entidade& alvo) {
    if (!estaViva())
        throw std::logic_error(nome + " esta derrotado e nao pode atacar");
    if (&alvo == this)
        throw std::invalid_argument(nome + " nao pode atacar a si mesmo");

    // receberDano lanca logic_error se o alvo ja estiver derrotado
    return alvo.receberDano(calcularAtaque());
}

void Monstro::defender() {}