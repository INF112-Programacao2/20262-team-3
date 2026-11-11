#include "Jogador.h"
#include <stdexcept>

Jogador::Jogador(const std::string& nome, Mapa* mapa, int x, int y, int z,
                 int vida, int ataque, int defesa)
    : Entidade(nome, mapa, x, y, z, vida, ataque, defesa),
      bonusAtaque(0), bonusDefesa(0),
      danoCausado(0), danoSofrido(0), inimigosDerrotados(0) {}

int Jogador::calcularAtaque() const { return ataqueBase + bonusAtaque; }
int Jogador::calcularDefesa() const { return defesaBase + bonusDefesa; }

int Jogador::atacar(Entidade& alvo) {
    if (!estaViva())
        throw std::logic_error(nome + " esta derrotado e nao pode atacar");
    if (&alvo == this)
        throw std::invalid_argument(nome + " nao pode atacar a si mesmo");

    // receberDano lanca logic_error se o alvo ja estiver derrotado
    int dano = alvo.receberDano(calcularAtaque());
    danoCausado += dano;
    if (!alvo.estaViva())
        ++inimigosDerrotados;
    return dano;
}

int Jogador::receberDano(int danoBruto) {
    int dano = Entidade::receberDano(danoBruto);
    danoSofrido += dano;
    return dano;
}

void Jogador::definirBonusAtaque(int bonus) {
    if (bonus < 0) throw std::invalid_argument("Bonus de ataque negativo");
    bonusAtaque = bonus;
}

void Jogador::definirBonusDefesa(int bonus) {
    if (bonus < 0) throw std::invalid_argument("Bonus de defesa negativo");
    bonusDefesa = bonus;
}

int Jogador::getBonusAtaque() const { return bonusAtaque; }
int Jogador::getBonusDefesa() const { return bonusDefesa; }
int Jogador::getDanoCausado() const { return danoCausado; }
int Jogador::getDanoSofrido() const { return danoSofrido; }
int Jogador::getInimigosDerrotados() const { return inimigosDerrotados; }