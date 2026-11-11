#include "Chefe.h"
#include <stdexcept>

Chefe::Chefe(const std::string& nome, Mapa* mapa, int x, int y, int z,
             int vida, int ataque, int defesa)
    : Monstro(nome, mapa, x, y, z, vida, ataque, defesa, ALCANCE_CHEFE),
      ataquesRealizados(0), posturaDefensiva(false) {}

std::string Chefe::tipo() const { return "Chefe"; }

int Chefe::calcularDefesa() const {
    return posturaDefensiva ? defesaBase * MULTIPLICADOR_DEFESA : defesaBase;
}

bool Chefe::proximoAtaqueEForte() const {
    return (ataquesRealizados + 1) % ATAQUES_ATE_FORTE == 0;
}

int Chefe::atacar(Entidade& alvo) {
    if (!estaViva())
        throw std::logic_error(nome + " esta derrotado e nao pode atacar");
    if (&alvo == this)
        throw std::invalid_argument(nome + " nao pode atacar a si mesmo");

    int danoBruto = calcularAtaque();
    if (proximoAtaqueEForte())
        danoBruto *= MULTIPLICADOR_FORTE;

    // Se o alvo ja estiver derrotado, receberDano lanca logic_error e o
    // contador e a postura nao mudam (o ataque nao aconteceu).
    int dano = alvo.receberDano(danoBruto);
    ++ataquesRealizados;
    posturaDefensiva = false;
    return dano;
}

void Chefe::defender() {
    if (!estaViva())
        throw std::logic_error(nome + " esta derrotado e nao pode se defender");
    posturaDefensiva = true;
}

bool Chefe::emPosturaDefensiva() const { return posturaDefensiva; }
int Chefe::getAtaquesRealizados() const { return ataquesRealizados; }