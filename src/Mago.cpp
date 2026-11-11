#include "Mago.h"
#include <stdexcept>

Mago::Mago(const std::string& nome, Mapa* mapa, int x, int y, int z,
           int vida, int ataque, int defesa)
    : Monstro(nome, mapa, x, y, z, vida, ataque, defesa, ALCANCE_MAGO) {}

std::string Mago::tipo() const { return "Mago"; }

int Mago::atacar(Entidade& alvo) {
    if (!estaViva())
        throw std::logic_error(nome + " esta derrotado e nao pode atacar");
    if (&alvo == this)
        throw std::invalid_argument(nome + " nao pode atacar a si mesmo");

    // receberDano desconta a defesa inteira do alvo; somar metade dela ao
    // dano bruto faz a magia ignorar metade da defesa.
    // (receberDano lanca logic_error se o alvo ja estiver derrotado)
    return alvo.receberDano(calcularAtaque() + alvo.calcularDefesa() / 2);
}